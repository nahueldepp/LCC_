#include "../cabeceras/parser.h"
#include "../cabeceras/funciones.h"
#include "../cabeceras/utils.h"
#include "../cabeceras/tablahash.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int tokenizar(char linea[], char* tokens[]){
    int numTokens = 0;
    linea[strcspn(linea, "\n")] = '\0';
    int largoLinea= strlen(linea);
    
    for(int i = 0; i<largoLinea; i++){
        //ignora espacios
        if(isspace(linea[i]) || linea[i]=='\n')
        continue;
        if(isalnum(linea[i])){
            char secuencia[50];//tamaño suficiente para almacenar una cadena o número entero
            int j = 0;
            while(i<largoLinea && isalnum(linea[i])){
                secuencia[j++]= linea[i++];
            }
            secuencia[j]= '\0';
            
            tokens[numTokens]=malloc(sizeof(char)* (strlen(secuencia)+1));
            strcpy(tokens[numTokens],secuencia);
            
            numTokens++;
        }
        //no se usa elseif para evitar saltear caracteres
        //detecta caracteres especiales
        if(strchr(",;][{}<>=",linea[i])){
            tokens[numTokens]= malloc(sizeof(char)*2);
            tokens[numTokens][0]= linea[i];
            tokens[numTokens][1]= '\0';
           
            numTokens++;
        }
        
    }
    tokens[numTokens]=NULL;
    
    return numTokens;
}

void liberar_tokens(char* tokens[]){

    for(int i = 0; tokens[i]!=NULL; i++){
        free(tokens[i]);
    }
}

/**
 * retorna 1 si la declaracion de defl esta bien definida
 */
int parse_defl(char* tokens[],int numTokens){
    if (numTokens < 5) {
    printf("Error: declaración demasiado corta.\n");
    return 0;
    }
    if(!isalpha(tokens[1][0])){
        printf("Error: El nombre de una lista debe comenzar con una letra\n");
        return 0;
    }
    else if(tokens[2][0] != '='){
        printf("Error: Para definir una lista use '='\n");
        return 0;
    }
    else if (tokens[3][0]!='[' || tokens[numTokens-2][0] != ']'){
        printf("Error: La lista debe estar definida entre corchetes,declaración valida: '[x,Z,y]'\n");
        return 0;
    }
    
    int esInt=1;
    int hayComa=1;
    for(int i = 4; i<numTokens-2 && esInt && hayComa; i+=2){
        esInt= es_entero(tokens[i]);
        if (i + 1 < numTokens - 2 && strcmp(tokens[i + 1], ",") != 0)
            hayComa=0;
    }
    if(!esInt || !hayComa){
        printf("Error: Los datos en la lista son invalidos, declaración valida 'x1,x2,x3'\n");
        return 0;
    }

    return 1;
}


int parse_deff(char* tokens[],int numTokens,TablaHash tablaFunc){
    if(numTokens<4){
        printf("Error: declaración demasiado corta.\n");
        return 0;
    }
    else if(tokens[numTokens-1][0] != ';'){
        printf("La declaración debe terminar en ';'\n");
        return 0;
    }

    struct _Funcion fTemp= {tokens[1],NULL};
    if(primitiva_tipo(fTemp.nombre)<6){
        printf("Error: El nombre de la función esta reservado intente con otro ");
        return 0;
    }
    else if(!isalpha(fTemp.nombre[0])){
        printf("Error: El nombre de la función debe comenzar con una letra\n");
        return 0;
    }
    else if (tablahash_buscar(tablaFunc, &fTemp) != NULL) {
        printf("Error: La función '%s' ya fue definida\n", fTemp.nombre);
        return 0;
    }
    
    else if(tokens[2][0] != '='){
        printf("Error: Para definir una función use '='\n");
        return 0;
    }
    int repeticionAbre=0; //<
    int repeticionCierra=0;//>
    char* funNombreNovalido= NULL;
    char* funcionDefinida= NULL;
    
    for(int i = 3; i<numTokens-1 && funcionDefinida==NULL &&  funNombreNovalido==NULL ; i++){
        fTemp.nombre = tokens[i];
        if(tokens[i][0] == '<')
            repeticionAbre++;
        else if(tokens[i][0] == '>')
            repeticionCierra++;
        else if (!isalpha(tokens[i][0])  && primitiva_tipo(tokens[i])==6){
           funNombreNovalido= tokens[i];
        }
        else if (primitiva_tipo(tokens[i])==6 && tablahash_buscar(tablaFunc, &fTemp) == NULL){
            funcionDefinida= tokens[i];
            
        }
       
         
    }
    
    if(funcionDefinida!=NULL){
        printf("Error: La funcion: '%s' no se encuentra previamente definida\n",funcionDefinida);
        return 0;
    }
    if(funNombreNovalido!=NULL){
        printf("Error: El nombre de la funcion '%s' no es valido\n",funNombreNovalido);
        return 0;
    }
    if(repeticionCierra != repeticionAbre){
        printf("Error: Las repeticiones deben estar declaradas entre '< >'\n");
        return 0;
    }

    return 1;
}

