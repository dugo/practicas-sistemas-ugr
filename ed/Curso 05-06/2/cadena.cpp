// cadena.cpp
#include <string.h>
#include "cadena.h"

using namespace std;

/**
 * @brief Constructor por defecto. No requiere ningun parametro.
 * Inicializa el objeto a una cadena vacia de cero caracteres.
 */
cadena::cadena()
{
	pstr = new char[1];
	strcpy(pstr, "");
	nchar = 0;
}


/**
 * @brief Constructor general. Crea un objeto que contiene la cadena de
 * caracteres que se le pasa como argumento.
 * @param c puntero a una cadena de caracteres cualquiera. Debe tener un '\0' al final.
 */
cadena::cadena(char* c)
{
	nchar = strlen(c);
	pstr = new char[nchar + 1];
	strcpy(pstr, c);
}

/**
 * @brief Constructor de copia.
 * @param cd referencia constante a un objeto cadena.
 */
cadena::cadena(const cadena& cd)
{
	nchar = cd.nchar;
	pstr = new char[nchar +1];
	strcpy(pstr, cd.pstr);
}

/**
 * @brief Destructor de la clase. Es necesario ya que se va utilizar
 * reserva dinamica de memoria.
 */
cadena::~cadena()
{
	delete [] pstr;
}

/**
 * @brief Permite cambiar el valor de la cadena de caracteres que contiene
 * un objeto cadena.
 * @param c puntero a char que contiene la direccion del primer caracter
 *  del texto a introducir. Debe tener un '\0' al final.
 */
void cadena::setcad(char* c)
{
	nchar = strlen(c);
	delete [] pstr;
	pstr = new char[nchar + 1];
	strcpy(pstr, c);
}

/**
 * @brief Sobrecarga del operador de asignacion.
 * @param cd referencia const a un objeto cadena. Es una referencia constante pues no ha de ser modificada.
 * @return referencia al objeto cadena asignado. Asi permite hacer sentencias del tipo a=b=c.
 */
cadena& cadena::operator= (const cadena& cd)
{
	if(*this != cd) {
		nchar = cd.nchar;
		delete [] pstr;
		pstr = new char[nchar + 1];
		strcpy(pstr, cd.pstr);
	}
	return *this;
}

/**
 * @brief Concatena dos objetos de la clase cadena y devuelve un nuevo objeto cadena
 * cuyo texto es la concatenacion de las dos cadenas de caracteres.
 * @param b referencia constante a un objeto cadena
 * @return objeto cadena resultado de la concatenacion.
 */
cadena cadena::operator+ (const cadena& b) const
{
	cadena c;
	c.nchar = nchar + b.nchar;
	c.pstr = new char[c.nchar + 1];
	strcpy(c.pstr, pstr);
	strcat(c.pstr, b.pstr);
	return c;
}



/**
 * @brief Concatena un objeto de la clase cadena y una cadena de caracteres estandar
 * y devuelve un nuevo objeto cadena cuyo texto es la concatenacion de
 * las dos cadenas de caracteres.
 * @param ch puntero un vector de caracteres. Debe tener un '\0' al final.
 * @return objeto cadena resultado de la concatenacion.
 */
cadena cadena::operator+ (const char* ch) const
{
	cadena c;
	c.nchar = nchar + strlen(ch);
	c.pstr = new char[c.nchar + 1];
	strcpy(c.pstr, pstr);
	strcat(c.pstr, ch);
	return c;
}


/**
 * @brief Operador suma para realizar concatenacion de cadenas. Se declaran como
 * friend, asi que no tiene argumento implicito.
 * Concatena un objeto de la clase cadena y una cadena de caracteres estandar
 * y devuelve un nuevo objeto cadena cuyo texto es la concatenacion de
 * las dos cadenas de caracteres operando.
 * @param ch puntero un vector de caracteres. Debe tener un '\0' al final.
 * @param b referencia constante a un objeto cadena
 * @return objeto cadena resultado de la concatenacion.
 */
