//fichero funciones.cpp
#include <iostream>
#include "funciones.h"

using namespace std;

/**
 * @brief Funcion de inserccion de una cadena en otra.
 * @param cad referencia al objeto cadena con el texto en el que se 
 * 	       insertara un nuevo texto.
 * @param inserta referencia al objeto cadena con el texto que se insertara.
 * @param pos entero con la posicion a partir de la cual se insertara la cadena inserta en 
 *	  la cadena cad.
 * @return objeto nuevo cadena con el texto compuesto por la insercion del 
 *	   texto del objeto inserta en el texto de la cadena cad a partir de la posicion pos.
 */
cadena insertarCadena(const cadena& cad, const cadena& inserta, int pos){
	return cadena();
}


/**
 * @brief Funcion que determina si el texto contenido en el objeto cadena es un palindromo.
 * @param cad referencia a objeto cadena.
 * @return devuelve true si el texto del objeto cadena cad es un palindromo y false
 *	   en caso contrario.
 */
bool palindromo(const cadena& cad){
	return true;
}


int main(int argc, char *argv[])
{
}