//apply f L2;
//apply f [2 , 1 ,5];
int parse_apply(char* tokens[], int  numTokens, TablaHash tablaLista){
    
    if(numTokens<4){
        printf("Error: Declaración demasiado corta.\n");
        return 0;
    }
    else if(!isalpha(tokens[1][0]) && primitiva_tipo(tokens[1])>5){
        printf("Error: Declaración invalida\n");
        return 0;
    }
    //apply = 1 -> apply nombreFun nombreLista;
    //apply = 2 -> apply nombreFun [x,Y,z];
    int tipoListaaEvaluar= 2- (tokens[2][0]!='[');
    switch(tipoListaaEvaluar){
        case 2:
            
            if (tokens[numTokens-2][0] != ']'){
                printf("Error: La lista debe estar definida entre corchetes,declaración valida: '[x,Z,y]'\n");
                return 0;
            }
            
            int esInt=1;
            int hayComa=1;
            for(int i = 3; i<numTokens-2 && esInt && hayComa; i+=2){
                esInt= es_entero(tokens[i]);
                if (i + 1 < numTokens - 2 && strcmp(tokens[i + 1], ",") != 0)
                    hayComa=0;
            }
            if(!esInt || !hayComa){
                printf("Error: Los datos en la lista son invalidos, declaración valida 'x1,x2,x3'\n");
                return 0;
            }
            return tipoListaaEvaluar;

        case 1:
            if(!isalpha(tokens[2][0])){
                printf("Error: nombre de lista invalido\n");
                return 0;
            }
            struct _List lista={tokens[2],NULL};
            if(tablahash_buscar(tablaLista,&lista ) == NULL){
                printf("Error: La lista '%s' no fue previamente definida\n", tokens[2]);
                return 0;
            }
            return tipoListaaEvaluar;
        default: 
            return 0;
    }
}

int parse_search(char* tokens[], int  numTokens, TablaHash tablaListas){

    if(numTokens<7){
        printf("Error: Declaración demasiado corta\n");
        return 0;
    }
    else if(tokens[1][0]!='{' && tokens[numTokens-2][0] != '}' ){
        printf("Error: Los pares de listas deben estar definidos entre '{ }' \n");
        return 0;
    }
    
    int hayComa= 1;
    int hayPuntoyComa= 1;
    char* lista1= NULL;
    char* lista2= NULL;
    int cantPares=0;
    for(int i = 2; i<numTokens-2  && hayComa && hayPuntoyComa && !lista1 && !lista2 && cantPares<20; i+=4){
        if(tokens[i+1][0] != ',')
            hayComa=0;
        if(i+3<numTokens-2 && tokens[i+3][0] != ';')
            hayPuntoyComa=0;
        

        struct _List l1= {tokens[i], NULL};
        struct _List l2= {tokens[i+2], NULL};

        if(tablahash_buscar(tablaListas,&l1)==NULL)
            lista1 = tokens[i];
        if(tablahash_buscar(tablaListas,&l2)==NULL)
            lista2 = tokens[i+2];
        cantPares++;
    }

    if(cantPares>=20){
        printf("Error: Cantidad de pares excedida, cantidad maxima: 20\n");
        return 0;
    }

    if(!hayComa || !hayPuntoyComa){
        printf("Error: El formato esperado de pares es: {L11,L21;L12,L22}\n");
        return 0;
    }
    if(lista1){
        printf("Error: La lista '%s' no se encuentra previamente definida\n", lista1);
        return 0;
    }
    if(lista2){
        printf("Error: La lista '%s' no se encuentra previamente definida\n", lista2);
    }

    return 1;
}

int parse_intruccion(char* token){
    if(strcmp(token,"defl")==0)
        return DEFL;
    else if(strcmp(token,"deff")== 0)
        return DEFF;
    else if (strcmp(token,"search")== 0)
       return SEARCH;
    else if(strcmp(token,"apply")== 0)
       return APPLY;
    else if ((strcmp(token,"search")== 0))
        return SEARCH;
    else if( strcmp(token,"exit")==0)
        return EXIT;
    else{
        printf("Error: comando invalido\n");
        return -1;
    }
}




