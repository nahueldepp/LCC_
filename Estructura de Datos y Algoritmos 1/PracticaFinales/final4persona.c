#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "final4tabla.h"

typedef struct{
    char* nombre, *direccion,*dni;
    int edad;
}Persona;

/**
 * Dado un puntero a persona crea una copia fisica de la Persona 
 */
Persona* persona_copia(Persona* persona){

    Persona* copia= malloc(sizeof(Persona));
    copia->direccion= malloc(sizeof(char)* (strlen(persona->direccion)+ 1));
    strcpy(copia->direccion,persona->direccion);
    
    copia->dni= malloc(sizeof(char)* (strlen(persona->dni)+ 1));
    strcpy(copia->dni,persona->dni);
    
    copia->nombre= malloc(sizeof(char)* (strlen(persona->nombre)+ 1));
    strcpy(copia->nombre,persona->nombre);
    
    copia->edad= persona->edad;

    return copia;

}

void persona_destruir(Persona* persona){
    free(persona->direccion);
    free(persona->dni);
    free(persona->nombre);
    free(persona);
    return;

}

int persona_comparar(Persona* p1, Persona* p2){

    return strcmp(p1->nombre,p2->nombre);
}


unsigned persona_hash(Persona* persona){

    unsigned hashVal;
    char* dni= persona->dni;
    for(hashVal= 0; *(dni) != '\0'; ++dni){
        hashVal= *dni +31*hashVal;
    }
    return hashVal;
}

/**
 * dada una tabla con personas, imprime la tabla
 */
/* void tabla_imrimir(TablaHash tabla){

    for(unsigned i = 0; i< tabla->capacidad; i++){
        
        if(tabla->elems[i].dato!= NULL){
            if(tabla->elems[i].estado == ELIMINADO)
                printf("%d \t -eliminado-\n", i);
            else{
                Persona* p= tabla->elems[i].dato;
                printf("%d \t -%s-\n", i, p->nombre );
            }
        }
        else
            printf("%d \t ---\n", i);
    }
}
 */
void tabla_imprimir2(TablaHash tabla){

    for(unsigned i = 0; i< tabla->capacidad; i++){
        printf("%d\t", i);
        if(tabla->elems[i]!= NULL){
            CasillaHash nodo= tabla->elems[i];
            Persona* p;
            while(nodo){
                p= nodo->dato;
                printf("%s->", p->nombre );
                nodo=nodo->sig;
            }
            puts("");
        }
        else
            printf("---\n");
    }
}
int main(){

    TablaHash personas= tabla_crear((FuncionCopiadora)persona_copia, (FuncionComparadora)persona_comparar,
                        (FuncionDestructora)persona_destruir, (FuncionHash)persona_hash);
    Persona p1= {.direccion="rep1", .dni="4444102",.nombre="Nahuel",.edad=22};
    Persona p2= {.direccion="rep2", .dni="4444104",.nombre="Juana",.edad=23};
    //agrego a Nahuel
    tabla_insertar(personas, &p1);
    tabla_imprimir2(personas);
    //agrego a Juana
    tabla_insertar(personas, &p2);
    tabla_imprimir2(personas);
    
    Persona* pp= tabla_buscar(personas, &p1);
    printf("Persona pp : %s, %s, %s, %d\n", pp->direccion, pp->dni, pp->nombre,pp->edad); 
    //elimino a Juana
    tabla_eliminar(personas, &p2);
    tabla_imprimir2(personas);
    tabla_insertar(personas, &p2);
    
    Persona p3= {.direccion="rep4", .dni="4444104",.nombre="Juan",.edad=23};
    tabla_insertar(personas, &p3);
    tabla_imprimir2(personas);

    Persona p4= {.direccion="rep4", .dni="4444105",.nombre="Maria",.edad=23};
    tabla_insertar(personas, &p4);
    tabla_imprimir2(personas);

    pp= tabla_buscar(personas, &p3);
    printf("Persona pp : %s, %s, %s, %d\n", pp->direccion, pp->dni, pp->nombre,pp->edad);

    tablahash_destruir(personas);
    
    return 0;

    
}