/*************************************************************************
  09-01-2008: Rubén Dugo
  - Servidor de frases UDP no bloqueante: recibe solicitudes de frases con un nombre y devuelve frases con el nombre solicitado.
  - Uso: ./servidor_udp <puerto 1> ... <puerto n>
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

#define SEG 1

#include "frases.h"


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
	if(argc<2)
	{
		fprintf(stderr,"Uso: %s <puerto 1> ... <puerto n>\n",argv[0]);
		return EXIT_FAILURE;
	}


	//Variables para sockets y demás historias
	struct sockaddr_in cliente, servidor;
	unsigned int puerto;
	int salir, longitud, *sd, leido, i, retval,num;
	long ciclos;
	socklen_t tam_sockcliente = sizeof(cliente);
	char comando[5], buffer[255];
	mi_cabecera cabecera;
	fd_set rfds;
	struct timeval tv;

	//Reservo memoria para los descriptores
	sd = (int*)malloc(sizeof(int)*(argc-1));

	//Procesamos los parámetros
	num = argc-1;
	for (i=0;i<num;i++)
	{
		puerto = atoi(argv[i+1]);

		if ( (sd[i] = socket (AF_INET, SOCK_DGRAM, 0) ) <0)
		{
			perror("Error abriendo socket");
			return EXIT_FAILURE;
		}

		servidor.sin_family = AF_INET;
		servidor.sin_addr.s_addr = INADDR_ANY;
		servidor.sin_port = htons(puerto);

		if (bind ( sd[i], (struct sockaddr *)&servidor, sizeof (servidor) ) <0)
		{
			perror("Error en la funcion bind");
			return EXIT_FAILURE;
		}

	}

	//Semilla aleatoria
	srand(time(NULL));

	printf("\n\tServidor UDP listo para procesar las peticiones a los %d puertos.\n\n",num);

	salir = 0;
	//Bucle para procesar las solicitudes
	while (!salir)
	{

		ciclos = leido = 0;

		while (!leido)
		{
			//Inicializo el tiempo de espera
			tv.tv_sec = SEG;
			tv.tv_usec = 0;

			//Inicializo el conjunto de descriptores
			FD_ZERO(&rfds);
			for (i=0;i<num;i++) FD_SET(sd[i], &rfds);

			/*
				Debo inicializar ambas cosas debido a que la función select()
				me las destruye una vez agotado el tiempo de espera
			*/

			retval = select(sd[num-1]+1, &rfds, NULL, NULL, &tv);

			if (retval<0)
			{
				perror("Error en la funcion select()");
				return EXIT_FAILURE;
			}

			if (retval)
			{
				sleep(3);

				leido = 1;

				for (i=0;i<num;i++)
				{
					if (FD_ISSET(sd[i],&rfds))
					{
						//Recibo el comando
						if ((longitud = recvfrom(sd[i], (char*)&comando, 5, MSG_PEEK, (struct sockaddr *)&cliente, &tam_sockcliente)) < 0 )
						{
							perror("Error recibiendo la peticion");
							return EXIT_FAILURE;
						}

						// ¿Acabamos?
						if(strncasecmp(comando,"fin",3)==0)
						{
							printf("\tRecibido el comando fin. Finalizando...\n");
							salir=1;
							if(close(sd[i])<0)
							{
								perror("Error cerrando descriptor de socket");
								return EXIT_FAILURE;
							}
						}
						else if (strncasecmp(comando,"frase",5)==0) //¿Envio frase?
						{

							//Recibo el paquete completo
							if (recvfrom(sd[i], (char*)&cabecera, sizeof(cabecera), 0, (struct sockaddr*)&cliente, &tam_sockcliente) < 0)
							{
								perror("Error recibiendo datos");
								return EXIT_FAILURE;
							}

							cabecera.nombre[cabecera.longitud] = 0;

							longitud = sprintf(buffer,frases[rand()%NFRASES],cabecera.nombre);
							buffer[longitud]='\0';

							//Envio
							if (sendto(sd[i], buffer, longitud, 0, (struct sockaddr*)&cliente, sizeof(cliente) ) < 0 )
							{
								perror("Error enviando respuesta");
								return EXIT_FAILURE;
							}

							printf("Enviado:\n%s\n",buffer);
						}
						else printf("\tNo entiendo el comando \"%s\".\n",comando);
					}
				}

				printf("Han transcurrido %li ciclo(s) desde la ultima recepcion de datos.\nEquivalentes a %li segundo(s).\n\n",ciclos,ciclos*SEG);
			}
			ciclos++;
		}
	}

	free(sd);

	return EXIT_SUCCESS;
}

