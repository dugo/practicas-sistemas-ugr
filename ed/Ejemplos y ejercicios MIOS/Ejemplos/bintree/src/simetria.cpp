#include <iostream>
#include "bintreeutils.h"
#include "graficos.h"

using namespace std;

bool simetria(bintree<int>::node a1,bintree<int>::node a2) {

	if (a1.null() && a2.null()) return true;

	if ((a1.left().null()) && !(a2.right().null())) return false;
	if (!(a1.left().null()) && (a2.right().null())) return false;
	if ((a1.right().null()) && !(a2.left().null())) return false;
	if (!(a1.right().null()) && (a2.left().null())) return false;

	if ((a1.left().null() && a2.right().null() || *a1.left()==*a2.right()) &&
		(a1.right().null() && a2.left().null() || *a1.right()==*a2.left()))
			return (simetria(a1.left(),a2.left())&&simetria(a1.right(),a2.right()));
	else return false;

}

int main() {

	bintree<int> arbol1(10),arbol2(10);

	bintree<string> arbol_pintar;

	CrearVentana(800,600,"simetria arborea");

	arbol1.insert_left(arbol1.root(),20);
	arbol1.insert_right(arbol1.root().left(),13);
	arbol1.insert_right(arbol1.root(),24);
	arbol1.insert_left(arbol1.root().right(),1);
	arbol1.insert_right(arbol1.root().right(),2);

	arbol_pintar=pasar_a_string(arbol1);

	dibujar(arbol_pintar.root(),270,20,0);

	arbol1.insert_right(arbol1.root(),20);
	arbol1.insert_left(arbol1.root().right(),13);
	arbol1.insert_left(arbol1.root(),24);
	arbol1.insert_right(arbol1.root().left(),1);
	arbol1.insert_left(arbol1.root().left(),2);

	arbol_pintar=pasar_a_string(arbol1);

	dibujar(arbol_pintar.root(),540,20,0);

	click();

	if (simetria(arbol1.root(),arbol2.root())) {
		cout << "Simetria"<<endl;
	}
	else	cout << "NO Simetria"<<endl;

	click();

}
