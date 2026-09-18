#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

//---Estructuras--//

//----------------//
//---prototipos---//


int crear_lista_de_archivos(char**);

int crear_texto_unificado(char**, int,char*);

//----------------//


int main(int argc, char* argv[]){

    if (argc < 2) {
        printf("Uso: %s <directorio>\n", argv[0]);
        return 1;
    }
    char comando[60];
    snprintf(comando,sizeof(comando),"cd Textos/%s && pwd",argv[1]); //crea el comando ls Textos/Carpeta > archvivos.txt, 
                                                                            //donde se pone linea por linea el nombre de los archivos dentro de un archivo

    int status=system(comando);
    if (status == -1){
        printf("Revise el nombre del archivo\n");
    }

    char* lista_de_archivos[50];
    int cantidad_de_archivos=crear_lista_de_archivos(lista_de_archivos);//crea una lista de archivos y guarda su cantidad
    
    crear_texto_unificado(lista_de_archivos,cantidad_de_archivos,argv[1]);

    for(int j=0;j<2;j++){
        printf("%s\n",lista_de_archivos[j]);
        printf("%c\n",lista_de_archivos[j][strlen(lista_de_archivos[j])-1]);
        free(lista_de_archivos[j]);
    }
    


    return 1;
}

//crear_lista_de_archivos: char**->int
//recibe un array de punteros a char y abre el archivo donde estan los nombres de los archivos txt
//luego coloca cada nombre en la lista de nombres, es decir el array de punteros a char
//y devuelve la cantidad de archivos

int crear_lista_de_archivos(char** lista){
    system("pwd");
    char nombre_archivo[60];
    FILE* archivos=fopen("archivos.txt","r");
    if (archivos==NULL){
        printf("Error al abrir el archivo\n");
        return -1;   
    }
    else{
        int i=0;
        while(fgets(nombre_archivo,sizeof(nombre_archivo),archivos) && i<50){
            if(nombre_archivo[strlen(nombre_archivo)-1]=='\n'){
                nombre_archivo[strlen(nombre_archivo)-1]='\0';
            }
            lista[i]=(char*)malloc(strlen(nombre_archivo)+1);
            strcpy(lista[i],nombre_archivo);
            i++;
        }
        fclose(archivos);
            return i;
    }
}

//crear_texto_unificado():char**->file(retorna int 0 si funciona correctamente)
//Dado una lista de nombres de archivos txt, crea un archivo cuyo contenido es la union de los archivos de las listas.
//Cada linea de unificado.txt sera una frase hasta un '.', en los archivos anteriores 
int crear_texto_unificado(char** lista,int cantidad_archivos,char* carpeta_de_archivos){

    FILE *unificados=fopen("unificados.txt","a");

    
    int i=0;

   while(cantidad_archivos>i){
        
        char comando[60];
        snprintf(comando,sizeof(comando),"Textos/%s/%s",carpeta_de_archivos,lista[i]);

        FILE* texto=fopen(comando,"r");
        if (texto==NULL){
            printf("Error al abrir el archivo\n");
            return -1;   
        }
        char frase;
        
        while((frase=fgetc(texto))!=EOF){
            if(isupper(frase)){
                tolower(frase);
            }
            if(frase=='\n'){
                frase=' ';
            }
            if((ispunct(frase) && !(frase=='.'))){
                frase=' ';
            } 
            if(frase=='.'){
                frase='\n';
                 
            }

            fputc(frase,unificados); 

            
        }
        fclose(texto);

        
        i++;
    }
    fclose(unificados);

}


//limpiar_frase:char*->void
//dada una frase, reemplaza caracteres especiales por ''.

void limpiar_frase(char *frase){
    int i=0;
    int largo_frase= strlen(frase);
    while(i<largo_frase){
        if(!isalnum(frase[i])){
            frase[i]=' ';
        }
    }
}