/*
Ejercicio 3:

Programa que muestra los datos de las cabeceras TCP.

Rubén Dugo Martín <raubn.zero@gmail.com>
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pcap.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <net/ethernet.h>
#include <unistd.h>

#define FILTRO "tcp"

typedef struct protoent protoent;
typedef struct ether_header ether_header;
typedef struct iphdr iphdr;
typedef struct tcphdr tcphdr;

void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void mostrar(tcphdr *cabecera_tcp);

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
			exit(0);
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
		exit(0);
	}

	printf("Pulse Ctrl+C pasa salir\n\n");

	pcap_loop(handle, 0, manejador, NULL);
	
	pcap_close(handle);


	return 0;
}

void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	protoent *protocolo;
	iphdr *datagrama;
	ether_header *trama;
	tcphdr *cabecera_tcp;

	trama=(ether_header *)(pkt_data);

	if(ntohs(trama->ether_type) == ETHERTYPE_IP)  //IP¿?
	{		
		datagrama=(iphdr *)(pkt_data+sizeof(ether_header));

		protocolo = getprotobynumber(datagrama->protocol);

		if(protocolo!=0 && !strcmp(protocolo->p_name, "tcp")) //tcp¿?
		{
			cabecera_tcp = (tcphdr *) (pkt_data+sizeof(ether_header)+sizeof(iphdr));
			mostrar(cabecera_tcp);
		}
	}
}

void mostrar(tcphdr *cabecera_tcp)
{

	printf("Nuevo Paquete TCP!\n");
	printf("==================\n\n");
	printf("P.Destino  P.Origen        Seq#         Ack#  DataOffset  Reservado\n");

	printf("%9u  ",ntohs(cabecera_tcp->source));
	printf("%8u   ",ntohs(cabecera_tcp->dest));
	printf("%9u    ",ntohl(cabecera_tcp->seq));
	printf("%9u          ",ntohl(cabecera_tcp->ack_seq));

	printf("%2u  ",cabecera_tcp->doff);
	printf(" 0x%-2x",cabecera_tcp->res1);
	printf(" 0x%-2x",cabecera_tcp->res2);

	printf("\n\nBits:  URG(%1u)  ACK(%1u)  PSH(%1u)  RST(%1u)  SYN(%1u)  FIN(%1u)\n",
		cabecera_tcp->urg,
		cabecera_tcp->ack,
		cabecera_tcp->psh,
		cabecera_tcp->rst,
		cabecera_tcp->syn,
		cabecera_tcp->fin);

	printf("\n\nWindow      Checksum           Urgent Pointer\n");

	printf(" %5u",ntohs(cabecera_tcp->window));
	printf("       0x%-5u",ntohs(cabecera_tcp->check));
	printf("                  0x%-5u\n\n",ntohs(cabecera_tcp->check));


}

