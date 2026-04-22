#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct _GNodo{
    void* dato;
    struct _GNodo* sig;
}GNodo;

typedef struct{
    GNodo* primero;
    GNodo* ultimo;
}GList;

typedef  void   (* FuncionDestructora)(void *dato);
typedef  void* (* FuncionCopia)(void *dato);
typedef  void   (* FuncionVisitante) (void* dato);
typedef  void* (* FuncionTransformar)(void* dato);


GList glist_crear(){
    GList lista;
    lista.primero=NULL;
    lista.ultimo=NULL;
    return lista;
}

GList glist_agregar_final(GList lista, void* dato, FuncionCopia copia){
    GNodo* nuevo = malloc(sizeof(GNodo));
    nuevo->dato= copia(dato);
    nuevo->sig = NULL;
    if(lista.primero == NULL){
        lista.primero = nuevo;
    }
    else{
        lista.ultimo->sig = nuevo;
    }
    lista.ultimo = nuevo;
    return lista;
}

void glist_destruir(GList lista, FuncionDestructora destroy){
    GNodo* temp;
    for(GNodo* nodo = lista.primero; nodo != NULL; ){
        temp = nodo;
        nodo = nodo->sig;
        destroy(temp->dato);
        free(temp);
    }
}

void glist_recorrer(GList lista, FuncionVisitante visit){
    for(GNodo* nodo = lista. primero; nodo != NULL; nodo = nodo->sig){
        visit(nodo->dato);
    }
}

//a)
/**
 * devuelve el resultado de realizar un map a la lista
 * aplicando la funcion f a cada uno de los elementos de la lista
 */
GList glist_map(GList lista, FuncionTransformar f, FuncionCopia c){

    for(GNodo* nodo= lista.primero; nodo != NULL; nodo= nodo->sig){
        void* nuevoDato= f(nodo->dato);
        nodo->dato= c(nuevoDato);
    }
    return lista;
}

/* b)  Defina una funcion stringMayuscula que cumpla con el prototipo 
de FuncionTransformar.La misma debe tomar un string y devolver un nuevo
 string igual al anterior pero con todos sus caracteres alfabeticos en mayuscula */

char* stringMayuscula(char* string){

    int longStr= strlen(string);
    char* nuevoString= malloc(sizeof(char) * longStr + 1);
    for(int i = 0; i <= longStr; i++){
        if(isalpha(string[i])){
            nuevoString[i] = toupper(string[i]);
        }
    }
    
    return nuevoString;
}

void* copia_string(void* dato){
    char* str= (char*) dato;
    char* nuevo = malloc(sizeof(char)*(strlen(str)+1));
    strcpy(nuevo,str);
    return nuevo;
}

void imprimir_string(char* dato){
    printf("%s\n",dato);
}
void dest_string(void* dato){
    free(dato);
}

int main(){

    GList  lista = glist_crear ();
    char* str = "Licenciatura ";
    lista = glist_agregar_final(lista , str , copia_string);
    str = "en ";
    lista = glist_agregar_final(lista , str , copia_string);
    str = "Ciencias ";lista = glist_agregar_final(lista , str , copia_string);
    str = "de la ";
    lista = glist_agregar_final(lista , str , copia_string);
    str = "Computacion.";
    lista = glist_agregar_final(lista , str , copia_string);
    //  COMPLETAR
    
    glist_map(lista, (FuncionTransformar)stringMayuscula, (FuncionCopia) copia_string);
    glist_recorrer(lista,(FuncionVisitante) imprimir_string);
    glist_destruir(lista , dest_string);

    printf("%d",7/2);
    
   
    return 0;

}