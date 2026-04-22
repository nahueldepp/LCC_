#include"headers/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



/**
 * Estructura del nodo del arbol AVL.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * un puntero al nodo raiz del subarbol derecho (der), y
 * un entero para representar la altura del arbol (altura)
 */
typedef struct _AVL_Nodo {
  void* dato;
  struct _AVL_Nodo* izq, * der;
  int altura;
  int balance;
} AVL_Nodo;

/**
 * Estructura del arbol AVL.
 * Tiene un puntero al nodo raiz (raiz),
 * un puntero a funcion (copia) que recibe un dato y retorna un puntero con la
 * direccion de memoria de una copia fisica del dato,
 * un puntero a funcion (comp) que compara dos datos y retorna un entero
 * negativo si el primero es menor que el segundo, 0 si son iguales, y un entero
 * positivo en caso contrario,
 * y un puntero a una funcion (destr) que recibe un dato y lo destruye.
 * En esta implementación, los punteros a funcion necesarios para manipular los
 * datos se mantienen en la estructura para evitar pasarlos por parametro a las
 * demas funciones.
 */
struct _AVL {
  AVL_Nodo* raiz;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
};



/**
 * avl_crear: Retorna un arbol AVL vacio
 */
AVL avl_crear(FuncionCopiadora copia, FuncionComparadora comp,
  FuncionDestructora destr){

    AVL nuevoArbol= malloc(sizeof(struct _AVL));
    assert(nuevoArbol != NULL);
    nuevoArbol->comp= comp;
    nuevoArbol->copia= copia;
    nuevoArbol->destr= destr;
    nuevoArbol->raiz= NULL;

    return nuevoArbol;
  }


/**
 * avl_destruir: Destruye el arbol y sus datos.
 */
static void avl_nodo_destruir(AVL_Nodo* raiz, FuncionDestructora destr){

    if(raiz != NULL){
        avl_nodo_destruir(raiz->izq, destr);
        avl_nodo_destruir(raiz->der, destr);
        destr(raiz->dato);
        free(raiz);
    }

}

void avl_destruir(AVL arbol){
    avl_nodo_destruir(arbol->raiz, (FuncionDestructora)arbol->destr);
    free(arbol);
}



/**
 * avl_buscar: Retorna 1 si el dato se encuentra y 0 en caso contrario
 */
static int avl_nodo_buscar(AVL_Nodo* raiz, FuncionComparadora comp,
  void* dato){

    if(raiz == NULL){
        return 0;
    }
    if(comp(raiz->dato, dato) == 0){
        return 1;
    }
    else if(comp(raiz->dato, dato)<0)//raiz->dato < dato
    {
       return avl_nodo_buscar(raiz->der, comp,dato);
    }
    else{
       return avl_nodo_buscar(raiz->izq, comp, dato);
    }
}

int avl_buscar(AVL arbol, void* dato){
    return avl_nodo_buscar(arbol->raiz, arbol->comp, dato);
}



/**
 * avl_nodo_altura: Funcion interna que retorna la altura del arbol.
 * La altura del arbol vacio se define como -1.
 */
static int avl_nodo_altura(AVL_Nodo* raiz){
    
    return (raiz == NULL? -1:raiz->altura);
}



/**
 * avl_nodo_max_altura_hijos: Funcion interna que retorna la maxima altura de
 * los hijos.
 */
static unsigned int avl_nodo_max_altura_hijos(AVL_Nodo* raiz){
    assert(raiz != NULL);
    int izq= avl_nodo_altura(raiz->izq);
    int der=  avl_nodo_altura(raiz->der);
    return izq>der? izq:der;
}


/**
 * avl_nodo_factor_balance: Funcion interna que retorna el factor de balance de
 * un nodo.
 */
static int avl_nodo_factor_balance(AVL_Nodo* raiz){
    assert( raiz != NULL);
    int bal=  avl_nodo_altura(raiz->der) - avl_nodo_altura(raiz->izq);
    assert((bal >= -2) || (2 >= bal));
    return bal;
}


/**
 * avl_nodo_rotacion_simple_izq: Funcion interna que realiza una rotacion simple
 * a izquierda y retorna la nueva raiz.
 */
static AVL_Nodo* avl_nodo_rotacion_simple_izq(AVL_Nodo* raiz){
    AVL_Nodo* hijoDerecho= raiz->der;
    assert( hijoDerecho!= NULL);

    raiz->der= hijoDerecho->izq;
    hijoDerecho->izq = raiz;

    raiz->altura= 1 + avl_nodo_max_altura_hijos(raiz);
    hijoDerecho->altura = 1 + avl_nodo_altura(hijoDerecho);
    return hijoDerecho;
}


