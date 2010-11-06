CFLAGS=-Wall -O3
LDFLAGS=-L./ -lalpha -lm

all: ej4 testalpha

ej4: ej4.o libalpha.a
	gcc ej4.o ${LDFLAGS} -o ej4

ej4.o: ej4.c alpha.h
	gcc ej4.c ${CFLAGS} -c -o ej4.o

testalpha: testalpha.o libalpha.a
	gcc testalpha.o ${LDFLAGS} -o testalpha

testalpha.o: testalpha.c alpha.h
	gcc testalpha.c ${CFLAGS} -c -o testalpha.o

libalpha.a: alphaodds.o alphagen.o
	ar rsv libalpha.a alphaodds.o alphagen.o

alphaodds.o: alpha.h alphaodds.c
	gcc alphaodds.c ${CFLAGS} -c -o alphaodds.o

alphagen.o: alpha.h alphagen.c
	gcc alphagen.c ${CFLAGS} -c -o alphagen.o

clean:
	-\rm -vf *.o ej4.1.txt ej4.2-es.txt ej4.2-en.txt ej4.3.txt prob1.txt prob2.txt prob3.txt dictest1.txt dictest2.txt

mrproper: clean
	-\rm -vf ej4 testalpha libalpha.a
