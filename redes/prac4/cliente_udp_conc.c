/*************************************************************************
  09-01-2008: Rubén Dugo
  - Cliente de frases UDP concurrente: envia solicitudes de frases con un nombre y recibe frases con el nombre solicitado.
  - Uso: ./cliente_udp_conc <IP> <puerto 1> ... <puerto n>
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
#include <pthread.h>

#define NOMBRE "anonimo"

/*
	Esta variable se compartira con los hijos
	en el momento que sea 0 todos haran la peticion
*/
static int espera = 1;

typedef struct
{
	const char *servidor;
	unsigned int puerto;
} param_hebra;

void *func_hebra(param_hebra *param)
{
	param_hebra p = *param;
	int longitud, sd;
	struct hostent *maquina;
	char buffer[255];
	struct sockaddr_in servidor;
	socklen_t tam_sockservidor = sizeof(servidor);

	//Utilizo la función gethostbyname
	maquina = gethostbyname (p.servidor);

	sd = socket (AF_INET, SOCK_DGRAM, 0);
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = ((struct in_addr *)(maquina->h_addr))->s_addr;
	servidor.sin_port = htons(p.puerto);

	//Lo conectamos
	if(connect(sd, (struct sockaddr*)&servidor, sizeof(servidor) ) < 0)
	{
		perror("Error en la funcion connect");
		exit(EXIT_FAILURE);
	}

	//Preparo la peticion
	longitud = sprintf(buffer,"frase%c%s",(unsigned char)strlen(NOMBRE),NOMBRE);

	printf("[Puerto %d] Listo para realizar peticion.\n",p.puerto);

	//Espero la orden
	while (espera);

	printf("[Puerto %d] Orden recibida.\n",p.puerto);

	//La envio
	if (sendto(sd, buffer, longitud, 0, (struct sockaddr*)&servidor, sizeof(servidor) )<0)
	{
		perror("Error enviando peticion");
		exit(EXIT_FAILURE);
	}

	//Recibo la respuesta
	if ((longitud = recvfrom(sd, buffer, 255, 0, (struct sockaddr*)&servidor, &tam_sockservidor))< 0)
	{
		perror("Error recibiendo respuesta");
		exit(EXIT_FAILURE);
	}
	buffer[longitud]='\0';

	printf("Frase:\n%s\n (%d bytes)\n",buffer,longitud);
	if(close(sd)<0)
	{
		perror("Error cerrando descriptor de socket");
		exit(EXIT_FAILURE);
	}

	pthread_exit(&(p.puerto));
}

int main(int argc, char **argv)
{

	//Comprobamos parámetros
	if(argc<3){
		fprintf(stderr,"Uso: %s <IP> <puerto 1> ... <puerto n>\n",argv[0]);
		return EXIT_FAILURE;
	}

	int i,res;

	pthread_t *tabla_thr = (pthread_t*)malloc(sizeof(pthread_t)*(argc-2));

	param_hebra p;

	p.servidor = strdup(argv[1]);

	//Creo tantos hijos como puertos
	for (i=0;i<argc-2;i++)
	{
		sleep(1);
		//Cojo el puerto
		p.puerto = atoi (argv[i+2]);

		//Creo la hebra
		pthread_create(&tabla_thr[i], NULL, (void *)&func_hebra, (void *)&p);
	}

	//El padre espera a que se me de la orden de realizar las peticiones
	printf("[Padre] Escriba un caracter y pulse intro para dar la orden.\n");
	getchar();
	espera = 0;

	//Espero a que finalicen los hijos
	for (i=0; i<argc-2; i++) {
		pthread_join(tabla_thr[i], (void *)&res);
	}

	free(tabla_thr);

	return EXIT_SUCCESS;
}