/**
 * avl_nodo_rotacion_simple_der: Funcion interna que realiza una rotacion simple
 * a derecha y retorna la nueva raiz.
 */
static AVL_Nodo* avl_nodo_rotacion_simple_der(AVL_Nodo* raiz){

    assert(raiz->izq != NULL);
    AVL_Nodo* hijoIzq= raiz->izq;

    raiz->izq= hijoIzq->der;
    hijoIzq->der= raiz;

    raiz->altura= 1 + avl_nodo_max_altura_hijos(raiz);
    hijoIzq->altura= 1 + avl_nodo_max_altura_hijos(hijoIzq);
    return hijoIzq;
}



/**
 * avl_nodo_crear: Funcion interna que crea un nuevo nodo y lo retorna.
 * La altura de un nodo hoja es 0.
 */
static AVL_Nodo* avl_nodo_crear(void* dato, FuncionCopiadora copia){

    AVL_Nodo* nuevoNodo= malloc(sizeof(AVL_Nodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->altura= 0;
    nuevoNodo->balance= 0;
    nuevoNodo->dato= copia(dato);
    nuevoNodo->der= nuevoNodo->izq= NULL;

    return nuevoNodo;
}



/**
 * avl_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad de los arboles AVL.
 */
static AVL_Nodo* avl_nodo_insertar(AVL_Nodo* raiz, void* dato,
  FuncionCopiadora copia, FuncionComparadora comp){
    
    if(raiz == NULL){
        return avl_nodo_crear(dato, copia);
    }
    else if(comp(dato,raiz->dato)<0){
        raiz->izq= avl_nodo_insertar(raiz->izq, dato, copia,comp);

        //chequeo balance
        if(avl_nodo_factor_balance(raiz) == -2){
            
            if(avl_nodo_factor_balance(raiz->izq) == 1)//desbalance generado por incersion interna
            {
                raiz->izq= avl_nodo_rotacion_simple_izq(raiz->izq);
            
            }
            raiz= avl_nodo_rotacion_simple_der(raiz);
        
        }
        raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);

        return raiz;
    }
    else if(comp(dato, raiz->dato)>0){
        raiz->der= avl_nodo_insertar(raiz->der,dato, copia, comp);

        if(avl_nodo_factor_balance(raiz) == 2) //pesado en la derecha
        {
            if(avl_nodo_factor_balance(raiz->der) == -1)//insercion interna, pesado a la izq
            {
                raiz->der= avl_nodo_rotacion_simple_der(raiz->der);
            }
            raiz= avl_nodo_rotacion_simple_izq(raiz);
        }
        raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
        return raiz;
    }
    else{
        return raiz;
    }

  }

void avl_insertar(AVL arbol, void* dato){
    arbol->raiz= avl_nodo_insertar(arbol->raiz, dato, arbol->copia, arbol->comp);
}


/**
 * avl_validar: Retorna 1 si el arbol cumple la propiedad de los arboles AVL,
 * y 0 en caso contrario.
 * avl_nodo_validar_abb: Funcion interna que retorna 1 si el arbol cumple la
 * propiedad de los arboles BB, y 0 en caso contrario.
 * avl_nodo_validar_altura_y_balance: Funcion interna que retorna 1 si la
 * altura y el factor de balance de los nodos son correctos, y 0 en caso
 * contrario.
 */
static int avl_nodo_validar_abb(AVL_Nodo* raiz, void* min, void* max,
  FuncionComparadora comp){

 // si la raiz es vacia, retornar exitosamente
  if (raiz == NULL)
    return 1;
  else {
    // sino, validar intervalo
    if (min != NULL && comp(raiz->dato, min) <= 0)
      return 0;
    if (max != NULL && comp(max, raiz->dato) <= 0)
      return 0;
    // y validar subarboles recursivamente
    return (avl_nodo_validar_abb(raiz->izq, min, raiz->dato, comp) &&
      avl_nodo_validar_abb(raiz->der, raiz->dato, max, comp));
  }
}


static int avl_nodo_validar_altura_y_balance(AVL_Nodo* raiz){

    if(raiz == NULL)
        return 1;
    
    int izq= avl_nodo_validar_altura_y_balance(raiz->izq);
    int der= avl_nodo_validar_altura_y_balance(raiz->der);

    if(izq && der){
        int altura= 1 + avl_nodo_max_altura_hijos(raiz);
        int balance= avl_nodo_factor_balance(raiz);

        if((altura == raiz->altura) && (-1 <= balance) && (balance <= 1)){
            return 1;
        }
    }
    return 0;
}

int avl_validar(AVL arbol){

    return  avl_nodo_validar_abb(arbol->raiz ,NULL, NULL, arbol->comp ) && 
      avl_nodo_validar_altura_y_balance( arbol->raiz);
}


/**
 * avl_recorrer: Recorrido DSF del arbol
 */
static void avl_nodo_recorrer(AVL_Nodo* raiz, AVLRecorrido orden,
  FuncionVisitanteExtra visita, void* extra){

    
    if(raiz != NULL){
    if(orden == AVL_RECORRIDO_PRE){
        visita(raiz->dato, extra);
    }
    avl_nodo_recorrer(raiz->izq, orden, visita, extra);
    if(orden == AVL_RECORRIDO_IN){
        visita(raiz->dato, extra);
    }
    avl_nodo_recorrer(raiz->der, orden, visita, extra);
    if(orden == AVL_RECORRIDO_POST){
        visita(raiz->dato, extra);
    }
}
}

void avl_recorrer(AVL arbol, AVLRecorrido orden, FuncionVisitanteExtra visita,
  void* extra){
    avl_nodo_recorrer(arbol->raiz, orden, visita, extra);
}

/**
 * elima un dato del arbol manteniendo su propiedad de avl
 */

static AVL_Nodo* avl_minimo_derecho(AVL_Nodo* raiz){
    if(raiz == NULL) return NULL;
    AVL_Nodo* nodo= raiz->der;
    AVL_Nodo* nodoAnterior= raiz;
    while(nodo->izq != NULL){
        nodoAnterior=nodo;
        nodo= nodo->izq;
    }
    (void)raiz;
    return nodo;
}
static AVL_Nodo* avl_balancear(AVL_Nodo* raiz){
    
        //chequeo balance
        if(avl_nodo_factor_balance(raiz) == -2){
            
            if(avl_nodo_factor_balance(raiz->izq) == 1)//desbalance generado por incersion interna
            {
                raiz->izq= avl_nodo_rotacion_simple_izq(raiz->izq);
            
            }
            raiz= avl_nodo_rotacion_simple_der(raiz);
            
        }
        

        else if(avl_nodo_factor_balance(raiz) == 2) //pesado en la derecha
        {
            if(avl_nodo_factor_balance(raiz->der) == -1)//insercion interna, pesado a la izq
            {
                raiz->der= avl_nodo_rotacion_simple_der(raiz->der);
            }
            raiz= avl_nodo_rotacion_simple_izq(raiz);
        }
        raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
    return raiz;
}

static AVL_Nodo* avl_nodo_eliminar(AVL_Nodo* raiz, void* dato, FuncionDestructora destr, FuncionComparadora comp,
    FuncionCopiadora copia){
   
    if(raiz == NULL) return NULL;
    
    if(comp(dato, raiz->dato)<0)//dato<arbol->dato
    {
        raiz->izq= avl_nodo_eliminar(raiz->izq, dato,destr, comp, copia);
    }
    else if(comp(dato, raiz->dato) > 0){
        
        raiz->der= avl_nodo_eliminar(raiz->der, dato,destr , comp, copia);
       
    }
    else{
        if(raiz->der == NULL || raiz->izq == NULL){// el nodo a eliminar es una hoja
            //o tiene un solo hijo
           
            AVL_Nodo* sucesor= raiz->der == NULL?raiz->izq:raiz->der;
            printf("dato %d\n", *(int*)raiz->dato);
            destr(raiz->dato);
            free(raiz);
            return sucesor;


        }
        else{
            //el nodo a eliminar tiene dos hijos;
            AVL_Nodo* menor= avl_minimo_derecho(raiz);
            printf("dato %d\n", *(int*)raiz->dato);
            destr(raiz->dato);
            raiz->dato= copia(menor->dato);
            printf("dato %d\n", *(int*)raiz->dato);
            raiz->der= avl_nodo_eliminar(raiz->der, menor->dato, destr, comp, copia);
            
            (void)menor;
            return raiz;
        }

    }
    
    return avl_balancear(raiz);
}

void avl_eliminar(AVL arbol, void* dato){
   arbol->raiz= avl_nodo_eliminar(arbol->raiz, dato, arbol->destr, arbol->comp, arbol->copia);
  
}

