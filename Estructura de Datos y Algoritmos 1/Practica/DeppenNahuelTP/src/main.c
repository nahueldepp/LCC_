#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
 

#include "../cabeceras/funciones.h"
#include "../cabeceras/colas.h"
#include "../cabeceras/listas.h"
#include "../cabeceras/parser.h"
#include "../cabeceras/tablahash.h"
#include "../cabeceras/utils.h"
#include "../cabeceras/search.h"


#define CAPACIDAD_INICIAL_TABLA 127
//cantidad maxima de tokens
#define MAX_TOKENS 250
//la profundidad maxima determina tambien el número maximo de funciones a componer
#define PROFUNDIAD_MAXIMA 5


int main(){
    char texto[300];
    char* tokens[MAX_TOKENS];
    memset(tokens,0,(sizeof(tokens)));

    /**
    * Tabla donde se guardaran las funciones
    */
    TablaHash tablaFunciones= tablahash_crear(CAPACIDAD_INICIAL_TABLA, (FuncionCopia)funcion_copia,
    (FuncionComparadora)funcion_comparar, (FuncionDestructora)funcion_destuir,
    (FuncionHash)funcion_hashear, (FuncionHash)funcion_hashear2);

    NombresFunciones nombres =nombre_funciones_crear();

    TablaHash tablaListas= tablahash_crear(CAPACIDAD_INICIAL_TABLA,(FuncionCopia)lista_copia,(FuncionComparadora)lista_comparar,
    (FuncionDestructora)lista_destruir, (FuncionHash)lista_hashear,(FuncionHash)lista_hashear2);
    

    while(1){
        memset(texto,0,(sizeof(texto)));
        if(tokens[0] != NULL){
            liberar_tokens(tokens);
        }
        
        printf("=>");
        
        if ( fgets(texto, sizeof(texto), stdin) == NULL ) break;
        

        

        int numTokens= tokenizar(texto,tokens);
        if(!numTokens)
            continue;
        if(tokens[numTokens-1][0] != ';'){
            printf("La declaración debe terminar en ';'\n");
            continue;
        }
        int operador= parse_intruccion( tokens[0]);

        
        if(operador == DEFL){
            
            if(parse_defl(tokens, numTokens)){
                Lista lista= lista_crear(tokens, numTokens,0);
                if(lista != NULL){
                    printf("La lista '%s' fue creada con exito\n", lista->nombre);
                    tablahash_insertar(tablaListas, lista);
                }
                lista_imprimir(lista);
                lista_destruir(lista);
            }
            else
                continue;
        } 
        else if(operador == DEFF){

            if(parse_deff(tokens, numTokens, tablaFunciones)){

                Funcion f= funcion_crear(tokens, numTokens);
                if(f != NULL){
                    printf("La funcion '%s' fue creada con exito\n",f->nombre);
                    tablahash_insertar(tablaFunciones, f);
                    nombres_funciones_agregar(nombres, f->nombre);
                    
                }
                funcion_destuir(f);
            }
            else
                continue;
        }
        else if(operador == APPLY){
            int apply= parse_apply(tokens, numTokens,tablaListas);
            //apply = 1 -> apply nombreFun nombreLista;
            //apply = 2 -> apply nombreFun [x,Y,z];
            if(apply > 0){
                struct _Funcion fTemp= {tokens[1],NULL};
                Funcion f=tablahash_buscar(tablaFunciones,&fTemp);
                if(f != NULL){//si se determina que la funcion fue definida por el usuario
                    if(apply == 1){//apply = 1 -> apply nombreFun nombreLista;
                        struct _List lTemp= {tokens[2],NULL};
                        //la busqueda es segura ya que parse_apply determina 
                        //si la lista a usar fue definida previamente
                        Lista lista= tablahash_buscar(tablaListas, &lTemp);
                        lista= funcion_evaluar(f,lista,tablaFunciones);//lista ahora es la copia de la lista original o NULL 
                        if(lista){
                            lista_imprimir(lista);
                            lista_destruir(lista);// no se conserva la lista a la que se le aplico la función
                        }
                    }
                    else{//apply = 2 -> apply nombreFun [x,Y,z];
                        //se crea una lista generica temporal con el nombre "apply"
                        Lista listaGenerica= lista_crear(tokens, numTokens, 1);
                        Lista listaGenericaP= funcion_evaluar(f,listaGenerica, tablaFunciones);
                        if(listaGenericaP){
                            lista_imprimir(listaGenericaP);
                            lista_destruir(listaGenericaP);// no se conserva la lista a la que se le aplico la función
                        }
                        lista_destruir(listaGenerica);
                    }
                    
                }
                else if(primitiva_tipo(tokens[1])<6){// si la funcion es una primitiva
                    if(apply == 1){//apply = 1 -> apply nombreFun nombreLista;
                        struct _List lTemp= {tokens[2],NULL};
                        //la busqueda es segura ya que parse_apply determina 
                        //si la lista a usar fue definida previamente
                        Lista lista= tablahash_buscar(tablaListas, &lTemp);
                        Lista listaCopia=lista_copia(lista);
                        evaluar_primitiva(lista,apply);
                        lista_imprimir(listaCopia);
                        lista_destruir(listaCopia);
                    
                    }
                    else{//apply = 2 -> apply nombreFun [x,Y,z];
                        //se crea una lista generica temporal con el nombre "apply"
                        Lista listaGenerica= lista_crear(tokens, numTokens, 1);
                        evaluar_primitiva(listaGenerica, primitiva_tipo(tokens[1]));
                        lista_imprimir(listaGenerica);
                        lista_destruir(listaGenerica);
                    }
                }
                else
                    printf("Error: La función '%s' no fue previamente definida\n", tokens[1]);
            }
            
            else
                continue;
            
                
        }
        else if(operador == SEARCH){
            if(parse_search(tokens, numTokens, tablaListas)){
                search(tokens,numTokens,nombres,tablaFunciones,tablaListas, PROFUNDIAD_MAXIMA);
            }
            else
                continue;
        }
        else if(operador == EXIT){
            liberar_tokens(tokens);
            break;
        }
        else{
           continue;
        }
        
        
    }
    nombres_funciones_destruir(nombres);
    tablahash_destruir(tablaListas);
    tablahash_destruir(tablaFunciones); 
}