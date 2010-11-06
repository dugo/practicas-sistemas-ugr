/*
	Fichero testalpha.c.
	Fichero de prueba de la biblioteca alpha.

	Rubén Dugo Martín <raubn.zero@gmail.com>
	11-4-08
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "alpha.h"

int main(int argc, char **argv)
{

	Odds *prob;

	if (argc != 2)
	{
		printf("Parametros incorrectos.\n");
		printf("Uso: %s <dic_es>\n", argv[0]);
		printf("Ejemplo: %s PalabrasDRAE.4letras.txt\n", argv[0]);
		exit(1);
	}

	printf("Tests de la biblioteca alpha\n");
	printf("============================\n");
	
	// Inicializo las probabilidades
	prob = oddsinit(ALPHA_ES, 1);

	printf("\tPrimer test...");
	fflush(stdout);

	// Calculo probabilidades
	oddscalc(prob, argv[1]);
	// Imprimo probabilidades al fichero prob1.txt
	oddsprint(prob, "prob1.txt");
	// Semilla aleatoria
	srand( time(NULL) );
	// Genero un diccionario con cien mil palabras de 5 letras
	gendictionary(prob, 5, 100000, "dictest1.txt");
	// Calculo probabilidades del diccionario generado
	oddscalc(prob, "dictest1.txt");
	// Imprimo probabilidades al fichero prob2.txt
	oddsprint(prob, "prob2.txt");

	printf("realizado.\n\tLos ficheros prob1.txt y prob2.txt contienen las probabilidades del fichero de entrada y del generado (dictest1.txt), comparelas.\n");



	printf("\n\tSegundo test...");
	fflush(stdout);

	// Genero un diccionario con un millon de palabras de 6 letras
	gendictionary(prob, 6, 1000000, "dictest2.txt");
	// Calculo probabilidades del diccionario generado
	oddscalc(prob, "dictest2.txt");
	// Imprimo probabilidades al fichero prob3.txt
	oddsprint(prob, "prob3.txt");

	printf("realizado.\n\tLos ficheros prob1.txt y prob3.txt contienen las probabilidades del fichero de entrada y del generado (dictest2.txt), comparelas.\n");

	oddsdestroy(prob);

	return 0;
}
