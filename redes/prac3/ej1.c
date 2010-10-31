/*
Ejercicio 1:

Programa que muestra estadisticas sobre los protocolos de red.

Rubén Dugo Martín <raubn.zero@gmail.com>
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pcap.h>
#include <string.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <net/ethernet.h>
#include <unistd.h>

typedef struct protoent protoent;
typedef struct ether_header ether_header;
typedef struct iphdr iphdr;

unsigned int est[5] = {0,0,0,0,0};
char cadena[][11]={"Ethernet:","ARP:","IP:","UDP:","TCP:"};
int total;
/*
	0: Ethernet
	1: ARP
	2: IP
	3: UDP
	4: TCP
*/

void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void imprimir_valores();

int main(int argc, char **argv)
{
	pcap_t *handle;
	char *dev, errbuf[PCAP_ERRBUF_SIZE];

	if (geteuid()!=0)
	{
		printf("Debe ejecutar este programa como root.\n");
		exit(EXIT_FAILURE);
	}

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

	handle = pcap_open_live(dev,BUFSIZ,1,0,errbuf);

	if (handle == NULL)
	{
		printf("Error: %s\n",errbuf);
		exit(EXIT_FAILURE);
	}

	printf("Pulse Ctrl+C pasa salir\n\n");

	imprimir_valores();

	pcap_loop(handle, 0, manejador, NULL);
	
	pcap_close(handle);

	return EXIT_SUCCESS;
}

void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	protoent *protocolo;
	iphdr *datagrama;
	ether_header *trama;

	total++;
	est[0]++;	//Supongo que todos los paquetes son ethernet

	trama=(ether_header *)(pkt_data);

	if(ntohs(trama->ether_type) == ETHERTYPE_IP)  //IP¿?
	{		
		datagrama=(iphdr *)(pkt_data+sizeof(ether_header));
		est[2]++;
	}
	else if(ntohs(trama->ether_type) == ETHERTYPE_ARP)   //ARP¿?
	{
		est[1]++;
	}

	protocolo = getprotobynumber(datagrama->protocol);

	if(protocolo!=0)
	{
		if(!strcmp(protocolo->p_name, "udp")) est[3]++;
		else if (!strcmp(protocolo->p_name, "tcp")) est[4]++;
	}

	imprimir_valores();

}

void imprimir_valores()
{
	int i;

	for (i=0;i<5;i++)
	{
		printf(cadena[i]);

		printf(" %3.1f%%     ",(total>0) ? ((float)(est[i]*100)/total) : (0.) );
	}
	printf("\r");

	fflush(stdout);
}

