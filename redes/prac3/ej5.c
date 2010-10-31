/*
Ejercicio 5:

Programa que muestra el flujo de una conexión TCP determinada de un fichero de trazas.

Rubén Dugo Martín <raubn.zero@gmail.com>
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <pcap.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <net/ethernet.h>

//depurar?
//#define DEBUG

typedef struct protoent protoent;
typedef struct ether_header ether_header;
typedef struct iphdr iphdr;
typedef struct tcphdr tcphdr;

typedef u_int32_t dir_ip;
typedef u_int16_t puerto;
typedef u_int32_t num_seq_ack;

//Defino mi tipo personalizado de paquete
//con los datos que me interesan
struct mi_paquete_tcp
{
	dir_ip ip1;
	dir_ip ip2;
	puerto puerto1;
	puerto puerto2;
	num_seq_ack seq;
	num_seq_ack ack;
	char *contenido;
	unsigned int longitud;
};

//Defino mi tipo conexion
struct mi_conexion_tcp
{
	dir_ip ip1;
	dir_ip ip2;
	puerto puerto1;
	puerto puerto2;
};

typedef struct mi_paquete_tcp mi_paquete_tcp;
typedef struct mi_conexion_tcp mi_conexion_tcp;

unsigned int num_paquetes=0;
struct mi_paquete_tcp *ptr_paquetes;

//El manejador de paquetes simplemente los añade a un vector para tratarlos mas adelante
void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

//Muestra una conexión tcp en la consola
void mostrar_conexion_tcp(struct mi_conexion_tcp *c);

//Muestra un paquete tcp en la consola, para depurar
void mostrar_paquete_tcp(struct mi_paquete_tcp *c);

//Esta función recibe un vector de paquetes tcp y devuelve las diferentes conexiones que existen en el
mi_conexion_tcp* buscar_conexiones_tcp(struct mi_paquete_tcp *c,
	const unsigned int npaquetes,
	unsigned int *nconexiones);

//Esta función simplemente comprueba si una cabecera tcp pertenece a una conexión concreta
int misma_conexion_tcp(struct mi_paquete_tcp *c, struct mi_conexion_tcp *con);

//Muestra el flujo de una conexion tcp determinada
void mostrar_flujo_tcp(struct mi_paquete_tcp *c, unsigned int npaquetes, struct mi_conexion_tcp *con);

int main(int argc, char **argv)
{

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;

	struct mi_conexion_tcp *ptr_conexiones;
	unsigned int nconexiones;
	int i,sel;
	char buf[10];

	if (argc<2)
	{
		printf("Uso: %s <fichero de trazas>\n",argv[0]);
	}

	handle = pcap_open_offline(argv[1],errbuf);

	if (handle == NULL)
	{
		printf("Error: %s\n",errbuf);
		exit(0);
	}

	pcap_loop(handle, 0, manejador, NULL);

	pcap_close(handle);

	ptr_conexiones = buscar_conexiones_tcp(ptr_paquetes,num_paquetes,&nconexiones);


	if (nconexiones<1)
	{
		printf("No se encontro ninguna conexion.\n");

		for (i=0;i<num_paquetes;i++)
		{
			if (ptr_paquetes[i].longitud>0)
			{
				free(ptr_paquetes[i].contenido);
			}
		}

		if (num_paquetes>0) free(ptr_paquetes);

		exit(EXIT_FAILURE);
	}

	printf("\nConexiones TCP diferentes encontradas: %u\n\n",nconexiones);

	for (i=0;i<nconexiones;i++)
	{
		printf("[%u]\n",i+1);
		mostrar_conexion_tcp(&ptr_conexiones[i]);
	}

	i = 0;
	do
	{

	printf("Escriba el numero de la conexion seleccionada o 0 para salir: ");

	while(!i) i = scanf( "%127s", buf );

	sel = atoi(buf);

	}
	while(sel<0 || sel > nconexiones);

	if(sel>0) mostrar_flujo_tcp(ptr_paquetes, num_paquetes, &ptr_conexiones[sel-1]);

	for (i=0;i<num_paquetes;i++)
	{
		if (ptr_paquetes[i].longitud>0)
		{
			free(ptr_paquetes[i].contenido);
		}
	}

	if (num_paquetes>0) free(ptr_paquetes);

	return 0;
}

void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	protoent *protocolo;
	iphdr *datagrama;
	ether_header *trama;
	tcphdr *cabecera_tcp;

	struct mi_paquete_tcp *ptr_paquetes_aux;
	int i;

	trama=(ether_header *)(pkt_data);

	if(ntohs(trama->ether_type) == ETHERTYPE_IP)  //IP¿?
	{		
		datagrama=(iphdr *)(pkt_data+sizeof(ether_header));

		protocolo = getprotobynumber(datagrama->protocol);

		if(protocolo!=0 && !strcmp(protocolo->p_name, "tcp")) //tcp¿?
		{
			cabecera_tcp = (tcphdr *) (pkt_data+sizeof(ether_header)+sizeof(iphdr));

			//Reservo memoria en bloques de 10 paquetes
			if (num_paquetes%10==0)
			{
				ptr_paquetes_aux = ptr_paquetes;

				ptr_paquetes = (mi_paquete_tcp *)malloc(sizeof(mi_paquete_tcp)*(num_paquetes+10));

				for (i=0;i<num_paquetes;i++)
					ptr_paquetes[i] = ptr_paquetes_aux[i];

				if (num_paquetes>0) free(ptr_paquetes_aux);
			}

			//Añado al vector los paquetes TCP
			ptr_paquetes[num_paquetes].ip1 = (dir_ip) ntohl(datagrama->saddr);
			ptr_paquetes[num_paquetes].ip2 = (dir_ip) ntohl(datagrama->daddr);
			ptr_paquetes[num_paquetes].puerto1 = (puerto) ntohs(cabecera_tcp->source);
			ptr_paquetes[num_paquetes].puerto2 = (puerto) ntohs(cabecera_tcp->dest);
			ptr_paquetes[num_paquetes].seq = (num_seq_ack) ntohl(cabecera_tcp->seq);
			ptr_paquetes[num_paquetes].ack = (num_seq_ack) ntohl(cabecera_tcp->ack_seq);

			//Longitud de datos tcp
			ptr_paquetes[num_paquetes].longitud =
				header->caplen - sizeof(ether_header) - sizeof(iphdr) - sizeof(tcphdr) - 12;

			//Paquete vacio?
			if (ptr_paquetes[num_paquetes].longitud>0)
			{
				//Reservo memoria para los datos
				ptr_paquetes[num_paquetes].contenido = (char*)malloc(ptr_paquetes[num_paquetes].longitud);

				//Copio los datos al vector
				memcpy(ptr_paquetes[num_paquetes].contenido,
					pkt_data + sizeof(ether_header) + sizeof(iphdr) + sizeof(tcphdr)+12,
					ptr_paquetes[num_paquetes].longitud);
			}

			#ifdef DEBUG
			mostrar_paquete_tcp(&ptr_paquetes[num_paquetes]);
			#endif

			num_paquetes++;
		}
	}
}

void mostrar_conexion_tcp(struct mi_conexion_tcp *c)
{
	char ip_imp1[16],ip_imp2[16];
	int i;

	printf("IP1                IP2                Puerto1     Puerto2\n");


	sprintf(ip_imp1,"%u.%u.%u.%u",
		c->ip1>>24,
		(c->ip1>>16) & 255,
		(c->ip1>>8) & 255,
		c->ip1 & 255
	);

	sprintf(ip_imp2,"%u.%u.%u.%u",
		c->ip2>>24,
		(c->ip2>>16) & 255,
		(c->ip2>>8) & 255,
		c->ip2 & 255
	);

	for (i=strlen(ip_imp1);i<15;i++) ip_imp1[i] = ' ';
	for (i=strlen(ip_imp2);i<15;i++) ip_imp2[i] = ' ';

	ip_imp1[15]=ip_imp2[15]=0;

	printf("%s    %s    %-5u       %-5u\n\n",ip_imp1,ip_imp2,c->puerto1,c->puerto2);
}

void mostrar_paquete_tcp(struct mi_paquete_tcp *c)
{
	char ip_imp1[16],ip_imp2[16];
	int i;

	printf("IP1                IP2                Puerto1     Puerto2        Seq#        Ack#\n");


	sprintf(ip_imp1,"%u.%u.%u.%u",
		c->ip1>>24,
		(c->ip1>>16) & 255,
		(c->ip1>>8) & 255,
		c->ip1 & 255
	);

	sprintf(ip_imp2,"%u.%u.%u.%u",
		c->ip2>>24,
		(c->ip2>>16) & 255,
		(c->ip2>>8) & 255,
		c->ip2 & 255
	);

	for (i=strlen(ip_imp1);i<15;i++) ip_imp1[i] = ' ';
	for (i=strlen(ip_imp2);i<15;i++) ip_imp2[i] = ' ';

	ip_imp1[15]=ip_imp2[15]=0;

	printf("%s    %s    %-5u       %-5u    %10u    %10u\n\n",ip_imp1,ip_imp2,c->puerto1,c->puerto2,c->seq,c->ack);
}

mi_conexion_tcp* buscar_conexiones_tcp(struct mi_paquete_tcp *c,const unsigned int npaquetes,unsigned int *nconexiones)
{
	int i,j,misma,k;
	struct mi_conexion_tcp *ptr_aux,*ptr_con;

	*nconexiones=0;

	//npaquetes/2 será el número máximo de conexiones que podría encontrar
	ptr_aux = (mi_conexion_tcp*)malloc(sizeof(mi_conexion_tcp)*(npaquetes/2));

	for (i=0;i<npaquetes;i++)
	{
		for (j=0;j<npaquetes;j++)
		{
			if (c[i].ip1 == c[j].ip2 &&
				c[i].ip2 == c[j].ip1 &&
				c[i].puerto1 == c[j].puerto2 &&
				c[i].puerto2 == c[j].puerto1 &&
				c[i].seq == c[j].ack &&
				c[i].ack == c[j].seq) //Encuentra una conexion
			{
				//Compruebo que la conexion encontrada no este en la lista
				misma=0;
				for (k=0;k<*nconexiones && !misma;k++) misma = misma_conexion_tcp(&c[i],&ptr_aux[k]);

				if (!misma)
				{
					ptr_aux[*nconexiones].ip1 = c[i].ip1;
					ptr_aux[*nconexiones].ip2 = c[i].ip2;
					ptr_aux[*nconexiones].puerto1 = c[i].puerto1;
					ptr_aux[*nconexiones].puerto2 = c[i].puerto2;

					#ifdef DEBUG
					printf("Nueva conexion tcp encontrada:\n");
					mostrar_conexion_tcp(&ptr_aux[*nconexiones]);
					#endif

					(*nconexiones)++;
				}
			}
		}
	}

	//Optimizo la memoria
	if (*nconexiones>0)
	{
		ptr_con = (mi_conexion_tcp*)malloc(sizeof(mi_conexion_tcp)*(*nconexiones));
		for (i=0;i<*nconexiones;i++) ptr_con[i]=ptr_aux[i];
	}

	if (npaquetes>0) free(ptr_aux);

	return ptr_con;
}

int misma_conexion_tcp(struct mi_paquete_tcp *c, struct mi_conexion_tcp *con)
{
	return ((c->ip1 == con->ip1 &&
			c->ip2 == con->ip2 &&
			c->puerto1 == con->puerto1 &&
			c->puerto2 == con->puerto2) ||
			(c->ip1 == con->ip2 &&
			c->ip2 == con->ip1 &&
			c->puerto1 == con->puerto2 &&
			c->puerto2 == con->puerto1));
}


void mostrar_flujo_tcp(struct mi_paquete_tcp *c, unsigned int npaquetes, struct mi_conexion_tcp *con)
{
	int i,j,ida;
	int enc_primero=0;

	dir_ip ip1,ip2;

	printf("\nFlujo de la conexion:\n\n");
	mostrar_conexion_tcp(con);

	for (i=0;i<npaquetes;i++)
	{
		if (misma_conexion_tcp(&c[i],con))
		{
			if (!enc_primero)
			{
				ip1 = c[i].ip1;
				ip2 = c[i].ip2;
				enc_primero=1;
			}
			ida = (ip1==c[i].ip1);

			printf("%u.%u.%u.%u %c %u.%u.%u.%u: ",
				c->ip1>>24,
				(c->ip1>>16) & 255,
				(c->ip1>>8) & 255,
				c->ip1 & 255,
				(ida) ? ('>') : ('<'),
				c->ip2>>24,
				(c->ip2>>16) & 255,
				(c->ip2>>8) & 255,
				c->ip2 & 255
				);

			//Escribo solo los caracteres graficos
			for (j=0;j<c[i].longitud;j++)
				printf("%c",(isgraph((int)c[i].contenido[j])) ? c[i].contenido[j] : '.' );

			printf("\n\n");
		}
	}
}


