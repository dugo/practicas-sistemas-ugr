
all: entfile entfile2 diferencia diferencia-mod entfile-mod ej4 testalpha countalpha

countalpha: countalpha.c
	gcc countalpha.c -o countalpha

diferencia-mod: diferencia-mod.c
	gcc diferencia-mod.c -o diferencia-mod

diferencia: diferencia.c
	gcc diferencia.c -o diferencia

entfile: entfile.o entropy.o
	gcc entfile.o entropy.o -lm -o entfile

entfile.o: entfile.c idc.h
	gcc entfile.c -g -c -o entfile.o

entfile2: entfile2.o entropy.o
	gcc entfile2.o entropy.o -lm -o entfile2

entfile2.o: entfile2.c idc.h
	gcc entfile2.c -c -o entfile2.o

ej4: ej4.o libalpha.a
	gcc ej4.o -L./ -lalpha -lm -o ej4

ej4.o: ej4.c alpha.h
	gcc ej4.c -O3 -c -o ej4.o

testalpha: testalpha.o libalpha.a
	gcc testalpha.o -L./ -lalpha -lm -o testalpha

testalpha.o: testalpha.c alpha.h
	gcc testalpha.c -O3 -c -o testalpha.o

libalpha.a: alphaodds.o alphagen.o
	ar rsv libalpha.a alphaodds.o alphagen.o

alphaodds.o: alpha.h alphaodds.c
	gcc alphaodds.c -O3 -Wall -c -o alphaodds.o

alphagen.o: alpha.h alphagen.c
	gcc alphagen.c -O3 -Wall -c -o alphagen.o

entfile-mod: entfile-mod.o entropy.o
	gcc entfile-mod.o entropy.o -lm -o entfile-mod

entfile-mod.o: entfile-mod.c idc.h
	gcc entfile-mod.c -c -o entfile-mod.o

entropy.o: entropy.c
	gcc entropy.c -g -c -o entropy.o

clean:
	-\rm -vf *.o ej4.1.txt ej4.2-es.txt ej4.2-en.txt ej4.3.txt prob1.txt prob2.txt prob3.txt dictest1.txt dictest2.txt

mrproper: clean
	-\rm -vf entfile entfile2 diferencia diferencia-mod entfile-mod ej4 testalpha countalpha libalpha.a
