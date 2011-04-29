all: ejemplo1  ejemplo2  ejemplo3  ejemplos  ejemplo4

CXX = g++ -Wall

ejemplo1: ejemplo1.o
	${CXX} -o ejemplo1 ejemplo1.o

ejemplo1.o: ejemplo1.cpp  ejemplos.h  matriz.template  matriz.h
	${CXX} -c ejemplo1.cpp -o ejemplo1.o -g -I./

ejemplo2: ejemplo2.o
	${CXX} -o ejemplo2 ejemplo2.o

ejemplo2.o: ejemplo2.cpp  ejemplos.h  matriz.template  matriz.h
	${CXX} -c ejemplo2.cpp -o ejemplo2.o -g -I./

ejemplo3: ejemplo3.o
	${CXX} -o ejemplo3 ejemplo3.o

ejemplo3.o: ejemplo3.cpp  ejemplos.h  matriz.template  matriz.h
	${CXX} -c ejemplo3.cpp -o ejemplo3.o -g -I./

ejemplos: ejemplos.o
	${CXX} -o ejemplos ejemplos.o

ejemplos.o: ejemplos.cpp  ejemplos.h  matriz.template  matriz.h
	${CXX} -c ejemplos.cpp -o ejemplos.o -g -I./

ejemplo4: ejemplo4.o
	${CXX} -o ejemplo4 ejemplo4.o

ejemplo4.o: ejemplo4.cpp  ejemplos.h  matriz.template  matriz.h
	${CXX} -c ejemplo4.cpp -o ejemplo4.o -g -I./

clean:
	\rm *.o

mrproper: clean
	rm ejemplo1 ejemplo2 ejemplo3 ejemplos ejemplo4
