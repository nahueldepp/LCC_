#include "avl.h"
#include "tablahash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * estructura de un consumo, guarda los datos de la fecha, el monto consumido y el cliente
 * guarda un puntero al consumo siguiente de cada Cliente
 */
typedef struct  _consumo {
    int dd,mm,aaaa;
    unsigned montoConsumido;
    char* clienteDNI;
    struct _consumo* sig;
}* Consumo;
/**
 * Estructura del cliente
 * Guarda los datos personales del cliente y un puntero a un lista de consumos realizados por el mismo
 */
typedef struct _cliente{
    char* nombre,*apellido,*direccion,*DNI, *telefono;
    unsigned montoConsumidoTotal;
    Consumo listaDeconsumos;
}* Cliente;

/**
 * Estructura que guarda el monto COnsumido total de cada cliente identificandolo por su DNI
 */
typedef struct _CPC{
    char* DNI;
    unsigned montoConsumidoTotal;
}* CPC;//Consumo Por Cliente

typedef struct _CLientesEnRango{
    CPC* clientesCPC;
    unsigned numClientesEnRango;
}*   CLientesEnRango;

CPC cpc_copia(CPC cpc){
    CPC copiaCPC= malloc(sizeof(struct _CPC));
    copiaCPC->DNI= malloc(sizeof(char)*(strlen(cpc->DNI)+1));
    strcpy(copiaCPC->DNI,cpc->DNI);
    copiaCPC->montoConsumidoTotal= cpc->montoConsumidoTotal;
    return copiaCPC;
}


void cpc_destruir(CPC cpc){
    free(cpc->DNI);
    free(cpc);
    return;
}
/**
 * Funcion que compara el CPC por monto consumido total
 * 0 si son iguales
 * <0 si cpc1<cpc2
 * >0 si cpc1>cpc2
 */
int cpc_comparar(CPC cpc1,CPC cpc2){
    int consumo= (int)cpc1->montoConsumidoTotal -(int) cpc2->montoConsumidoTotal;
    if(consumo == 0){
        int dni= strcmp(cpc1->DNI,cpc2->DNI);
        return dni;
    }
    return consumo;
}

void cpc_imprimir(CPC cpc){
    printf("DNI: %s\nMonto: %d\n",cpc->DNI,cpc->montoConsumidoTotal);
    puts("");
}
/**
 * Retorna un puntero a una copia fisica de uana estructura _consumo
 */
Consumo consumo_copia(Consumo c){
    Consumo consumoCopia= malloc(sizeof(struct _consumo));
    consumoCopia->dd= c->dd;
    consumoCopia->mm= c->mm;
    consumoCopia->aaaa= c->aaaa;
    consumoCopia->montoConsumido= c->montoConsumido;
    consumoCopia->clienteDNI= malloc(sizeof(char)*(strlen(c->clienteDNI)));
    strcpy(consumoCopia->clienteDNI, c->clienteDNI);
    consumoCopia->sig= c->sig;
    return consumoCopia;
}


void consumo_destruir(Consumo lista){
    if(lista == NULL)
        return;
    Consumo consumoAdestruir= lista;
    lista= lista->sig;
    free(consumoAdestruir->clienteDNI);
    free(consumoAdestruir);
    consumo_destruir(lista);
    return;
}

/**
 * compara consumos segun su montoConsumido, 
 * retorna 0 si los monstosConsumido son iguales
 * <0 si c1<c2
 * >0 si c1>c2
 *  */
int consumo_comparar(Consumo c1, Consumo c2){
    return c1->montoConsumido - (int)c2->montoConsumido;
}

void consumo_imprimir(Consumo c){
    printf("fecha: %d/%d/%d\nMonto consumido: %d\nDNI del cliente: %s",c->dd,c->mm,c->aaaa,c->montoConsumido,c->clienteDNI);
}

/**
 * Retorna una copia fisica de un cliente
 */
