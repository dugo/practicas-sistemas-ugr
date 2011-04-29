CXX = g++ -Wall

all: codifica  decodifica_lineal  decodifica_binario

codifica: codificar.o  codigo_huffman.o
	${CXX} -o codifica codigo_huffman.o codificar.o

decodifica_lineal: decodificar.o  decodigo_huffman_lineal.o
	${CXX} -o decodifica_lineal decodificar.o decodigo_huffman_lineal.o

decodifica_binario: decodificar.o  decodigo_huffman_binario.o
	${CXX} -o decodifica_binario decodificar.o decodigo_huffman_binario.o

codificar.o: codificar.cpp
	${CXX} -c codificar.cpp -o codificar.o -g -I./

decodificar.o: decodificar.cpp  decodigo_huffman.h
	${CXX} -c decodificar.cpp -o decodificar.o -g -I./

codigo_huffman.o: codigo_huffman.cpp  codigo_huffman.h
	${CXX} -c codigo_huffman.cpp -o codigo_huffman.o -g -I./

decodigo_huffman_lineal.o: decodigo_huffman_lineal.cpp  decodigo_huffman.h
	${CXX} -c decodigo_huffman_lineal.cpp -o decodigo_huffman_lineal.o -g -I./

decodigo_huffman_binario.o: decodigo_huffman_binario.cpp  decodigo_huffman.h
	${CXX} -c decodigo_huffman_binario.cpp -o decodigo_huffman_binario.o -g -I./

clean:
	\rm *.o

mrproper: clean
	rm codifica
