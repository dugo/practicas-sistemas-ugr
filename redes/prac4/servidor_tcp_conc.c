/*************************************************************************
  09-01-2008: Rubén Dugo
  - Servidor de frases TCP concurrente: recibe solicitudes de frases con un nombre y devuelve frases con el nombre solicitado.
  - Uso: ./servidor_tcp_conc <puerto_servicio>
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "frases.h"

#define MAX_CONEXIONES 1000

//Mi tipo cabecera
typedef struct
{
	char orden[5];

	unsigned char longitud;
	char nombre[256];

} mi_cabecera ;

int main(int argc, char **argv)
{

	//Comprobamos parámetros
	if(argc!=2)
	{
		fprintf(stderr,"Uso: %s <puerto>\n",argv[0]);
		return EXIT_FAILURE;
	}


	//Variables para sockets y demás historias
	struct sockaddr_in cliente, servidor;
	unsigned int puerto;
	int pid,sd, nuevo_sd, salir, longitud, st;
	socklen_t tam_sockcliente = sizeof(cliente);
	char comando[5], buffer[255];
	mi_cabecera cabecera;

	//Cogemos los parámetros
	puerto = atoi(argv[1]);	

	//Apertura y configuración del socket
	if ((sd = socket (AF_INET, SOCK_STREAM, 0))<0)
	{
		perror("Error abriendo socket");
		return EXIT_FAILURE;
	}

	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;
	servidor.sin_port = htons(puerto);

	if (bind ( sd, (struct sockaddr *)&servidor, sizeof (servidor) ) <0)
	{
		perror("Error en la funcion bind");
		return EXIT_FAILURE;
	}

	if (listen ( sd, MAX_CONEXIONES )<0)
	{
		perror("Error en la funcion listen");
		return EXIT_FAILURE;
	}


	printf("\n[Padre] Servidor TCP concurrente listo para procesar las peticiones.\n\n");

	salir = 0;

	//Bucle para procesar las solicitudes
	while (!salir)
	{

		if ((nuevo_sd = accept(sd, (struct sockaddr*)&cliente, &tam_sockcliente))<0)
		{
			perror("Error aceptando solicitud");
			return EXIT_FAILURE;
		}

		//Creo el hijo
		if ((pid = fork()) < 0)
		{
			perror("Error creando proceso hijo");
			return EXIT_FAILURE;
		}

		//Si soy un proceso hijo trato la solicitud
		if (pid==0)
		{

			//Semilla aleatoria en el hijo
			srand(time(NULL));

			//Recibo el comando
			if ((longitud = recv(nuevo_sd, (char*)&comando, 5, MSG_PEEK)) < 0 )
			{
				perror("Error recibiendo la peticion");
				return EXIT_FAILURE;
			}

			// ¿Acabamos?
			if(strncasecmp(comando,"fin",3)==0)
			{
				printf("\t[Hijo %d] Recibido el comando fin. Finalizando...\n",getpid());

				if (shutdown(nuevo_sd, SHUT_RDWR)<0 || close(sd)<0)
				{
					perror("Error cerrando la conexion");
					return EXIT_FAILURE;
				}

				salir=1;
				return EXIT_FAILURE;
			}
			else if (strncasecmp(comando,"frase",5)==0) //¿Envio frase?
			{

				//Recibo el paquete completo
				if (recv(nuevo_sd, (char*)&cabecera, sizeof(cabecera), 0) < 0)
				{
					perror("Error recibiendo datos: ");
					return EXIT_FAILURE;
				}

				cabecera.nombre[cabecera.longitud] = 0;

				longitud = sprintf(buffer,frases[rand()%NFRASES],cabecera.nombre);
				buffer[longitud]='\0';

				//Envio
				if (sendto(nuevo_sd, buffer, longitud, 0, (struct sockaddr*)&cliente, sizeof(cliente) ) < 0 )
				{
					perror("Error enviando respuesta");
					return EXIT_FAILURE;
				}

				printf("[Hijo %d] Enviado:\n%s\n",getpid(),buffer);

				if (shutdown(nuevo_sd, SHUT_RDWR)<0)
				{
					perror("Error cerrando la conexion");
					return EXIT_FAILURE;
				}
			}
			else
			{
				printf("\t[Hijo %d] No entiendo el comando \"%s\".\n",getpid(),comando);

				if (shutdown(nuevo_sd, SHUT_RDWR)<0)
				{
					perror("Error cerrando la conexion");
					return EXIT_FAILURE;
				}
			}

			//Si soy un proceso hijo me cierro
			return EXIT_SUCCESS;
		}
		else
		{
			wait(&st);
			//Si el hijo me dice que cierre, me cierro
			if (st)
			{
				printf("\n[Padre] Cerrado el servidor TCP por el hijo %d.\n",pid);
				salir=1;
			}
		}
	}

	return EXIT_SUCCESS;
}