Cliente cliente_copia(Cliente cliente){

    Cliente clienteCopia= malloc(sizeof(struct _cliente));
    //se cre el espacio para las copias de las caracteristicas de un cliente
    clienteCopia->apellido= malloc(sizeof(char)*(strlen(cliente->apellido)+1));
    clienteCopia->nombre= malloc(sizeof(char)*(strlen(cliente->nombre)+1));
    clienteCopia->direccion= malloc(sizeof(char)*(strlen(cliente->direccion)+1));
    clienteCopia->DNI= malloc(sizeof(char)*(strlen(cliente->DNI)+1));
    clienteCopia->telefono= malloc(sizeof(char)*(strlen(cliente->telefono)+1));

    strcpy(clienteCopia->apellido, cliente->apellido);
    strcpy(clienteCopia->nombre,cliente->nombre);
    strcpy(clienteCopia->direccion,cliente->direccion);
    strcpy(clienteCopia->DNI,cliente->DNI);
    strcpy(clienteCopia->telefono, cliente->telefono);

    clienteCopia->montoConsumidoTotal = cliente->montoConsumidoTotal;

    return clienteCopia;
}

void cliente_destruir(Cliente cliente){
    free(cliente->apellido);
    free(cliente->nombre);
    free(cliente->telefono);
    free(cliente->direccion);
    free(cliente->DNI);
    consumo_destruir(cliente->listaDeconsumos);
    free(cliente);
    return;
}

/**
 * Funcion que compara los clientes por su DNI
 * 
 */
int cliente_comparar(Cliente c1, Cliente c2){
    return strcmp(c1->DNI, c2->DNI);
}


/**
 * retorna un hashval usando el DNI del cliente
 */

unsigned cliente_hash(Cliente cliente){
    unsigned hashVal=0;
    char* c= cliente->DNI;
    for(hashVal;*c != '\0'; c++){
        hashVal= *c + 31*hashVal;
    }
    return hashVal;
}

void cliente_imprimir(Cliente c){
    printf("Nombre: %s\n",c->nombre);
    printf("Apellido: %s\n",c->apellido);
    printf("Telefono: %s\n",c->telefono);
    printf("Dirección: %s\n",c->direccion);
    printf("DNI: %s\n",c->DNI);
    printf("Monto Total Consumido: %d", c->montoConsumidoTotal);
}


/**
 * Dado un cliente retorna su consumo
 */
int cliente_consumo(TablaHash tablaClientes,char* DNI){
    struct _cliente dummy={.DNI= DNI};
    Cliente cliente= tablahash_buscar(tablaClientes, &dummy);
    if(cliente)
        return cliente->montoConsumidoTotal;
    else    
        return -1;
}


void imprimir_clientes(TablaHash tablaClientes){
    
    for(unsigned i= 0; i < tablaClientes->capacidad ; i++ ){
        if(tablaClientes->elems[i].dato!=NULL){
            printf("\n-----------------------------------\n");
            cliente_imprimir(tablaClientes->elems[i].dato);
            printf("\n-----------------------------------\n");
        }
    }
}

void nuevo_consumo(Consumo c, TablaHash clientesTabla, AVL arbol){
    struct _cliente dummyCliente={.DNI= c->clienteDNI};
    Cliente cliente= tablahash_buscar(clientesTabla,&dummyCliente);
    assert(cliente != NULL);
    //se agrega el nuevo consumo a la lista de consumos
    c->sig= cliente->listaDeconsumos;
    cliente->listaDeconsumos= c;
    //se elimina el nodo CPC con el monto consumido total desactualizado y se agrega uno actualizado
    struct _CPC dummyCpc= {.montoConsumidoTotal=cliente->montoConsumidoTotal,.DNI= cliente->DNI};
    //avl_eliminar(arbol,&dummyCpc);
    //se actualiza el monto total consumio por el cliente
    cliente->montoConsumidoTotal+= c->montoConsumido;
    dummyCpc.montoConsumidoTotal= cliente->montoConsumidoTotal;
    //se agrega el nuevo monto total consumido asociado al cliente
    avl_insertar(arbol,&dummyCpc);
}
/**
 * clientes_en_rango(AVL clientes,int min,int max,Cliente* clientesEnrango):
 *  Dado un arbol de clientes , un intervalo de montos y un array con una cantidad de clientes 
 */

