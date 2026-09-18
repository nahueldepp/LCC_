#include<stdio.h>
#include<assert.h>


#define LARGO 12 // largo de la lista de alturas
double aAlturas[]={1.95,1.89,1.88,1.86,1.86,2.0,2.0,2.0,2.0,2.07,2.09,2.12};


//1-Promedio aritmetico e la altura del parana
//2-¿Cual es la altura maxima registrada?
//3-Calculo de la moda: El conjunto de datos puede tener una sola moda,ser multimodal o no tener moda
//la moda es el valor que mas se repite.


//-----------Prototipos-----------------------
double promedio(double array[]);
double altura_maxima(double array[]);
int en_lista(double valor,double l_sin_rep[]);
void lista_sin_repes(double l_original[],double l_sin_rep[] );
void moda(double arr[]);
//--------------------------------------------
int main(){

    double prom=promedio(aAlturas);
    printf("El promedio aritmetico de las alturas del parana es: %0.2f\n",prom);

    float aMax=altura_maxima(aAlturas);
    printf("La altura maxima registrada es de %0.2f\n",aMax);

    
    moda(aAlturas);

    

}

//1
//promedio:double[]->double
//toma un array de reales y devuelve su promedio 
double promedio(double array[]){

    double prom=0;

    for(int i=0;i<=LARGO;i++){
        prom+=array[i];
    }
    return prom/LARGO;

}

//2

//altura_maxima: double[]->double
//dada una lista de alturas devuelve la altura maxima 
double altura_maxima(double array[]){

    double aMaxima=array[0];

    for(int i=0;i<LARGO;i++){
        if (array[i]>=aMaxima){
            aMaxima=array[i];
        }
    }

    return aMaxima;
}

//en_lista:double,double[]->bool
int en_lista(double valor,double l_sin_rep[]){

    for(int i=0;i<LARGO;i++){
        if(l_sin_rep[i]==valor){
            return 1;
        }
    }
    return 0;
} 
//lista_sin_repes:double[], double[]->void
//toma una lista de valores y una lista vacia, completa la lista vacia con los valores distintos(sin repeticones),
//de la lista original
void lista_sin_repes(double l_original[],double l_sin_rep[] ){

    //se inicializa todos los elementos de aAlturas en -1 para evitar basura en los siguientes procedimientos
    
    for(int i=0;i<LARGO;i++){
        l_sin_rep[i]=-1;
    }

    int j=0;
    for(j;j<LARGO;j++){
        for(int i=0;i<LARGO;i++){
            if(en_lista(l_original[i],l_sin_rep)==0){
                l_sin_rep[j]=l_original[i];
            }
        }
    }  
}


// moda:double[]->void
//imprime en pantalla los tipos de moda y sus valores y cantidad de aparicones

void moda(double arr[]){

    double l_sin_rep[LARGO];
    lista_sin_repes(arr,l_sin_rep);

    int rep_max=0,rep_max2;
    int indice_v_max=0,indice_v_max2;
    int i=0;
    for(i;l_sin_rep[i]!=-1;i++){
        int k=0;
        
        for(int valor=0;valor<LARGO;valor++){
            if(l_sin_rep[i]==arr[valor]){
                k+=1;
            }
        }
        if (k>=rep_max){
            rep_max2=rep_max;
            rep_max=k;

            indice_v_max2=indice_v_max;
            indice_v_max=i;
            
        }
        
    }

    if(rep_max==1){
        printf("El conjunto de datos es amodal\n");
    }
    else if (rep_max2==rep_max)
    {
        printf("El conjunto de datos es bimodal, los valores q más se repiten son: %0.2f y %0.2f, %d veces\n",
        l_sin_rep[indice_v_max],l_sin_rep[indice_v_max2],rep_max);
    }
    else{
        printf("La moda del conjunto es %0.2f,que se repite %d veces\n",l_sin_rep[indice_v_max],rep_max);
    }
    

}

