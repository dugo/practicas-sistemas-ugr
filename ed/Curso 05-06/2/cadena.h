// fichero cadena.h
#include <iostream>

#ifndef __CADENA_H
#define __CADENA_H

using namespace std;


/**
 * @brief Esta clase es una version reducida de la clase 'string' de la libreria STL, para
 * el manejo de cadenas de caracteres.
 */
class cadena {
private:
	char* pstr; /**< puntero a un vector de caracteres. */
	int nchar;  /**< n de caracteres (sin el '\0').    */

public:

/**
 * @brief Constructor por defecto. No requiere ningun parametro.
 * Inicializa el objeto a una cadena vacia de cero caracteres.
 */
cadena();

/**
 * @brief Constructor general. Crea un objeto que contiene la cadena de
 * caracteres que se le pasa como argumento.
 * @param c puntero a una cadena de caracteres cualquiera. Debe tener un '\0' al final.
 */
cadena(char* c);

/**
 * @brief Constructor de copia.
 * @param cd referencia constante a un objeto cadena.
 */
cadena(const cadena& cd);

/**
 * @brief Destructor de la clase. Es necesario ya que se va utilizar
 * reserva dinamica de memoria.
 */
~cadena();

/**
 * @brief Permite cambiar el valor de la cadena de caracteres que contiene
 * un objeto cadena.
 * @param c puntero a char que contiene la direccion del primer caracter
 *  del texto a introducir. Debe tener un '\0' al final.
 */
void setcad(char* c);


/**
 * @brief Sobrecarga del operador de asignacion.
 * @param cd referencia const a un objeto cadena. Es una referencia constante pues no ha de ser modificada.
 * @return referencia al objeto cadena asignado. Asi permite hacer sentencias del tipo a=b=c.
 */
cadena& operator= (const cadena& cd);

/**
 * @brief Concatena dos objetos de la clase cadena y devuelve un nuevo objeto cadena
 * cuyo texto es la concatenacion de las dos cadenas de caracteres.
 * @param b referencia constante a un objeto cadena
 * @return objeto cadena resultado de la concatenacion.
 */
cadena operator+ (const cadena& b) const;

/**
 * @brief Concatena un objeto de la clase cadena y una cadena de caracteres estandar
 * y devuelve un nuevo objeto cadena cuyo texto es la concatenacion de
 * las dos cadenas de caracteres.
 * @param ch puntero un vector de caracteres. Debe tener un '\0' al final.
 * @return objeto cadena resultado de la concatenacion.
 */
cadena operator+ (const char* ch) const;


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
friend cadena operator+ (const char* ch, const cadena& b);


/**
 * @brief Operador relacional de igualdad. Permite comparar el texto
 * de dos objetos cadena.
 * @param c2 referencia constante a un objeto cadena.
 * @return true cuando ambos textos son iguales, o false si los textos son
 *	   distintos.
 */
bool operator== (const cadena& c2) const;


/**
 * @brief Operador relacional de igualdad. Permite comparar el texto
 * de un objeto cadena y un vector de caracteres.
 * @param c2 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son iguales, o false si los textos son
 *	   distintos.
 */
bool operator== (const char* c2) const;

/**
 * @brief Operador relacional de igualdad. Permite comparar el texto
 * de un vector de caracteres y un objeto cadena.
 * @param c1 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @param c2 referencia constante a un objeto cadena.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son iguales, o false si los textos son
 *	   distintos.
 */
friend bool operator== (const char* c1, const cadena& c2);


/**
 * @brief Operador relacional 'distinto de'. Permite comparar el texto
 * de dos objetos cadena.
 * @param c2 referencia constante a un objeto cadena.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son distintos, o false si los textos son
 *	   iguales.
 */
bool operator!= (const cadena& c2) const;


/**
 * @brief Operador relacional 'distinto de'. Permite comparar el texto
 * de un objeto cadena y un vector de caracteres.
 * @param c2 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son distintos, o false si los textos son
 *	   iguales.
 */
bool operator!= (const char* c2) const;


/**
 * @brief Operador relacional 'distinto de'. Permite comparar el texto
 * de un vector de caracteres y un objeto cadena.
 * @param c1 puntero a un vector de caracteres. Debe tener un '\0' al final.
 * @param c2 referencia constante a un objeto cadena.
 * @return valor de comparacion que devuelve true, cuando
 *	   ambos textos son distintos, o false si los textos son
 *	   iguales.
 */
friend bool operator!= (const char* c1, const cadena& c2);


/**
 * @brief Permite conocer la longitud de objeto cadena.
 * @return Devuelve la longitud o numero de caracteres del objeto 
 * cadena que invoque el metodo
 */
int longitud() const;

/**
 * @brief Permite extraer caracteres aislados de un objeto cadena. 
 * @param i entero que indica la posicion del caracter a extraer. 0 <= i < longitud().
 * @return char el caracter i-esimo del objeto cadena que invoque el modo
 */
char getChar(int i) const;

/**
 * @brief Permite establecer o cambiar caracteres concretos de un objeto cadena. 
 * @param i entero que indica la posicion del caracter a cambiar o extraer. 0 <= i < longitud().
 * @param c char con el caracter que se fijara en la posicion i del texto del objeto que invoca el metodo.
 */
void setChar(int i, char c);

/**
 * @brief Permite extraer o conocer subacadenas dentro de un objeto cadena.
 * @param ini entero que indica la posicion de inicio de la subcadena a extraer. 0 <= ini < longitud().
 * @param fin entero que inidica la posicion de fin de la subcadena a extraer. 0 <= fin < longitud() && ini <= fin.
 */
cadena subCadena(int ini, int fin) const;

/**
 * @brief Operador de insercion en el flujo de salida. Su finalidad el poder imprimir objetos cadena
 * en cualquier flujo de salida.
 * @param os referencia a un flujo de salida.
 * @param cad referencia constante al objeto cadena que se desea insertan en dicho flujo.
 * @return referencia al flujo de salida en el que ya se habria introducido el objeto cadena.
 */
friend ostream &operator<<(ostream& os, const cadena& cad);

};




#endif // __CADENA_H
