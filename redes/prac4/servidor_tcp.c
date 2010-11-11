/*************************************************************************
  09-01-2008: Rubén Dugo
  - Servidor de frases TCP: recibe solicitudes de frases con un nombre y devuelve frases con el nombre solicitado.
  - Uso: ./servidor_tcp <puerto_servicio>
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "frases.h"

#define MAX_CONEXIONES 2

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
	int sd, nuevo_sd, salir, longitud;
	socklen_t tam_sockcliente = sizeof(cliente);
	char comando[5], buffer[255];
	mi_cabecera cabecera;

	//Cogemos los parámetros
	puerto = atoi(argv[1]);	

	//Semilla aleatoria
	srand(time(NULL));

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


	printf("\nServidor TCP listo para procesar las peticiones.\n\n");

	salir = 0;

	//Bucle para procesar las solicitudes
	while (!salir)
	{

		if ((nuevo_sd = accept(sd, (struct sockaddr*)&cliente, &tam_sockcliente))<0)
		{
			perror("Error aceptando solicitud");
			return EXIT_FAILURE;
		}

		//Recibo el comando
		if ((longitud = recv(nuevo_sd, (char*)&comando, 5, MSG_PEEK)) < 0 )
		{
			perror("Error recibiendo la peticion");
			return EXIT_FAILURE;
		}

		// ¿Acabamos?
		if(strncasecmp(comando,"fin",3)==0)
		{
			printf("\tRecibido el comando fin. Finalizando...\n");

			if (shutdown(nuevo_sd, SHUT_RDWR)<0 || close(sd)<0)
			{
				perror("Error cerrando la conexion");
				return EXIT_FAILURE;
			}

			salir=1;
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

			printf("Enviado:\n%s\n",buffer);

			if (shutdown(nuevo_sd, SHUT_RDWR)<0)
			{
				perror("Error cerrando la conexion");
				return EXIT_FAILURE;
			}
		}
		else
		{
			printf("\tNo entiendo el comando \"%s\".\n",comando);

			if (shutdown(nuevo_sd, SHUT_RDWR)<0)
			{
				perror("Error cerrando la conexion");
				return EXIT_FAILURE;
			}
		}
	}

	return EXIT_SUCCESS;
}

