/*
	Fichero alphagen.c.
	Implementacion de las funciones de generacion de palabras y diccionarios
	de la biblioteca alpha.

	Rubén Dugo Martín <raubn.zero@gmail.com>
	11-4-08

	Licencia: GPL (http://www.gnu.org/licenses/gpl.html), por supuesto.

	ATENCION: El desarrollo de esta biblioteca es puramente academico, solo se puede
	garantizar el correcto funcionamiento para la realizacion de los ejercicios de
	practicas de la asignatura CCD.

	Para mas informacion sobre la biblioteca vea la especificacion en el fichero alpha.h.
*/
#include <stdio.h>
#include <stdlib.h>
#include "alpha.h"

void gendictionary(Odds *odds, int wordlength, const int words, const char *fdic)
{
	FILE *f;
	char buf[wordlength+1];
	int i;

	if ((f=fopen(fdic,"w"))==NULL)
	{
		perror("Output file open failed");
		exit(1);
	}

	buf[wordlength] = 0;

	// Genero y almaceno cada una de las palabras
	for (i=0;i<words;++i)
	{
		genword(odds, buf, wordlength);
		fprintf(f,"%s\n",buf);
	}

	fclose(f);
}

void genword(Odds *odds, char *word, const int length)
{
	register int i;
	register int k;
	register int j;
	int found;
	double r;

	for (i=0;i<length;i+=odds->seq_len)
	{

		// Genero el numero aleatorio
		r = (double) (rand()/(RAND_MAX+1.0));

		found = 0;
		for (k=0;k<odds->odds_len && !found;++k)
		{
			if (oddsdistfunc(odds, k)>r) found=1;
		}
		k--;


		for (j=odds->seq_len-1;j>=0;--j)
		{
			word[i+j] = ( (odds->lang==ALPHA_ES && ((k+1)%odds->alpha_len) == 0 ) ? ( ENNE ) : ( 'a' + (k%odds->alpha_len) ) );
			k = k/odds->alpha_len;
		}
	}
}
