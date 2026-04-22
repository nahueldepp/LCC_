#include "../cabeceras/funciones.h"
#include "../cabeceras/listas.h"
#include "../cabeceras/utils.h"


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * Oi: agrega un cero a la izquierda de la lista:
 */
void func_Oi(Lista lista){
    int cero= 0;
    glista_agregar_izq(lista->glista,&cero,(FuncionCopia)copiar_puntero_entero);
}

/**
 * Od: agrega un cero a la derecha de la lista:
 */
void func_Od(Lista lista){
    int cero= 0;
    glista_agregar_der(lista->glista, &cero, (FuncionCopia)copiar_puntero_entero);
}

/**
 * Si: suma uno al elemento a la izquierda de la lista
 */
void func_Si(Lista lista){
    if(lista->glista->izq == NULL){
        return;
    }
    
    (*(int*)(lista->glista->izq->dato))++;
}

/**
 * Sd: suma un uno al elemento a la derecha de la lista
 */
void func_Sd(Lista lista){
    if(lista->glista->izq == NULL){
        return;
    }
    (*(int*)(lista->glista->der->dato))++;
}

/**
 * Di: borra el elemento de la izquierda de la lista
 * en caso de querer borrar la lista vacia, devuelve la lista vacia
 */
void func_Di(Lista lista){
    glista_eliminar_izq(lista->glista,(FuncionDestructora)destruir_puntero_entero);
}   

/**
 * Dd: borra el elemento de la derecha de la lista
 */
void func_Dd(Lista lista){
    glista_eliminar_der(lista->glista,(FuncionDestructora)destruir_puntero_entero);
}

/*Funciones primitivas*/
const FuncionPrimitiva funcionesPrimitivas[6]=
{
    {"0i",func_Oi},
    {"0d",func_Od},
    {"Si",func_Si},
    {"Sd",func_Sd},
    {"Di",func_Di},
    {"Dd",func_Dd}
};

/**
 * Dada una Lista y un TipoFuncion  < FUNC_USUAIRO
 * evalua la lista segun el TipoFuncion
 */
void evaluar_primitiva(Lista lista, TipoFuncion t){
    funcionesPrimitivas[t].operacion (lista);
}

int primitiva_tipo(char* token){
    if(strcmp(token, "0i")==0)
        return FUNC_OI;
    else if (strcmp(token,"0d")==0)
        return FUNC_OD;
    else if(strcmp(token,"Si")==0)
        return FUNC_SI;
    else if(strcmp(token,"Sd")==0)
        return FUNC_SD;
    else if(strcmp(token,"Di")==0)
        return FUNC_DI;
    else if(strcmp(token,"Dd")==0)
        return FUNC_DD;
    else
        return FUNC_USUARIO;
}

/**
 * Dado un token (nombre de una funcion Primitiva o definida por el usuario)crea una Instruccion,
 * en caso de ser primitiva, solo asigna TipoFuncion como su primitiva correspondiente,
 * en el caso de ser una funcion definida por el usuario, guarda el TipoFuncion y su nombre
 * retorna una Instruccion
 */
Instruccion instruccion_simple_crear(char* token){

    Instruccion nuevaInstruccion = malloc(sizeof(struct _Instruccion));
    assert(nuevaInstruccion != NULL);
    int tipo= primitiva_tipo(token);
    if(tipo < FUNC_USUARIO){
        nuevaInstruccion->funcionTipo= tipo;
    }
    else{
        nuevaInstruccion->funcionTipo= FUNC_USUARIO;
        nuevaInstruccion->nombre= malloc(sizeof(char)* (strlen(token)+1));
        assert(nuevaInstruccion->nombre != NULL);
        strcpy(nuevaInstruccion->nombre,token);
    }

    return nuevaInstruccion;
}

/**
 * Destruye una instruccion
 */
void Instruccion_destruir(Instruccion inst){

    switch(inst->funcionTipo){
        case FUNC_USUARIO:
            free(inst->nombre);
            break;
        case FUNC_REPETICION:
            glista_destruir(inst->listaRepeticion,(FuncionDestructora)Instruccion_destruir);
            break;
        default: 
            //Es una funcion primitiva, no se debe borrar nada;
            break;
    }

    free(inst);
}
 
