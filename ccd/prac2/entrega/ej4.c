/*
	Fichero ej4.c.
	Realización del ejercio	4 del guion 2 de practicas de la asignatura CCD de la UGR.

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

	if (argc != 3)
	{
		printf("Parametros incorrectos.\n");
		printf("Uso: %s <dic_es> <dic_en>\n", argv[0]);
		printf("Ejemplo: %s PalabrasDRAE.4letras.txt 4letters.word.txt\n", argv[0]);
		exit(1);
	}

	printf("Ejercicio 4\n");
	printf("===========\n");

	// Inicializo las probabilidades, todas las letras con igual probabilidad
	prob = oddsinit(ALPHA_ES, 1);

	// Semilla aleatoria
	srand( time(NULL) );

	// Apartado 1
	gendictionary(prob, 4, 100, "ej4.1.txt");
	printf("\t1) Generado el diccionario en el fichero ej4.1.txt\n");

	// Apartado 2
	oddscalc(prob, argv[1]); // Calculo las probabilidades, español
	gendictionary(prob, 4, 100, "ej4.2-es.txt");
	oddsdestroy(prob);
	prob = oddsinit(ALPHA_EN, 1); // Vuelvo a inicializar el diccionario, esta vez en ingles
	oddscalc(prob, argv[2]); // Calculo las probabilidades, ingles
	gendictionary(prob, 4, 100, "ej4.2-en.txt");
	printf("\t2) Generados los diccionarios los ficheros ej4.2-es.txt y ej4.2-en.txt, español e ingles resp.\n");

	// Apartado 3
	oddsdestroy(prob);
	prob = oddsinit(ALPHA_ES, 2); // Inicializo las probabilidades, esta vez para secuencias de longitud 2
	oddscalc(prob, argv[1]);
	gendictionary(prob, 4, 100, "ej4.3.txt");
	printf("\t3) Generado el diccionario en el fichero ej4.3.txt\n");

	oddsdestroy(prob);


	return 0;
}
