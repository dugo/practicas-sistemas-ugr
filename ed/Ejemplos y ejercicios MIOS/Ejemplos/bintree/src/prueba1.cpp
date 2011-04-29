#include <iostream>
#include "bintreeutils.h"
#include "graficos.h"

int main() {

	srand( (unsigned)time( NULL ) ); // init Rand() function

	bintree<char> arbol=construir_char(5);

	bintree<int> arbol3=construir_int(5,0);

	bintree<string> arbol2=pasar_a_string(arbol3);

	CrearVentana(640,480,"bintreedraw");

	dibujar(arbol2.root(),320,20,0);

	click();

}
