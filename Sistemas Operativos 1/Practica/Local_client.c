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

/*Cliente Echo */

#define MSG "HOLA MUNDO\n"


int main(void){

    ssize_t nbytes;
    char buffer[MAXMSG];

    int sockfd;
    struct sockaddr_un srvAddr;
    struct sockaddr_un cliAddr;
    socklen_t srvSize = sizeof(srvAddr);

    /*Creación del socket */
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if(sockfd < 0){
        perror("Error en la creación del socket");
        exit(EXIT_FAILURE);
    }

    /*Estructura de la dirección del socket*/
    cliAddr.sun_family = AF_UNIX;
    strncpy(cliAddr.sun_path, CLI_NOMBRE, sizeof(cliAddr.sun_path));

    unlink(CLI_NOMBRE);
    
    /*Asignacion del nombre*/

    if(bind(sockfd, (struct sockaddr*)&cliAddr, sizeof(cliAddr)) < 0){
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    /*nombre/dirección del servidor*/
    srvAddr.sun_family = AF_UNIX;
    strncpy(srvAddr.sun_path, SRV_NOMBRE, sizeof(srvAddr.sun_path));

    /*Llenamos el buffer*/

    strcpy(buffer, MSG);

    nbytes = sendto(sockfd, buffer, strlen(buffer)+1, 0, (struct sockaddr*)&srvAddr, srvSize);
    if(nbytes < 0){
        perror("sendto error");
        exit(EXIT_FAILURE);
    }

    printf("SEND: OK\n");

    /*Nos quedamos a la espera de la respuesta del servidor*/

    nbytes = recvfrom(sockfd, buffer, MAXMSG-1, 0, (struct sockaddr*)&srvAddr, &srvSize);
    if(nbytes < 0){
        perror("recvfrom erro");
        exit(EXIT_FAILURE);
    }
    printf("RECV: %s\n", buffer);
    /************************ */
    close(sockfd);
    unlink(CLI_NOMBRE);

    return EXIT_SUCCESS;
}