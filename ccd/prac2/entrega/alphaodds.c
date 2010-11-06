/*
	Fichero alphaodds.c.
	Implementacion de las funciones de probabilidades de la biblioteca alpha.

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
#include <math.h>
#include "alpha.h"

Odds* oddsinit(const Language lang, const int n)
{
	int i;

	Odds *odds = (Odds*)malloc(sizeof(Odds));
	odds->lang = lang;
	odds->seq_len = n;

	// Español?
	if (lang == ALPHA_ES)
		odds->alpha_len = ALPHA_ES_LENGTH; 
	else
		odds->alpha_len = ALPHA_EN_LENGTH; 

	// Longitud total de mi alfabeto
	odds->odds_len = (unsigned int)powf((float)odds->alpha_len,(float)n);
	// Reserva de memoria para las probabilidades
	odds->odds = (odds_u*)malloc(sizeof(odds_u)*odds->odds_len);

	// Los valores son equiprobables
	for (i=0;i<odds->odds_len;++i)
		odds->odds[i] = 1./odds->odds_len;

	return odds;
}

void oddsdestroy(Odds *odds)
{
	free(odds->odds);
	free(odds);
}

void oddscalc(Odds *odds, const char *fin)
{
	const int len = odds->odds_len;
	const int n = odds->seq_len;
	int c[odds->seq_len],i,k,seq[len], num, next, correct;
	long pos;
	FILE *f;

	if((f = fopen(fin,"r")) == NULL)
	{
		perror("Input file open failed");
		exit(1);
	}

	for(i=0; i<len; ++i)
		seq[i] = 0;

	num = 0;
	next = 1;
	pos = 0L;
	do
	{

		// Mediante next se si he alcanzado el final del fichero
		// si es asi desprecio la secuencia sin terminar y me salgo
		for (i=0;i<n && next;++i)
			next = ((c[i]=getc(f)) != EOF);

		if (next)
		{
			// Una vez leidos los caracteres hago el conteo, si uno de los caracteres
			// no pertenece al alfabeto descarto la secuencia.
			k = 0;
			correct = 1;
			for (i=0;i<n && correct;++i)
			{
				if(c[i] >= 'A' && c[i] <= 'Z') // Mayusculas
					k += (int)(c[i]-'A') * (int)powf((float)odds->alpha_len, (float)(n-i-1) );
				else if(c[i] >= 'a' && c[i] <= 'z') // Minusculas
					k += (int)(c[i]-'a') * (int)powf((float)odds->alpha_len, (float)(n-i-1) );
				else if (odds->lang == ALPHA_ES) // Si el idioma es español
				{
					if (c[i]==ENNE || c[i]==M_ENNE) // Eñe
						k += (odds->alpha_len-1) * (int)pow((float)odds->alpha_len, (float)(n-i-1) );
					else
					switch(c[i]) // Vocales acentuadas
					{
						case AACUTE:
							//k += 
							break;
						case EACUTE:
							k += 4 * (int)pow((float)odds->alpha_len, (float)(n-i-1) );
							break;
						case IACUTE:
							k += 8 * (int)pow((float)odds->alpha_len, (float)(n-i-1) );
							break;
						case OACUTE:
							k += 14 * (int)pow((float)odds->alpha_len, (float)(n-i-1) );
							break;
						case UACUTE:
							k += 20 * (int)pow((float)odds->alpha_len, (float)(n-i-1) );
							break;
						default:
							correct = 0;
							break;
					}
				}
				else correct = 0;
			}

			#ifdef __ALPHA_READ_BYTE_BY_BYTE__

			if (correct)
			{
				seq[k]++;
				num++;
			}

			// Leo de caracter en caracter aunque
			// el tamaño de la secuencia sea > 1
			fseek(f, ++pos, SEEK_SET);

			#else

			if (correct)
			{
				seq[k]++;
				num++;
				pos+=odds->seq_len;
			}
			else fseek(f, ++pos, SEEK_SET);

			#endif

		}


	} while(next);

	// Cierro el fichero, ya no lo necesito
	fclose(f);
	
	// Calculo de probabilidades
	for(i=0; i<len; ++i)
		odds->odds[i] = (odds_u) seq[i] / (odds_u) num;

}

inline odds_u oddsdistfunc(Odds *odds, const int k)
{
	register int i;
	odds_u sum;

	sum = 0.;
	for (i=0;i<k+1;++i)
		sum += odds->odds[i];

	return sum;
}

void oddsprint(Odds *odds, const char *fodds)
{

	FILE *f;
	int i,j,k;
	char buf[odds->seq_len+1];
	const int len = odds->odds_len;

	if (fodds != NULL)
	{
		if((f = fopen(fodds,"w")) == NULL)
		{
			perror("Output file open failed");
			exit(1);
		}
	}
	else f = stdout;

	buf[odds->seq_len] = 0;
	for (i=0;i<len;++i)
	{
		k = i;
		for (j=odds->seq_len-1;j>=0;--j)
		{
			buf[j] = ( (odds->lang==ALPHA_ES && ((k+1)%odds->alpha_len) == 0 ) ? ( M_ENNE ) : ( 'A' + (k%odds->alpha_len) ) );
			k = k/odds->alpha_len;
		}

		fprintf(f,"%s\t%f\n",buf,odds->odds[i]);
	}

	if (fodds != NULL)
		fclose(f);
}