Instruccion instruccion_copiar(Instruccion inst){
    if(inst == NULL)
        return NULL;

    Instruccion nuevaInst= malloc(sizeof(struct _Instruccion));
    assert( nuevaInst != NULL);
    nuevaInst->funcionTipo= inst->funcionTipo;

    switch(inst->funcionTipo){
        case FUNC_USUARIO:
            nuevaInst->nombre= malloc(sizeof(char) * (strlen(inst->nombre) + 1));
            strcpy(nuevaInst->nombre, inst->nombre);
            break;
        case FUNC_REPETICION:
            nuevaInst->listaRepeticion= glista_copiar(inst->listaRepeticion, (FuncionCopia) instruccion_copiar);
            break;
        default: 
            //Es una funcion primitiva;
            break;
    }
    
    return nuevaInst;
}


/**
 * Dada una instruccion, retorna una copia fisica
 */
void instruccion_imprimir(Instruccion inst, int nivel) {
    for (int i = 0; i < nivel; i++) printf("  "); // indentación

    switch (inst->funcionTipo) {
        case FUNC_OI: 
            printf("0i\n"); 
            break;
        case FUNC_OD:
            printf("0d\n"); 
            break;
        case FUNC_SI: 
            printf("Si\n"); 
            break;
        case FUNC_SD: 
            printf("Sd\n"); 
            break;
        case FUNC_DI:
            printf("Di\n"); 
            break;
        case FUNC_DD: 
            printf("Dd\n"); 
            break;

        case FUNC_USUARIO:
            printf("%s\n", inst->nombre);
            break;

        case FUNC_REPETICION:
            printf("<\n");
            Nodo actual = inst->listaRepeticion->izq;
            while (actual != NULL) {
                instruccion_imprimir((Instruccion)actual->dato, nivel + 1);
                actual = actual->sig;
            }
            for (int i = 0; i < nivel; i++) printf("  ");
            printf(">\n");
            break;
    }
}

/**
 * Aplica la instruccion dada sobre la lista
 */
void instruccion_evaluar(Instruccion inst,Lista lista,TablaHash tablaFunciones,int* numEvaluaciones){

    if(*numEvaluaciones <= 0){
        return ;
    }
    
    if(inst->funcionTipo < FUNC_USUARIO){
        evaluar_primitiva(lista, inst->funcionTipo);
        (*numEvaluaciones)--;
    }
    else if(inst->funcionTipo == FUNC_USUARIO){
        struct _Funcion fTemp = {inst->nombre, NULL};
        Funcion g= tablahash_buscar(tablaFunciones, &fTemp );

        Nodo actual= g->cuerpo->izq;
        while(actual && *numEvaluaciones > 0){
            instruccion_evaluar((Instruccion)actual->dato, lista,tablaFunciones,numEvaluaciones);
            
            actual= actual->sig;
        }
    }
    else{
        while(!lista_lados_iguales(lista) && *numEvaluaciones > 0){
            Nodo actual= inst->listaRepeticion->izq;
            while(actual && *numEvaluaciones > 0){
                instruccion_evaluar((Instruccion)actual->dato,lista, tablaFunciones, numEvaluaciones);
                actual= actual->sig;
                
            }
        }
    }
}
Instrucciones instrucciones_crear(char* tokens[], int* i, int numTokens){

    Instrucciones insts= glista_crear(); 
    
    while( *i < numTokens-1){
        if(tokens[*i][0]  == '>'){
            (*i)++;
            break;
        }
            

        else if(tokens[*i][0] == '<'){
            (*i)++;
            
            Instrucciones subIns= instrucciones_crear(tokens,i,numTokens);
            
            Instruccion nuevaInstruccion= malloc(sizeof(struct _Instruccion));
            nuevaInstruccion->funcionTipo= FUNC_REPETICION;
            nuevaInstruccion->listaRepeticion= subIns;
            
            insts= glista_agregar_der(insts, nuevaInstruccion, (FuncionCopia)instruccion_copiar);
            Instruccion_destruir(nuevaInstruccion);

        }
        else{
            Instruccion nuevaInstruccion = instruccion_simple_crear(tokens[*i]);
            glista_agregar_der(insts, nuevaInstruccion, (FuncionCopia)instruccion_copiar);
            Instruccion_destruir(nuevaInstruccion);
            (*i)++;
        }
        
    }
    return insts;
}

Funcion funcion_crear(char* tokens[],int numTokens){
    
    Funcion nuevaFuncion= malloc(sizeof(struct _Funcion));
    assert(nuevaFuncion != NULL);
    
    nuevaFuncion->nombre= malloc(sizeof(char) * (strlen(tokens[1]) + 1));
    assert(nuevaFuncion->nombre != NULL);
    strcpy(nuevaFuncion->nombre, tokens[1]);
    
    int* i= malloc(sizeof(int));
    *i= 3;
    nuevaFuncion->cuerpo= instrucciones_crear(tokens,i, numTokens);
    free(i);
    return nuevaFuncion;
     
}

