#include <stdio.h>
#include <string.h>

#define LONG_NOM 30
#define LONG_TEL 20
#define LONG_MAX_CONT 100

//Cree una agenda de contactos

//---Estructuras---//
typedef struct 
{
    char nombre[LONG_NOM];
    char numTelefono[LONG_TEL];
    unsigned int edad;
}Contacto;

typedef struct
{
    Contacto contactos[LONG_MAX_CONT];
    unsigned int cantContactos ;
    
}Agenda;
//-----------------//

//

//crear_contacto:void->contacto
//al ser llamada pide por teclado los datos de una persona y crea un Contacto
Contacto crear_contacto(void){

    Contacto cont;

    printf("Nombre del contacto: \n");
    fgets(cont.nombre,sizeof(char)*LONG_NOM,stdin);
    cont.nombre[strlen(cont.nombre)-1]='\0';

    printf("Número del contacto: \n");
    fgets(cont.numTelefono,sizeof(char)*LONG_TEL,stdin);
    cont.numTelefono[strlen(cont.numTelefono)-1]='\0';

    printf("Edad del contacto: \n");
    scanf("%d",&cont.edad);

    return cont;
    
}


//actualizar_edadd:Contacto*->void
//dado un puntero a un contacto , pide una nueva edad por teclado
void actualizar_edad(Contacto* cont){
    printf("Nueva edad del contacto: \n");

    scanf("%i",&cont->edad);

}

//alta_contacto: *Agenda -> void
//dado un puntero a una Agenda, pide los datos de un nuevo Contacto y lo agrega a la lista
void alta_contacto(Agenda* agPtr){

    Contacto cont=crear_contacto();
    agPtr->contactos[agPtr->cantContactos]=cont;
    agPtr->cantContactos++;
    
}

//modificar_edad: Agenda* ->void
//Pide por teclado el nombre del contacto al cual se desea modificar su edad
 void modificar_edad(Agenda* agPtr){

    char nombreAbuscar[LONG_NOM];
    printf("Nombre del contacto a modificar edad: ");
    fgets(nombreAbuscar,sizeof(nombreAbuscar),stdin);
    nombreAbuscar[strlen(nombreAbuscar)-1]='\0';
    int i = 0;

    for(;(i < agPtr->cantContactos) && (strcmp(agPtr->contactos[i].nombre, nombreAbuscar)); i++){

    }
    if(i==agPtr->cantContactos){
        printf("El contacto ingresado no se encuentra en la lista\n");
    }
    else{
        actualizar_edad(agPtr->contactos + i);
    }
    
    

}

//imprimir_contactos: Agenda* -> void
//imprime en pantalla los datos de los contactos cargados
void imprimir_contactos(Agenda* agPtr){

    for(int i = 0; i < agPtr->cantContactos; i++){
        printf("Nombre: %s, Número: %s , Edad: %d\n",agPtr->contactos[i].nombre, agPtr->contactos[i].numTelefono, agPtr->contactos[i].edad);
    }
}
 

int main(){

    printf("Desea agregar un contacto?: s/n\n");
    char confirmacion;
    
    Agenda agenda;
    agenda.cantContactos=0;


    while ((confirmacion=getchar())=='s')
    {
        getchar();
        alta_contacto(&agenda);
        
        printf("Desea agregar otro contacto?: s/n\n");
        confirmacion=getchar();
    }
    imprimir_contactos(&agenda);

    printf("Desea modificar la edad de algun contacto? s/n:\n");
    getchar();

    while ((confirmacion=getchar())=='s'){
        getchar();
        modificar_edad(&agenda);

        printf("Desea modificar la edad de algun otro contacto? s/n:\n");
        confirmacion=getchar();
    }
    imprimir_contactos(&agenda);
    

    

    return 0;
}