#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define MAX_TXT 256
#define MAX_ARGS 50

void tokenizar(char* buffer, char* args[]){
    unsigned argsNum = 0;
    //parseo el string
    char* tok= strtok(buffer, " ");
    while(tok != NULL && argsNum < MAX_ARGS-1){
        args[argsNum++] = tok ;
        printf("%s\n", tok);
        tok = strtok(NULL, " ");
    }
    args[argsNum] = NULL;// para usar en execvp
    
}

int manejar_comando_interno(char* args[]){

    if(args[0] == NULL){return 1;}

    if(strcmp(args[0], "cd") == 0){ //cambio de directorio
        if(args[1] == NULL){
            char* home= getenv("HOME"); //Devuelve el valor de la variable de entorno HOME
            if(home == NULL){
                home = "/"; //devuelvo al root
            }
            if(chdir(home) != 0){ //cambio el directorio, devuelve 0 si la operación fue exitosa
                perror("cd");
            }
        }
        else{
            if(chdir(args[1]) != 0){
                perror("cd");
            }
        }
        return 1;
    }
    if(strcmp(args[0], "exit") == 0){exit(0);}

    return 0;
}

void ejecutar_cmd_simple(char* cmd,int redir, char*txt ){

    char* args[MAX_ARGS];
    tokenizar(cmd, args);
    if(manejar_comando_interno(args)){ return;}

    pid_t pid = fork();

    if(pid == -1)
        exit(EXIT_FAILURE);

    if(pid == 0){

        if(redir && txt != NULL){
            int fd = open(txt, O_CREAT | O_WRONLY | O_TRUNC, 0644);

            if(fd == -1){
                perror("open");
                exit(EXIT_FAILURE);
            }

            if(dup2(fd, STDOUT_FILENO) == -1){
                perror("dup2");
                close(fd);
                exit(EXIT_FAILURE);
            }

            close(fd);
        }
        execvp(args[0],args);
        perror("execpv\n");
        exit(EXIT_FAILURE);
    }
    else{
        //esperamos al hijo
        wait(NULL);
    }
}

void ejecutar_pipes(char* comandos[], unsigned numCmd){

    /**
    comandos  pipes     fd[]
        1       0        -  
        2       1        (fd[0]lectura,fd[1]escritura)   
        3       2        fd[0]R,fd[1]W, fd[2]R,fd[3]W   
        4       3        fd[0]R,fd[1]W, fd[2]R,fd[3]W , fd[4]R,fd[5]W 
        .       .
        .       .
        n       n-1     ... fd[(n-1)*2]W

        los extremos de lectura y escritura tienen la forma:
            fd[i*2]R
            fd[i*2 + 1]
            i= 0, ... , numCmd
     */

    int fd[(numCmd - 1)*2];
    pid_t pid;
    for(unsigned i = 0; i < numCmd - 1; i++){
        if(pipe(fd + i*2)){
            perror("pipe");
            exit(EXIT_FAILURE);
        };// voy haciendo pipes usando fd[i*2]R,fd[i*2 +1]W;
    }
    for(unsigned i = 0; i < numCmd; i++){

        pid =fork();

        if(pid < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if(pid == 0){//estoy en un proceso hijo
            //TEngo que hacer que la salida del pipe anterior sea manejada or la entrada del siguiente
            if(i != 0){
                dup2(fd[(i-1)*2], STDIN_FILENO);//se redirige la lectura al fdR del pipe anteiror
            }
            if(i != numCmd -1){
                dup2(fd[i*2+1], STDOUT_FILENO);//en el pipe actual, redirijo la salida
            }
            char* args[MAX_ARGS];
            tokenizar(comandos[i], args);
            for(unsigned x = 0; x < 2*(numCmd - 1); x++){
                close(fd[x]);//cierro todos los files descriptors referentes a las pipes en el hijo ya que ahora
                //stdin y stdout apuntan a las pipes
            }
            execvp(args[0], args);
            perror("excevp");
            exit(EXIT_FAILURE);

        }

    }
    for (unsigned i = 0; i < numCmd; i++)
    {wait(0);}//espero a todos los hijos
    for (unsigned i = 0; i < numCmd -1 ; i++){
        close(fd[i]);
    }
    
}
void manejar_comando(char* buffer){

    
    //----buscamos si existe ">"
    char* txt = NULL;
    int redir = 0;
    char* signo = strchr(buffer, '>'); //buscamos la primera aparición de >
 
    if(signo != NULL){
        redir = 1;
        *signo = '\0'; //en buffer se corta el string en signo

        signo++;

        while( *signo == ' '){
            signo++; //salteo los espacios
        }
        txt = signo;
    }
    //-----------------------------------------

    //----Separo comandos para pipes con |
    char* comandos[MAX_ARGS];
    char* tok = strtok(buffer, "|");
    int numCmd = 0;
    while(tok != NULL){ //separo por comandos para despues tokenizarlos
        comandos[numCmd++] = tok;
        tok = strtok(NULL, "|");
    }
    
    if(numCmd == 1)
        ejecutar_cmd_simple(buffer, redir, txt);
    else
        ejecutar_pipes(comandos, numCmd);
    
}



int main(void){
    
    char buffer[MAX_TXT];
    char* args[MAX_ARGS];
    while(1){
        printf(">> ");
        if(fgets(buffer,MAX_TXT,stdin) == NULL){
            perror("Error al leer el comando\n");
            break;
        }
        fflush(stdout);

        buffer[strcspn(buffer, "\n")] = '\0';
        if(strlen(buffer) == 0){continue;}
        // obtengo el comando
        manejar_comando(buffer);
    }
    return 0;
}