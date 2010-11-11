all: servidor_udp cliente_udp servidor_tcp cliente_tcp servidor_tcp_conc servidor_udp_nobloq cliente_udp_conc

servidor_udp: servidor_udp.c frases.h
	gcc -Wall servidor_udp.c -o servidor_udp

cliente_udp: cliente_udp.c
	gcc -Wall cliente_udp.c -o cliente_udp

servidor_tcp: servidor_tcp.c frases.h
	gcc -Wall servidor_tcp.c -o servidor_tcp

cliente_tcp: cliente_tcp.c
	gcc -Wall cliente_tcp.c -o cliente_tcp

servidor_tcp_conc: servidor_tcp_conc.c frases.h
	gcc -Wall servidor_tcp_conc.c -o servidor_tcp_conc

servidor_udp_nobloq: servidor_udp_nobloq.c
	gcc -Wall -g servidor_udp_nobloq.c -o servidor_udp_nobloq

cliente_udp_conc: cliente_udp_conc.c
	gcc -Wall cliente_udp_conc.c -o cliente_udp_conc -lpthread

clean:
	rm -rf servidor_udp cliente_udp servidor_tcp cliente_tcp servidor_tcp_conc servidor_udp_nobloq cliente_udp_conc

mrproper: clean


