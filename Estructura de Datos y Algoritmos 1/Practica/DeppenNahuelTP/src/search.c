#include "../cabeceras/funciones.h"
#include "../cabeceras/utils.h"
#include "../cabeceras/tablahash.h"
#include "../cabeceras/colas.h"
#include "../cabeceras/search.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

/**
 * Dado un array de tokens crea pares de listas
 */
ParesDeListas pares_crear(char* tokens[], int numTokens, TablaHash tablaListas){

    ParesDeListas paresDelistas= malloc(sizeof(struct _Pares));
    assert(paresDelistas != NULL);
    paresDelistas->numPar = 0;

    for(int i = 2; i<numTokens-2 ; i+=4){
        
        struct _List l1= {tokens[i], NULL};
        struct _List l2= {tokens[i+2], NULL};

        paresDelistas->par[paresDelistas->numPar].listaOrigen= tablahash_buscar(tablaListas,&l1);
        paresDelistas->par[paresDelistas->numPar].listaDestino= tablahash_buscar(tablaListas,&l2);
        
        paresDelistas->numPar++;
    } 

    return paresDelistas;
}

/**
 * Destruye  ParesDeListas
 */
void pares_destruir(ParesDeListas paresDelistas){
    free(paresDelistas);
}


/**
 * A partir de pares de listas, crea una composicion inicial, en la cual no se aplicaron funciones
 * es decir, solo copia las listas de origen
 */
Composicion composicion_crear(ParesDeListas pares, int profundidad){

    Composicion comp= malloc(sizeof(struct _Composicion));
    comp->profundidad = profundidad;
    comp->funcNombres=malloc(sizeof(char*) * (profundidad));
    comp->numListas= 0;
    comp->numFunc= 0;
    
    for(int i = 0; i < pares->numPar; i++){
        comp->listas[i]= lista_copia(pares->par[i].listaOrigen);
        comp->numListas++;
    }

    return comp;
}

/**
 * Crea una copia de una composición
 */
Composicion composicion_copiar(Composicion comp){

    Composicion copiaComp= malloc(sizeof(struct _Composicion));
    copiaComp->numListas= comp->numListas;
    for(int i = 0; i < comp->numListas; i++){
        copiaComp->listas[i]= lista_copia(comp->listas[i]);
    }
    copiaComp->profundidad = comp->profundidad ;
    copiaComp->funcNombres=malloc(sizeof(char*) * (comp->profundidad ));
    copiaComp->numFunc= comp->numFunc;
    for(int j = 0; j < comp->numFunc; j++){
        copiaComp->funcNombres[j]= malloc(sizeof(char) * (strlen(comp->funcNombres[j]) + 1));
        strcpy(copiaComp->funcNombres[j],comp->funcNombres[j]);
    }
    return copiaComp;
}

/**
 * Composicion destruir 
 */

void composicion_destruir(Composicion comp){

    for(int i = 0; i < comp->numListas; i++){
        lista_destruir(comp->listas[i]);
    }
    for(int i = 0; i < comp->numFunc; i++){
        free(comp->funcNombres[i]);
    }
    free(comp->funcNombres);
    free(comp);
}
/**
 * Aplica una instruccion a las listas de la estructura Composicion y agrega el nombre de la instrucción simple
 * (nombre de la función) al array de nombres
 */
Composicion nueva_composicion(Instruccion inst, Composicion comp, TablaHash tablaFunciones){

    Composicion nuevaComp= composicion_copiar(comp);
    
    //agregamos el nombre de la instruccion
    //por como funciona la composicion, no habra repeticiones
    switch(inst->funcionTipo){

        case 0:
            nuevaComp->funcNombres[nuevaComp->numFunc]= malloc(sizeof(char)*(strlen("0i")+1));
            strcpy(nuevaComp->funcNombres[nuevaComp->numFunc],"0i");
            break;
        case 1:
            nuevaComp->funcNombres[nuevaComp->numFunc]= malloc(sizeof(char)*(strlen("0d")+1));
            strcpy(nuevaComp->funcNombres[nuevaComp->numFunc],"0d");
            break;
        case 2:
            nuevaComp->funcNombres[nuevaComp->numFunc]= malloc(sizeof(char)*(strlen("Si")+1));
            strcpy(nuevaComp->funcNombres[nuevaComp->numFunc],"Si");
            break;
        case 3:
            nuevaComp->funcNombres[nuevaComp->numFunc]= malloc(sizeof(char)*(strlen("Sd")+1));
            strcpy(nuevaComp->funcNombres[nuevaComp->numFunc],"Sd");
            break;
        case 4:
            nuevaComp->funcNombres[nuevaComp->numFunc]= malloc(sizeof(char)*(strlen("Di")+1));
            strcpy(nuevaComp->funcNombres[nuevaComp->numFunc],"Di");
            break;
        case 5:
            nuevaComp->funcNombres[nuevaComp->numFunc]= malloc(sizeof(char)*(strlen("Dd")+1));
            strcpy(nuevaComp->funcNombres[nuevaComp->numFunc],"Dd");
            break;
        case 6:
            nuevaComp->funcNombres[nuevaComp->numFunc]= malloc(sizeof(char)*(strlen(inst->nombre)+1));
            strcpy(nuevaComp->funcNombres[nuevaComp->numFunc],inst->nombre);
            break;
        case 7: break;    
            
    }
    nuevaComp->numFunc++;
    int maxEvaluaciones= MAX_EVALUACIONES; 
    for(int i = 0; i < comp->numListas && maxEvaluaciones>0; i++){
        maxEvaluaciones= MAX_EVALUACIONES; 
        //instruccion evaluar modifica la lista dada, asi que modificara las copias de las listas originales de comp
        instruccion_evaluar(inst, nuevaComp->listas[i], tablaFunciones,&maxEvaluaciones);
    }

    if(maxEvaluaciones <=0){
        composicion_destruir(nuevaComp);
        return NULL;
    }
    return nuevaComp;
}

