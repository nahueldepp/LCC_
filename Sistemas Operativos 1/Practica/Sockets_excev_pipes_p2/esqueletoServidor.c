//Servidor de turnos

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/shm.h>
#include <semaphore.h>
#define TAM_MEMORIA 1024

/*
 * Para probar, usar netcat. Ej:
 *
 *      $ nc localhost 4040
 *      NUEVO
 *      0
 *      NUEVO
 *      1
 *      CHAU
 */

void quit(char *s)
{
	perror(s);
	abort();
}

int U = 0;

int fd_readline(int fd, char *buf)
{
	int rc;
	int i = 0;

	/*
	 * Leemos de a un caracter (no muy eficiente...) hasta
	 * completar una línea.
	 */
	while ((rc = read(fd, buf + i, 1)) > 0) {
		if (buf[i] == '\n')
			break;
		i++;
	}

	if (rc < 0)
		return rc;
	if (i > 0 && buf[i - 1] == '\r')
        i--;
	
	buf[i] = 0;
	return i;
}

void handle_conn(int csock, int* shmI)
{
	char buf[200];
	int rc;

	while (1) {
		/* Atendemos pedidos, uno por linea */
		rc = fd_readline(csock, buf);
		if (rc < 0)
			quit("read... raro");

		if (rc == 0) {
			/* linea vacia, se cerró la conexión */
			close(csock);
			return;
		}

		if (!strcmp(buf, "NUEVO")) {
			char reply[20];
			sprintf(reply, "%d\n", *shmI);
			(*shmI)++;
			write(csock, reply, strlen(reply));

		} else if (!strcmp(buf, "CHAU")) {
			
			write(csock, buf, strlen(buf));
			
			close(csock);
			return;
		}
	}
}

void wait_for_clients(int lsock, int* shmI)
{
	int csock;
	pid_t pid;

	
	while(1){ 

		/* Esperamos una conexión, no nos interesa de donde viene */
		csock = accept(lsock, NULL, NULL);// devuelve un client socket, para hablar con un cliente en concreto
		if (csock < 0)
			quit("accept");
		else{
			pid = fork();

			if(pid < 0){
				perror("fork");
				exit(EXIT_FAILURE);
			}

			if(pid == 0){
				sleep(1);
				/*el hijo no necesita al socket de escucha, no es él el que acepta conexiones*/
				close(lsock);
				/* Atendemos al cliente */
				
				handle_conn(csock, shmI);
				close(csock);
				exit(EXIT_SUCCESS);
			}
			/*Como el padre no atiende al cliente y solo espera, luego sigue atendiendo otros clientes */
			close(csock);
			
		}
	}

}

/* Crea un socket de escucha en puerto 4040 TCP */
int mk_lsock()
{
	struct sockaddr_in sa;
	int lsock;
	int rc;
	int yes = 1;


	/* Crear socket */
	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if (lsock < 0)
		quit("socket");

	/* Setear opción reuseaddr... normalmente no es necesario */
	if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
		quit("setsockopt");

	sa.sin_family = AF_INET;
	sa.sin_port = htons(4040);//"host network short" convierte el número de formato maquina a formato red
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Bindear al puerto 4040 TCP, en todas las direcciones disponibles */
	rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
	if (rc < 0)
		quit("bind");

	/* Setear en modo escucha */
	rc = listen(lsock, 10);
	if (rc < 0)
		quit("listen");

	return lsock;
}

int main()
{
	
	/*Memoria compartida entre process*/
	key_t clave = ftok("shmfile", 65); // Clave única
    int shmid = shmget(clave, TAM_MEMORIA, 0666 | IPC_CREAT); // Crear segmento de memoria
	int * shmI = (int*)shmat(shmid, NULL, 0);
	if (shmid < 0) {
		perror("Error al crear memoria compartida");
		exit(1);
	}
	*shmI = 0;
	signal(SIGCHLD, SIG_IGN);
	int lsock;
	lsock = mk_lsock();
	wait_for_clients(lsock, shmI);
	// Eliminar la memoria compartida
	shmctl(shmid, IPC_RMID, NULL);
}