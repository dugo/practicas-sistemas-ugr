/*
	Fichero alpha.h.
	Cabecera de la biblioteca alpha desarrollada para la asignatura CCD de la UGR.

	Rubén Dugo Martín <raubn.zero@gmail.com>
	11-4-08

	Licencia: GPL (http://www.gnu.org/licenses/gpl.html), por supuesto.

	ATENCION: El desarrollo de esta biblioteca es puramente academico, solo se puede
	garantizar el correcto funcionamiento para la realizacion de los ejercicios de
	practicas de la asignatura CCD.
*/
#ifndef __LIB_ALPHA__
#define __LIB_ALPHA__

/*
	Enumeracion Language, utilizada para seleccionar el idioma con el que trabajaremos.
	Actualmente solo esta soportado el ingles (ALPHA_EN) y el español (ALPHA_ES).
*/
enum Language
{
	ALPHA_EN,
	ALPHA_ES
} typedef Language;


/*
	Define el tipo en el que tratarán las probabilidades, la podemas cambiar por
	double si requerimos mas precision.
*/
typedef double odds_u;

/*
	Odds, estructura de probabilidades, su implementacion no interesa al programador, es usada por
	las funciones de la biblioteca.
	Almacena todo lo necesario para manejar probabilidades alfabeticas.

	NOTA: Antes de usarla es estrictamente necesario inicializarla.
*/
struct Odds
{
	odds_u *odds;
	Language lang;
	unsigned int alpha_len;
	unsigned int odds_len;
	unsigned int seq_len;
} typedef Odds;

/*
	Estas macros definen las longitudes de los alfabetos para ingles y español respectivamente.
*/
#define ALPHA_EN_LENGTH 26
#define ALPHA_ES_LENGTH 27

/*
	Definiendo la macro __ALPHA_ASCII__ activamos que las letras se lean como ASCII en lugar
	de ISO-8859-1 (ISO Latin 1).
	Esto solo afecta a las letras acentuadas y a la letra eñe.
*/
#ifdef __ALPHA_ASCII__
	#define AACUTE 160
	#define EACUTE 130
	#define IACUTE 161
	#define OACUTE 162
	#define UACUTE 163
	#define ENNE 164
	#define M_ENNE 165
#else
	#define AACUTE 225
	#define EACUTE 233
	#define IACUTE 237
	#define OACUTE 243
	#define UACUTE 250
	#define ENNE 241
	#define M_ENNE 209
#endif

/*
	Esta macro activa que en el conteo de frecuencias se lea byte a byte y no se desprecie
	los bytes sobrantes de una secuencia, con un ejemplo:

	Supongamos que estamos leyendo con secuencias de longitud 2 (pares de letras) la
	cadena abcd, con la macro definida en el conteo se tendra en cuenta las secuencias ab,bc y cd.
	Sin embargo con la macro sin definir solo se tendra en cuenta los pares ab y cd.

	Lo mismo ocurriria si leyeramos una cadena cuya longitud no fuera multiplo de la
	longitud de la secuencia, usando el mismo ejemplo anterior pero con la cadena abcde.
	Con la macro definida contariamos los pares ab,bc,cd y de y sin definirla solo
	leeriamos ab y cd.

	Solo afecta a la funcion oddscalc. Activada por defecto.
*/
#define __ALPHA_READ_BYTE_BY_BYTE__

/*
	Funcion oddsinit.
	Inicializa la estructura de las probabilidades a un idioma y con una longitud
	de secuencia determinadas.

	Parametros:
	lang: Idioma al que se quiere inicializar la estructura de probabilidades.
	n: Longitud de secuencia.

	Retorna un puntero a dicha estructua inicializada, inicialmente todos los elementos
	tiene la misma probabilidad.
*/
Odds* oddsinit(const Language lang, const int n);
/*
	Funcion oddsdestroy.
	Destruye una estructura de probabilidades.

	Parametros:
	odds: Puntero a la estructura que sera destruida.
*/
void oddsdestroy(Odds *odds);
/*
	Funcion oddscalc.
	Calcula las probabilidades de cada alfabeto desde un fichero dado.

	Parametros:
	odds: Estructura de probabilidades previamente inicializada en la que se almacenara las
	estadisticas del fichero.
	fin: Nombre del fichero de entrada.
*/

void oddscalc(Odds *odds, const char *fin);
/*
	Funcion oddsdistfunc.
	Funcion de distribucion de las probabilidades.

	Parametros:
	odds: Estructura de probabilidades desde la cual se leera la informacion estadistica.
	k: Elemento del que se devuelve su valor de la funcion de distribucion.
*/
inline odds_u oddsdistfunc(Odds *odds, const int k);
/*
	Funcion oddsprint.
	Imprime a un flujo el contenido estadistico de una estructura de probabilidades.

	Parametros:
	odds: Puntero a una estructura de probabilidades de la cual se imprimira la informacion.
	fodds: Nombre del fichero donde queremos que se imprima dicha informacion, si el
	puntero es NULL lo imprime por stdout.
*/
void oddsprint(Odds *odds, const char *fodds);

/*
	Funcion gendictionary.
	Genera un diccionario pseudo-aleatorio con las caracteristicas determinadas.

	Parametros:
	odds: Puntero a una estructura de probabilidades previamente inicializada y mediante
	la informacion estadistica que contiene se generara el diccionario.
	wordlength: Longitud de cada palabra del diccionario.
	words: Numero de palabras del diccionario.
	fdic: Nombre del fichero donde se guardara el diccionario.
*/
void gendictionary(Odds *odds, int wordlength, const int words, const char *fdic);
/*
	Funcion genword.
	Genera una palabra pseudo-aleatoria.

	odds: Puntero a una estructura de probabilidades previamente inicializada y mediante
	la informacion estadistica que contiene se generara la palabra.
	word: Vector de caracteres donde se guardara la palabra generada.
	length: Longitud de la palabra a generar.
*/
void genword(Odds *odds, char *word, const int length);

#endif