void clientes_en_rango_aux(AVL_Nodo* raiz,void* min,void* max,CLientesEnRango datosEnrango, FuncionComparadora comp, FuncionCopiadora copi){

  if(raiz == NULL)
    return;
  //el dato del nodo esta en el intervalo [min,max]
  else if( comp(raiz->dato,min)>=0 && comp(raiz->dato,max)<=0){
    datosEnrango->clientesCPC[datosEnrango->numClientesEnRango++]= copi(raiz->dato);
    
    printf("cpcArbol monto %d",datosEnrango->clientesCPC[0]->montoConsumidoTotal);
    clientes_en_rango_aux( raiz->izq,min,max,datosEnrango, comp, copi);
    clientes_en_rango_aux( raiz->der,min,max,datosEnrango, comp, copi);
    printf("b\n");
  }
  else if(comp(raiz->dato,min)<0 && raiz->der){
    clientes_en_rango_aux( raiz->der,min,max,datosEnrango, comp, copi);
  }
  else if(comp(raiz->dato,max)>0 && raiz->izq)
    clientes_en_rango_aux( raiz->izq,min,max,datosEnrango, comp, copi);
  return;
}

void clientes_en_rango(AVL clientesCpc,unsigned min,unsigned max,CLientesEnRango clientesEnrango){
    struct _CPC dummyMenor= {.montoConsumidoTotal=min,.DNI="0"};
    struct _CPC dummyMayor= {.montoConsumidoTotal=max,.DNI="0"};
    clientes_en_rango_aux( clientesCpc->raiz,&dummyMenor,&dummyMayor,clientesEnrango, clientesCpc->comp,clientesCpc->copia);
    
}
int main(){
    TablaHash clientes= tablahash_crear(20, (FuncionCopiadora)cliente_copia,(FuncionComparadora)cliente_comparar,
    (FuncionDestructora)cliente_destruir,(FuncionHash)cliente_hash);
    AVL cpcArbol= avl_crear((FuncionCopiadora)cpc_copia,(FuncionComparadora)cpc_comparar,(FuncionDestructora)cpc_destruir);

    struct _cliente cliente1={.apellido="Perez",.nombre="Juan",.direccion="rep1",.telefono="123",.DNI="44441256",.montoConsumidoTotal=0};
    struct _cliente cliente2={.apellido="Schwartz",.nombre="Olivia",.direccion="rep2",.telefono="1233",.DNI="44441257",.montoConsumidoTotal=0};
    struct _cliente cliente3={.apellido="Parker",.nombre="Peter",.direccion="rep3",.telefono="124",.DNI="44441258",.montoConsumidoTotal=0};
    struct _cliente cliente4={.apellido="Antonio",.nombre="Estrella",.direccion="rep4",.telefono="124",.DNI="44441259",.montoConsumidoTotal=0};

    tablahash_insertar(clientes, &cliente1);
    tablahash_insertar(clientes, &cliente2);
    tablahash_insertar(clientes, &cliente3);
    tablahash_insertar(clientes, &cliente4);

    struct _consumo consumo2= {.aaaa=2002,.mm=12,.dd=15,.clienteDNI="44441257",.montoConsumido=56,.sig=NULL};
    struct _consumo consumo1= {.aaaa=2002,.mm=12,.dd=15,.clienteDNI="44441256",.montoConsumido=50,.sig=NULL};
    struct _consumo consumo3= {.aaaa=2002,.mm=12,.dd=15,.clienteDNI="44441258",.montoConsumido=49,.sig=NULL};
    struct _consumo consumo4= {.aaaa=2002,.mm=12,.dd=15,.clienteDNI="44441259",.montoConsumido=623,.sig=NULL};

    nuevo_consumo(&consumo1,clientes, cpcArbol);
    nuevo_consumo(&consumo2,clientes, cpcArbol);
    nuevo_consumo(&consumo3,clientes, cpcArbol);
    nuevo_consumo(&consumo4,clientes, cpcArbol);

    printf("Cliente:%s\nCPC: %d","44441258",cliente_consumo(clientes, "44441258"));
    
    imprimir_clientes(clientes);
    avl_recorrer(cpcArbol,AVL_RECORRIDO_IN,(FuncionVisitante)cpc_imprimir);
    CLientesEnRango rango= malloc(sizeof(struct _CLientesEnRango));
    rango->clientesCPC= malloc(sizeof(CPC)*20);
    rango->numClientesEnRango=0;

    
    clientes_en_rango( cpcArbol, 40, 60,rango);
    for(unsigned i= 0; i<rango->numClientesEnRango;i++){
        struct _cliente dummy={.DNI=rango->clientesCPC[i]->DNI};
        Cliente ctemp= tablahash_buscar(clientes,&dummy);
        cliente_imprimir(ctemp);
    }
    printf("%d", rango->numClientesEnRango);
}