/**
 * Compara las listas de la composición con las listas de origen
 * retorna 1 si las listas de la composición son todas iguales a las de origen
 * caso contrario retorna 0;
 */
int composicion_adecuada(Composicion comp, ParesDeListas paresListas){

    int adecuada = 1;
    for(int i = 0; i<comp->numListas && adecuada; i++){
        adecuada= lista_comparar_cuerpo(comp->listas[i],paresListas->par[i].listaDestino);
    }
    return adecuada;
}


Composicion search_aux(NombresFunciones nombres, ParesDeListas paresDelistas,Cola cola,TablaHash tablaFunciones, int profundidadMax){

    Composicion comp=NULL;
    Composicion compAdecuada= NULL;
    Composicion inicioDeCola= cola_inicio(cola);
    int encontrada= 0;
    int colaVacia= cola_es_vacia(cola);
    int casoCompNull=0;
    while(!colaVacia && !encontrada && inicioDeCola->numFunc <profundidadMax){
        comp= cola_desencolar(cola,(FuncionDestructora)composicion_destruir,(FuncionCopia)composicion_copiar);
        //en el siclo for  no se aumenta la profundidad de las composiciones (cant de nombres)
        for(int i=0; i < nombres->numNombres && !encontrada; i++){
            // como por cada nombre es una posible composicion de funciones e instruccion_evaluar
            //modifica la lista pasada, se crean copias de la comp inicial para ser evaluadas 
            //y se encolan por si se usan mas tarde
            Instruccion inst= instruccion_simple_crear(nombres->arrNombres[i]);
            Composicion nuevaComp= nueva_composicion(inst,comp,tablaFunciones);
            Instruccion_destruir(inst);
            if(nuevaComp ==NULL){
                casoCompNull=1;
                break;
            }
            encontrada= composicion_adecuada(nuevaComp,paresDelistas);
            
            if(!encontrada){
                cola=cola_encolar(cola,nuevaComp,(FuncionCopia)composicion_copiar);
                composicion_destruir(nuevaComp);
            }
            else{
                compAdecuada= nuevaComp;
            }
            
        }
        composicion_destruir(comp);
        if(casoCompNull){
            compAdecuada=NULL;
            break;
        }
       
        colaVacia= cola_es_vacia(cola);
        inicioDeCola= cola_inicio(cola);
    }
    if(!cola_es_vacia(cola)){
        cola_destruir(cola,(FuncionDestructora)composicion_destruir);
    }

    return compAdecuada;
    
}

/**
 * Usando BFS busca si existe composición que cumpla con las condiciones de los pares de listas ingresados por
 * el usuario dentro del limite de profundidad definido
 */
void search(char* tokens[],int numTokens,NombresFunciones nombres, TablaHash tablaFunciones, TablaHash tablaListas, int profundadMax){

    ParesDeListas paresDelistas= pares_crear(tokens,numTokens, tablaListas);
    Composicion inicial = composicion_crear(paresDelistas, profundadMax);
    Cola cola= cola_crear();
    cola= cola_encolar(cola, inicial,(FuncionCopia)composicion_copiar);

    Composicion adecuada=search_aux(nombres, paresDelistas, cola,tablaFunciones ,profundadMax);

    if(adecuada){
        printf("La composición encontrada es:\n");
        for(int i = 0; i < adecuada->numFunc; i++){
            printf("%s ",adecuada->funcNombres[i]);
        }
        puts("");
        composicion_destruir(adecuada);
    }
    else{
        printf("No se encontró una composición adecuada dentro de la profundidad aceptable: %d\n",profundadMax);
        printf("Considera definir funciones nuevas o revise si todas tienen como dominio a los naturales \n");
    }
    pares_destruir(paresDelistas);
    composicion_destruir(inicial);


}