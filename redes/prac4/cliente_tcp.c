/*************************************************************************
  09-01-2008: Rubén Dugo
  - Cliente de frases TCP: envia solicitudes de frases con un nombre y recibe frases con el nombre solicitado.
  - Uso: ./cliente_tcp <IP> <puerto_servicio> [nombre]
*************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

enum ACCION
{
	FIN,
	FRASE
};

int main(int argc, char **argv)
{

	//Comprobamos parámetros
	if(argc<3 || argc>4){
		fprintf(stderr,"Uso: %s <IP> <puerto_servicio> [nombre]\n",argv[0]);
		return EXIT_FAILURE;
	}

	int longitud, sd;
	unsigned int puerto;
	struct hostent *maquina;
	char nombre[100], buffer[255];
	enum ACCION accion;
	struct sockaddr_in servidor;
	socklen_t tam_sockservidor = sizeof(servidor);

	//Cogemos los parámetos
	puerto = atoi (argv[2]);
	//Utilizo la función gethostbyname
	maquina = gethostbyname (argv[1]);

	if(argc>3)
	{
		accion = FRASE;
		sprintf(nombre,argv[3]);
	}
	else accion = FIN;

	//Inicializando el socket
	sd = socket (AF_INET, SOCK_STREAM, 0);
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = ((struct in_addr *)(maquina->h_addr))->s_addr;
	servidor.sin_port = htons(puerto);

	//Lo conectamos

	if(connect(sd, (struct sockaddr*)&servidor, sizeof(servidor) ) < 0)
	{
		perror("Error en la funcion connect");
		return EXIT_FAILURE;
	}
	else
	{
		if (accion == FIN)
		{
			longitud = sprintf(buffer,"fin");

			//La envio
			if (sendto(sd, buffer, longitud, 0, (struct sockaddr*)&servidor, sizeof(servidor) )<0)
			{
				perror("Error enviando peticion");
				return EXIT_FAILURE;
			}

			if(close(sd)<0)
			{
				perror("Error cerrando descriptor de socket");
				return EXIT_FAILURE;
			}
		}
		else
		{

			//Preparo la peticion
			longitud = sprintf(buffer,"frase%c%s",(unsigned char)strlen(nombre),nombre);

			//La envio
			if (sendto(sd, buffer, longitud, 0, (struct sockaddr*)&servidor, sizeof(servidor) )<0)
			{
				perror("Error enviando peticion");
				return EXIT_FAILURE;
			}

			//Recibo la respuesta
			if ((longitud = recvfrom(sd, buffer, 255, 0, (struct sockaddr*)&servidor, &tam_sockservidor))< 0)
			{
				perror("Error recibiendo respuesta");
				return EXIT_FAILURE;
			}
			buffer[longitud]='\0';

			printf("Frase:\n%s\n (%d bytes)\n",buffer,longitud);
			if(close(sd)<0)
			{
				perror("Error cerrando descriptor de socket");
				return EXIT_FAILURE;
			}
		}
	}

	return EXIT_SUCCESS;
}


