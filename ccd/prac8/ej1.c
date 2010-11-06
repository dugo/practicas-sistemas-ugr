/*
	Compilar con: gcc -Wall ej1.c -o ej1 -lm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


enum FORMATO
{
	PGM,
	PBM
};


unsigned char *LeerImagen(const char *nombre, int *anch, int *alt, enum FORMATO *fmt, int *planos);
void EscribirImagenPGM(const char *nombre, const unsigned char *datos, const int ancho, const int alto);
void calcularSNR(const unsigned char *original, const unsigned char *reconstruida, const int tam, double *snr, double *snrdb);

int main(int argc, char **argv)
{

	printf("Realiza las tareas del ejercicio 1 del guion 8.\n");
	printf("NOTA: Solo trabaja con imagenes PGM.\n\n");

	if (argc!=3)
	{
		fprintf(stderr, "Parametros incorrectos.\nUso: %s <fichero original> <fichero comprimido>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned char *comprimida, *reconstruida, *original;
	char buf[100];
	double snr, snrdb;
	enum FORMATO fmt;
	int alto, ancho, planos, tam, i;

	original = LeerImagen(argv[1], &ancho, &alto, &fmt, &planos);
	comprimida = LeerImagen(argv[2], &ancho, &alto, &fmt, &planos);

	tam = alto*ancho;

	// Primer apartado del ejercicio, reconstruye los valores con +10
	reconstruida = (unsigned char*)malloc(sizeof(unsigned char)*tam);
	for (i=0;i<tam;i++)
		reconstruida[i] = comprimida[i]+10;

	strcpy(buf, argv[2]);
	strcat(buf, "-1");

	printf("Ejercicio 1\n===========\n");

	EscribirImagenPGM(buf, reconstruida, ancho, alto);
	calcularSNR(original, reconstruida, tam, &snr, &snrdb);

	printf("Escrita la imagen reconstruida sumando 10 a cada pixel en el fichero '%s'\n", buf);
	printf("SNR(RMS): %f\tSNR(DBS): %f\n\n",snr,snrdb);


	// Semilla aleatoria
	srand(time(NULL));

	for (i=0;i<tam;i++)
		reconstruida[i] = comprimida[i]+(unsigned char)(20.0*rand()/(RAND_MAX+1.0))-10;

	strcpy(buf, argv[2]);
	strcat(buf, "-2");

	EscribirImagenPGM(buf, reconstruida, ancho, alto);
	calcularSNR(original, reconstruida, tam, &snr, &snrdb);

	printf("Escrita la imagen reconstruida sumando o restando 10 a cada pixel aleatoriamente en el fichero '%s'\n", buf);
	printf("SNR(RMS): %f\tSNR(DBS): %f\n\n",snr,snrdb);

	free(original);
	free(comprimida);
	free(reconstruida);

	return EXIT_SUCCESS;
}

unsigned char *LeerImagen(const char *nombre, int *anch, int *alt, enum FORMATO *fmt, int *planos)
{

	char buf[3], aux;
	int ancho, alto, tam, maxval;
	enum FORMATO fmto;
	unsigned char *datos;
	FILE *f;

	if (!(f=fopen(nombre,"r")))
	{
		fprintf(stderr, "Error abriendo fichero de entrada");
		exit(EXIT_FAILURE);
	}

	// Leemos el formato y lo comprobamos.
	fgets(buf, 3, f);

	if (!strcmp(buf,"P5"))
	{
		fmto = PGM;
	}
	else if (!strcmp(buf,"P4"))
	{
		fmto = PBM;
		*planos = 1;
	}
	else
	{
		fprintf(stderr, "Error: Fichero de entrada corrupto o formato no soportado\n");
		exit(EXIT_FAILURE);
	}

	// Posicion lectura +1
	fseek(f, 1, SEEK_CUR);

	// Ignoramos los comentarios
	aux = fgetc(f);
 	while (aux=='#')
	{
		while (aux!='\n')
		{
		  aux = fgetc(f);
		}
	}

	if (aux!='\n') ungetc(aux, f);


	fscanf(f, "%d", &ancho);
	fscanf(f, "%d", &alto);
	if (fmto==PGM)
	{
		fscanf(f, "%d", &maxval);
		int i=1;
		*planos = 0;
		while(i<maxval)
		{
			i=i<<1;
			(*planos)++;
		}
	}

	tam = (fmto==PBM) ? (ancho*alto)/8 + 1 : (ancho*alto);

	#ifdef DEBUG
	printf("maxval: %d\n",maxval);
	printf("ancho: %d \t alto: %d\n",ancho,alto);
	printf("tam: %d\n",tam);
	printf("planos: %d\n",*planos);
	#endif

	datos = (unsigned char *) malloc(tam);

	do
	{
		aux = fgetc(f);
	}
	while(aux != '\n');


	if (fread(datos, 1, tam, f)<(tam-1))
	{
		fprintf(stderr, "Error: El tamaño del fichero de entrada no coincide con sus dimensiones\n");
		fclose(f);
		exit(EXIT_FAILURE);
	}

	fclose(f);

	*anch = ancho;
	*alt = alto;
	*fmt = fmto;

	return datos;
}

void EscribirImagenPGM(const char *nombre, const unsigned char *datos, const int ancho, const int alto)
{


	FILE *f;

	if (!(f=fopen(nombre,"w")))
	{
		fprintf(stderr,"Hubo un error al abrir el fichero de salida \"%s\".\n",nombre);
		exit(EXIT_FAILURE);
	}

	// Escribimos comentarios
	fprintf(f,
		"P5\n"
		"# Creador: Ruben Dugo Martin\n"
		"%d %d\n"
		"255\n"
		, ancho, alto
		);

	// Escribimos datos.
	fwrite((void*)datos, 1, ancho*alto, f);

	fclose(f);
}

void calcularSNR(const unsigned char *original, const unsigned char *reconstruida, const int tam, double *snr, double *snrdb)
{
	double media, sum1, sum2;
	int i;

	media = 0.;
	for (i=0;i<tam;i++)
		media += (double)original[i];

	media = media/(double)tam;

	sum1 = 0.;
	for (i=0;i<tam;i++)
		sum1 += pow(((double)original[i]-media), 2.);

	sum2 = 0.;
	for (i=0;i<tam;i++)
		sum2 += pow(((double)original[i]-(double)reconstruida[i]), 2.);

	*snr = sum1/sum2;

	*snrdb = 10*log(*snr);
}

