#include <iostream>
#include "bintreeutils.h"
#include "graficos.h"

using namespace std;

int main() {

	srand( (unsigned)time( NULL ) ); // init Rand() function

	bintree<int> arbol;
	bintree<string> arbol2;

	CrearVentana(640,480,"abb");

	int j;
	for (int i=0;i<12;i++) {
		do{
			j=rand() % 100;
		}while(existe(arbol,j));
		cout<<j<<','<<endl;
		arbol=insertar_abb(arbol,j);
		arbol2=pasar_a_string(arbol);
		LimpiarVentana();
		dibujar(arbol2.root(),320,20,0);
		click();
	}
	cout<<endl;

}
