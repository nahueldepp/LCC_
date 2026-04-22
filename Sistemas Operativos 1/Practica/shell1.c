#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

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

void manejar_comando(char** args){
    pid_t pid = fork();
    
    if(pid == -1)
        exit(EXIT_FAILURE);
    
    if(pid == 0){
        execvp(args[0],args);
        perror("execpv\n");
        exit(EXIT_FAILURE);
    }
    else{
        //esperamos al hijo
        wait(NULL);
    }
    
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
        tokenizar(buffer, args);

        manejar_comando(args);

    }
    return 0;
}