void funcion_imprimir(Funcion f) {
    printf("%s =\n", f->nombre);

    Nodo actual = f->cuerpo->izq;
    while (actual != NULL) {
        instruccion_imprimir((Instruccion)actual->dato, 0);
        actual = actual->sig;
    }
}


/**
 * Dada una funcion y un nombre, determina si ese es el nombre de la funcion
 */
int funcion_comparar(Funcion f, Funcion g){
    return comparar_cadena(f->nombre, g->nombre);
}

/**
 * Destruye una función de listas
 */
void funcion_destuir(Funcion funcion){

    free(funcion->nombre);
    glista_destruir(funcion->cuerpo, (FuncionDestructora) Instruccion_destruir);
    free(funcion);
}


/**
 * Dada una funcion de listas crea una copia fisica y la retorna
 */
Funcion funcion_copia(Funcion f){
    
    Funcion copiaFuncion= malloc(sizeof(struct _Funcion));
    assert(copiaFuncion != NULL);
    copiaFuncion->nombre= malloc(sizeof(char) * (strlen(f->nombre) + 1));
    strcpy(copiaFuncion->nombre, f->nombre);
    copiaFuncion->cuerpo= glista_copiar(f->cuerpo, (FuncionCopia)instruccion_copiar);
    return copiaFuncion;
}


/**
 * Dada una función de listas y una lista  evalua la función
 *sobre la lista con la palabra clave apply.
 */
Lista funcion_evaluar(Funcion f, Lista lista,TablaHash tablaFunciones ){
    Lista copiaLista= lista_copia(lista);
    int evaluaciones = MAX_EVALUACIONES;
    for(Nodo actual= f->cuerpo->izq; actual != NULL && evaluaciones>=0; actual= actual->sig){
        instruccion_evaluar((Instruccion)actual->dato, copiaLista, tablaFunciones, &evaluaciones);
        
        
    }
    
    if(evaluaciones <= 0){
        printf("Se alcanzó el número maximo de evaluaciones (posible bucle infinito)\n");
        lista_destruir(copiaLista);
        return NULL;
    }
        
    return copiaLista;
}



/**
 * Hashear un contacto por su nombre.
 */
unsigned funcion_hashear(Funcion funcion) {
  return KRHash(funcion->nombre);
}
unsigned funcion_hashear2(Funcion funcion) {
  return KRHash2(funcion->nombre);
}


/**
 * Crea una estructura NombresFunciones
 */
NombresFunciones nombre_funciones_crear(void){
    NombresFunciones nuevosNombres= malloc(sizeof(struct _nombres));
    nuevosNombres->capacidad= CAPACIDAD_INICIAL_NOMBRES;
    nuevosNombres->arrNombres= malloc(sizeof(char*) * nuevosNombres->capacidad);
    nuevosNombres->numNombres= 0;
    while(nuevosNombres->numNombres< FUNC_USUARIO){
        char* nombrePrimitiva= funcionesPrimitivas[nuevosNombres->numNombres].nombre;
        nuevosNombres->arrNombres[nuevosNombres->numNombres]= malloc(sizeof(char) * (strlen(nombrePrimitiva) + 1));
        strcpy(nuevosNombres->arrNombres[nuevosNombres->numNombres],nombrePrimitiva);
        nuevosNombres->numNombres++;
    }
    
    return nuevosNombres;
}

/**
 * agrega nombre de funciones a un array NombresFunciones
 */
void nombres_funciones_agregar(NombresFunciones nombres, char* nuevoNombre){
    if(nombres->numNombres == nombres->capacidad){
        nombres_funciones_ampliar_capacidad(nombres);
    }
    nombres->arrNombres[nombres->numNombres]= malloc(sizeof(char)* (strlen(nuevoNombre) + 1));
    strcpy(nombres->arrNombres[nombres->numNombres], nuevoNombre);
    nombres->numNombres++;

} 

/**
 * Dobla la capacidad de almacenamieto de nombres
 */
void nombres_funciones_ampliar_capacidad(NombresFunciones nombres){
    nombres->capacidad *= 2;
    nombres->arrNombres= realloc(nombres->arrNombres, sizeof(char*) * nombres->capacidad);
}

/**
 * Destruye una estructura NombresFunciones
 */
void nombres_funciones_destruir(NombresFunciones nombres){
    for(int i = 0; i < nombres->numNombres; i++){
        free(nombres->arrNombres[i]);
    }
    free(nombres->arrNombres);
    free(nombres);
}
