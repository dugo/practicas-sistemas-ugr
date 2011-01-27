all: main main_rango1 main_rango2

main_rango1: main_rango1.o	dyv_rango.o	dyv_tornillos_y_tuercas.o
	g++ -g -Wall main_rango2.o dyv_rango.o dyv_tornillos_y_tuercas.o -o main_rango1

main_rango2: main_rango2.o	dyv_rango.o	dyv_tornillos_y_tuercas.o
	g++ -g -Wall main_rango2.o dyv_rango.o dyv_tornillos_y_tuercas.o -o main_rango2

main: main.o	dyv_rango.o	dyv_tornillos_y_tuercas.o
	g++ -g -Wall main.o dyv_rango.o dyv_tornillos_y_tuercas.o -o main

main_rango2.o: main_rango2.cpp
	g++ -g -Wall main_rango2.cpp -c -o main_rango2.o

main_rango1.o: main_rango1.cpp
	g++ -g -Wall main_rango1.cpp -c -o main_rango1.o

main.o: main.cpp
	g++ -g -Wall main.cpp -c -o main.o

dyv_rango.o: dyv_rango.cpp
	g++ -g -Wall dyv_rango.cpp -c -o dyv_rango.o

dyv_tornillos_y_tuercas.o: dyv_tornillos_y_tuercas.cpp
	g++ -g -Wall dyv_tornillos_y_tuercas.cpp -c -o dyv_tornillos_y_tuercas.o
