/*
Servidor usando sockets.
Dominio: local
Tipo de señales: Datagramas
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include "8.0-socket_server_configuration.h"

//socket server Echo datagrama

int main(void){

    int sockfd; 
    struct sockaddr_un srvAddr; 
    struct sockaddr_un cliAddr;
    socklen_t cliSize = sizeof(cliAddr);
    ssize_t nbytes; //largo del mensaje recibido
    char buffer[MAXMSG];

    /*Creación del socket*/
    sockfd = socket(AF_UNIX, SOCK_DGRAM,0 );
    if(sockfd < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Socket creado\n");

    /*Creamos la estructura de la dirección del socket */
    srvAddr.sun_family = AF_UNIX;
    strncpy(srvAddr.sun_path, SRV_NOMBRE, sizeof(srvAddr.sun_path)); //path

    //remueve el socket adress path si ya esta usado
    unlink(SRV_NOMBRE);
    
    /*Asignación de nombre*/
    if(bind(sockfd, (struct sockaddr*)&srvAddr,sizeof(srvAddr)) < 0){
        perror("Bind");
        exit(EXIT_FAILURE);
    }

    /*Respondo al echo del cliente*/
    nbytes = recvfrom(sockfd, buffer, MAXMSG-1, 0, (struct sockaddr*) &cliAddr, &cliSize);//recibo del cliente

    if(nbytes < 0){
        perror("recvfrom");
        unlink(SRV_NOMBRE);
        exit(EXIT_FAILURE);
    }

    printf("RECV: %s\n", buffer);

    /*responder al echo*/

    nbytes = sendto(sockfd, buffer, MAXMSG-1,0, (struct sockaddr*)&cliAddr,cliSize ); //mando al cliente
    if(nbytes < 0){
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    printf("SEND: OK\n");

    /****************************** */
    close(sockfd);
    unlink(SRV_NOMBRE);
    return EXIT_SUCCESS;
}