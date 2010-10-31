/*
Ejercicio 7:

Detecta un posible escaneo de puertos.

Rubén Dugo Martín <raubn.zero@gmail.com>
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pcap.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <net/ethernet.h>
#include <unistd.h>

#define FILTRO "tcp"

//Con NUM_SYN paquetes SYN considero un escaneo
#define NUM_SYN 5

typedef struct protoent protoent;
typedef struct ether_header ether_header;
typedef struct iphdr iphdr;
typedef struct tcphdr tcphdr;
typedef struct pcap_if pcap_if_t;

typedef u_int32_t dir_ip;
typedef u_int16_t puerto;

struct atacante
{
	dir_ip ip;
	unsigned int intentos;

	puerto *puertos;
};

dir_ip ip_actual;
unsigned int num_atacantes=0;
struct atacante *atacantes;

dir_ip obteneriplocal(char *iface);
void manejador(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

int main(int argc, char **argv)
{

	if (geteuid()!=0)
	{
		printf("Debe ejecutar este programa como root.\n");
		exit(0);
	}

	char *dev, errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	dir_ip ip,mascara;
	struct bpf_program filtro;

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

	ip_actual = obteneriplocal(dev);

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

	struct atacante *ptr_atacantes;
	dir_ip ip;
	puerto puerto_dest,*ptr_puertos;

	int i,j,at;
	int enc;

	trama=(ether_header *)(pkt_data);

	if(ntohs(trama->ether_type) == ETHERTYPE_IP)  //IP¿?
	{		
		datagrama=(iphdr *)(pkt_data+sizeof(ether_header));

		protocolo = getprotobynumber(datagrama->protocol);

		if(protocolo!=0 && !strcmp(protocolo->p_name, "tcp")) //tcp¿?
		{

			//Cojo la ip origen
			ip = (dir_ip) ntohl(datagrama->saddr);

			//Compruebo si es la ip de mi maquina
			if (ip!=ip_actual)
			{
				cabecera_tcp = (tcphdr *) (pkt_data+sizeof(ether_header)+sizeof(iphdr));

				//Tiene el byte syn activo, posible escaneo de puertos
				if (cabecera_tcp->syn)
				{
					//Busco el atacante en la lista
					for (enc=0,i=0;i<num_atacantes && !enc;i++) enc=(atacantes[i].ip==ip);

					puerto_dest = ntohs(cabecera_tcp->dest);

					i--;
					at = -1;

					//El atacante ya esta en la lista
					if (enc)
					{
						//Compruebo que no haya intentado escanear el puerto antes
						for (enc=0,j=0;j<atacantes[i].intentos && !enc;j++)
							enc = (atacantes[i].puertos[j]==puerto_dest);

						//Si no lo ha intentado lo añado y lo cuento como intento
						if (!enc)
						{

							//Reservo memoria en bloques de 10 para los puertos
							if (atacantes[i].intentos%10==0)
							{

								ptr_puertos = atacantes[i].puertos;
								atacantes[i].puertos = (puerto*)malloc(sizeof(puerto)*(atacantes[i].intentos+10));

								for (j=0;j<atacantes[i].intentos;j++)
									atacantes[i].puertos[j]=ptr_puertos[i];

								if (atacantes[i].intentos>0) free(ptr_puertos);
							}

							atacantes[i].puertos[atacantes[i].intentos] = puerto_dest;
							atacantes[i].intentos++;
							at = i;
						}
					}
					else
					{
						//Reservo memoria en bloques de 10
						if (num_atacantes%10==0)
						{
							ptr_atacantes = atacantes;

							atacantes = (struct atacante*)malloc(sizeof(struct atacante)*(num_atacantes+10));

							for (i=0;i<num_atacantes;i++) atacantes[i]=ptr_atacantes[i];

							if (num_atacantes>0) free(ptr_atacantes);
						}

						atacantes[num_atacantes].ip = ip;
						atacantes[num_atacantes].intentos = 1;

						atacantes[num_atacantes].puertos = (puerto*)malloc(sizeof(puerto)*10);

						atacantes[num_atacantes].puertos[0] = puerto_dest;

						num_atacantes++;
					}

					if (at>=0 && atacantes[at].intentos % NUM_SYN == 0 )
					{

						if (atacantes[at].intentos>NUM_SYN)
							printf("El atacante %u.%u.%u.%u siguiente insistiendo, ",
								ip>>24,
								(ip>>16) & 255,
								(ip>>8) & 255,
								ip & 255);

						else
							printf("Posible escaneo de puertos desde la IP: %u.%u.%u.%u, ",
								ip>>24,
								(ip>>16) & 255,
								(ip>>8) & 255,
								ip & 255);

						printf("puertos: ");

						for (i = atacantes[at].intentos-NUM_SYN;i<atacantes[at].intentos;i++)
							printf("%u ",atacantes[at].puertos[i]);

						printf("\n\n");
					}
				}
			}

		}
	}
}

dir_ip obteneriplocal(char *iface)
{
	int tmp;
	struct ifreq ifr;
	struct sockaddr sa;
  
  tmp = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	strcpy(ifr.ifr_name, iface);
	ifr.ifr_addr.sa_family = AF_INET;

	if (ioctl(tmp, SIOCGIFADDR, &ifr) != 0)
	{
		fprintf(stderr, "Cannot get local IP address for iface %s\n",
			iface);
		exit(EXIT_FAILURE);
	}

	close(tmp);
	sa = ifr.ifr_addr;

	return ntohl(((struct sockaddr_in*)&sa)->sin_addr.s_addr);
}

