/*
Ejercicio 2:

Programa que muestra los datos de las cabeceras UDP.

Rubén Dugo Martín <raubn.zero@gmail.com>
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pcap.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <net/ethernet.h>
#include <unistd.h>

#define FILTRO "udp"

typedef struct protoent protoent;
typedef struct ether_header ether_header;
typedef struct iphdr iphdr;
typedef struct udphdr udphdr;

void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void mostrar(udphdr *cabecera_udp);

unsigned int paquetes=0;

int main(int argc, char **argv)
{

	if (geteuid()!=0)
	{
		printf("Debe ejecutar este programa como root.\n");
		exit(0);
	}

	char *dev, errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct bpf_program filtro;
	u_int32_t ip,mascara;

	if (argc<2)
	{
		dev = pcap_lookupdev(errbuf);
		if (dev == NULL)
		{
			printf("Error: %s\n",errbuf);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		dev=(char*)malloc(strlen(argv[1])+1);
		strcpy(dev,argv[1]);
	}


	if (pcap_lookupnet(dev, &ip, &mascara, errbuf)<0)
	{
		printf("Error: %s\n",errbuf);
		exit(EXIT_FAILURE);
	}

	handle = pcap_open_live(dev,BUFSIZ,1,0,errbuf);

	pcap_compile(handle, &filtro, FILTRO, 0, ip);
	pcap_setfilter(handle, &filtro);


	if (handle == NULL)
	{
		printf("Error: %s\n",errbuf);
		exit(EXIT_FAILURE);
	}

	printf("Pulse Ctrl+C pasa salir\n\n");

	printf("N#      P.Destino      P.Origen       Longitud     Checksum\n");
	printf("-----------------------------------------------------------\n");

	pcap_loop(handle, 0, manejador, NULL);
	
	pcap_close(handle);


	return 0;
}

void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	protoent *protocolo;
	iphdr *datagrama;
	ether_header *trama;
	udphdr *cabecera_udp;

	trama=(ether_header *)(pkt_data);

	if(ntohs(trama->ether_type) == ETHERTYPE_IP)  //IP¿?
	{		
		datagrama=(iphdr *)(pkt_data+sizeof(ether_header));

		protocolo = getprotobynumber(datagrama->protocol);

		if(protocolo!=0 && !strcmp(protocolo->p_name, "udp")) //UDP¿?
		{
			cabecera_udp = (udphdr *) (pkt_data+sizeof(ether_header)+sizeof(iphdr));
			mostrar(cabecera_udp);
		}
	}
}

void mostrar(udphdr *cabecera_udp)
{
	printf("%-7u ",++paquetes);
	printf("%9u      ",ntohs(cabecera_udp->source));
	printf("%8u       ",ntohs(cabecera_udp->dest));
	printf("%8u     ",ntohs(cabecera_udp->len));
	printf("0x%-8x\n",ntohs(cabecera_udp->check));
}

