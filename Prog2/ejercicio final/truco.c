#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

/*Ejercicio 10. Suponga que tiene que implementar un juego que requiere utilizar un mazo de
cartas. Implemente los siguientes puntos para crear una representación del mismo que luego
a) Defina una estructura Carta para representar una carta de la baraja española (represente
el palo con una enumeración).
b) Cree un arreglo de 48 cartas, llámelo mazo y llénelo con las cartas correspondientes.
c) Implemente una función struct Carta azar(struct Carta[], int) que reciba un mazo
y la longitud del mismo y devuelva una carta al azar del mazo pasado.
*/

/*En este programa se tratara de recrear una partida de truco entre dos personas*/

typedef struct
{
    char palo;// los palos se representaran como O(oro),B(Basto),E(espada),C(copa)
    short unsigned int valor; // los valores iran del 1 al 12
}Carta;

//------------------------------ //
void crear_mazo(Carta *mazo);
Carta repartir_carta(Carta* mazo );
int juego_valido(Carta juego[]);
void repartir_manos(Carta mazo[], Carta manoj1[],Carta manoj2[]);
void ordenar_cartas(Carta mazo[], Carta mazo_ordenado[]);
int comparacion(const void* a, const void* b);

//------------------------------//
void main(void){
srand(time(NULL));
Carta mazo[40];
crear_mazo(mazo);
Carta mazo_ordenado[40];
ordenar_cartas(mazo,mazo_ordenado);
Carta manoj1[3];
Carta manoj2[3];



repartir_manos(mazo,manoj1,manoj2);


 for(int i=0;i<6;i++){
    if(i<3){
        printf("%c,%d\n",manoj1[i].palo,manoj1[i].valor);
    }
    /* else{
        printf("%c,%d\n",manoj2[i-3].palo,manoj2[i-3].valor);
    } */
}  





}



//#############################Repartir las manos ################################################
/*crear_mazo:void->Carta
toma una lista vacia y devuelve un mazo de cartas de la baraja francesa*/
void crear_mazo(Carta *mazo){
    char palos[4]={'O','E','C','B'};
    short unsigned int valores[10]={1,2,3,4,5,6,7,10,11,12};
    
    
    int n_carta=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<10;j++){
            mazo[n_carta].palo=palos[i];
            mazo[n_carta].valor=valores[j];
            n_carta++;
        }

    }
    
    

    
}

/*repartir_carta: Carta[]-> Carta
Dada un lista de cartas(mazo) devueve una carta al azar del mismo*/

Carta repartir_carta(Carta* mazo ) {

    return mazo[(rand()%41)];
}

/*juego_valido:Carta[]->int
Dado un juego de cartas, devuelve 0 si las cartas son distintas*/
int juego_valido(Carta juego[]){

    
    for(int j=0;j<6;j++){
        for(int i=j+1;i<6;i++){
            if((juego[j].palo==juego[i].palo)&&(juego[j].valor==juego[i].valor)){
                return -1;
            }
        }
    }
    return 0;
}

/*repartir_manos: Carta[] Carta[] Carta[]->Void
repartir manos recibe un mazo, y dos manos vacias (a repartir), devuelve las dos manos con Cartas distintas*/
void repartir_manos(Carta mazo[], Carta manoj1[],Carta manoj2[]){

    
    Carta juego[6];
    //asigna valores a las manos a repartir

    for(int i=0;i<6;i++){
        Carta c;
        c=repartir_carta(mazo);
        
        juego[i].palo=c.palo;
        juego[i].valor=c.valor;
        
    }
     
     //hasta que los valores no sean distintos, sigue repartiendo
    while(juego_valido(juego)==-1){
        srand(time(NULL));
        for(int i=0;i<6;i++){
            Carta c;
            c=repartir_carta(mazo);
            
            juego[i].palo=c.palo;
            juego[i].valor=c.valor;
            
        }
        
    }

    //asigna las manos
    for(int j=0;j<6;j++){
        if(j<3){
            manoj1[j]=juego[j];
        }
        else{
            manoj2[j-3]=juego[j];
        }
    }

}

int comparacion(const void* a, const void* b){
    Carta * c1=(Carta *)a;
    Carta *c2=(Carta *)b;
    return c1->valor-c2->valor;
}

/*ordenar_cartas: Cartas[] Carta[]->Void
Dado un mazo de cartas, las ordena por el valor de la carta de izquierda a derecha, estando a las derecha las cartas mas bajas
y a la izquierda las mas altas*/

void ordenar_cartas(Carta mazo[], Carta mazo_ordenado[]){

    
    Carta bajos[26];// 4s,5s,6s,7ś,10s,11s,12s
    Carta falsos[2];//anchos falsos
    Carta dos[4];//los dos's
    Carta tres[4];
    Carta sietes[2];
    Carta anchos[2];

    //intermedios
    int k=0;
    for(int i=0;i<40;i++){
        
        if((4<=mazo[i].valor<=12)&& (!((mazo[i].valor=7)&& ((mazo[i].palo=='E')||(mazo[i].palo=='O'))))){
            bajos[k].palo=mazo[i].palo;
            bajos[k].valor=mazo[i].valor;
            printf("%c,%d\n",bajos[k].palo,bajos[k].valor);
            k++;
        }
    }
    //ordeno los intermedios

    qsort(bajos,26,sizeof(Carta),comparacion);

    /* for (int i = 0; i < 26; i++)
    {
        printf("%c,%d\n",bajos[i].palo,bajos[i].valor);
    } */
    
}   


//############################Funcionamiento del juego######################################

//Aquie estaran las funciones que controlan las cartas y las declaraciones de las jugadas, como truco,rectruco,vale cuatro
//envido, real envido, falta envido
//Estas funciones seran por ejemplo: int ganar_mano(Carta j1,Carta j2), donde la carta mas alta gana la mano

/* int ganar_mano(Carta j1,Carta j2){
    if
} */