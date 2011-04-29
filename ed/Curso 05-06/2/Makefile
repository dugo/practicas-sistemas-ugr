all: funciones

CXX = g++ -Wall

funciones: funciones.o cadena.o
	${CXX} -o funciones funciones.o cadena.o

funciones.o: funciones.cpp cadena.h

cadena.o: cadena.cpp

clean:
	\rm *.o funciones

distclean: clean
	rm funciones