cadena operator+ (const char* ch, const cadena& b)
{
	cadena c;
	c.nchar = strlen(ch) + b.nchar;
	c.pstr = new char[c.nchar + 1];
	strcpy(c.pstr, ch);
	strcat(c.pstr, b.pstr);
	return c;
}


/**
 * @brief Operador relacional de igualdad. Permite comparar el texto
 * de dos objetos cadena.
 * @param c2 referencia constante a un objeto cadena.
 * @return true cuando ambos textos son iguales, o false si los textos son
 *	   distintos.
 */
bool cadena::operator== (const cadena& c2) const
{
	return (strcmp(pstr, c2.pstr)==0);
}


/**
 * @brief Operador relacional de igualdad. Permite comparar el texto
 * de un objeto cadena y un vector de caracteres.
 * @param c2 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son iguales, o false si los textos son
 *	   distintos.
 */
bool cadena::operator== (const char* c2) const
{
	return (strcmp(pstr, c2)==0);
}

/**
 * @brief Operador relacional de igualdad. Permite comparar el texto
 * de un vector de caracteres y un objeto cadena.
 * @param c1 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @param c2 referencia constante a un objeto cadena.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son iguales, o false si los textos son
 *	   distintos.
 */
bool operator== (const char* c1, const cadena& c2)
{
	return (strcmp(c1, c2.pstr)==0);
}


/**
 * @brief Operador relacional 'distinto de'. Permite comparar el texto
 * de dos objetos cadena.
 * @param c2 referencia constante a un objeto cadena.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son distintos, o false si los textos son
 *	   iguales.
 */
bool cadena::operator!= (const cadena& c2) const
{
	return strcmp(pstr, c2.pstr)!=0;
}

/**
 * @brief Operador relacional 'distinto de'. Permite comparar el texto
 * de un objeto cadena y un vector de caracteres.
 * @param c2 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son distintos, o false si los textos son
 *	   iguales.
 */
bool cadena::operator!= (const char* c2) const
{
	return strcmp(pstr, c2)!=0;
}


/**
 * @brief Operador relacional 'distinto de'. Permite comparar el texto
 * de un vector de caracteres y un objeto cadena.
 * @param c1 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @param c2 referencia constante a un objeto cadena.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son distintos, o false si los textos son
 *	   iguales.
 */
bool operator!= (const char* c1, const cadena& c2)
{
  return strcmp(c1, c2.pstr)!=0;
}


/**
 * @brief Permite conocer la longitud de objeto cadena.
 * @return Devuelve la longitud o numero de caracteres del objeto
 * cadena que invoque el metodo
 */
int cadena::longitud() const
{
	return 0;
}

/**
 * @brief Permite extraer caracteres aislados de un objeto cadena.
 * @param i entero que indica la posicion del caracter a extraer. 0 <= i < longitud().
 * @return char el caracter i-esimo del objeto cadena que invoque el modo
 */
char cadena::getChar(int i) const
{
	return '\0';
}


/**
 * @brief Permite establecer o cambiar caracteres concretos de un objeto cadena.
 * @param i entero que indica la posicion del caracter a cambiar o extraer. 0 <= i < longitud().
 * @param c char con el caracter que se fijara en la posicion i del texto del objeto que invoca el metodo.
 */
void cadena::setChar(int i, char c)
{
	return;
}

/**
 * @brief Permite extraer o conocer subacadenas dentro de un objeto cadena.
 * @param ini entero que indica la posicion de inicio de la subcadena a extraer. 0 <= ini < longitud().
 * @param fin entero que inidica la posicion de fin de la subcadena a extraer. 0 <= fin < longitud() && ini <= fin.
 */
cadena cadena::subCadena(int ini, int fin) const
{
	return cadena();
}


/**
 * @brief Operador de insercion en el flujo de salida. Su finalidad el poder imprimir objetos cadena
 * en cualquier flujo de salida.
 * @param os referencia a un flujo de salida.
 * @param cad referencia constante al objeto cadena que se desea insertan en dicho flujo.
 * @return referencia al flujo de salida en el que ya se habria introducido el objeto cadena.
 */
ostream &operator<< (ostream & os, const cadena & cad)
{
	os << cad.pstr;
	return os;
}

// fin del fichero cadena.cpp

