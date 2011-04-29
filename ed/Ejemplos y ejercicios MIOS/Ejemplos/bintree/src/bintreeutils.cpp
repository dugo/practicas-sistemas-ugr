#include <iostream>
#include "bintreeutils.h"
#include "graficos.h"

using namespace std;

bintree<char> construir_char(int altura) {

	bintree<char> arbol;

	if (altura==0)  return arbol;

	bintree<char> izq,der;

	izq=construir_char(altura-1);
	der=construir_char(altura-1);

	arbol=bintree<char>(static_cast<char>(rand() % ('Z'-'A'))+'A');
	arbol.insert_left(arbol.root(),izq );
	arbol.insert_right(arbol.root(),der);

	return arbol;
	
}

bintree<int> construir_int(int altura,int num) {

	bintree<int> arbol;

	if (altura==0)  return arbol;

	bintree<int> izq,der;

	izq=construir_int(altura-1,num+1);
	der=construir_int(altura-1,num+2);

	arbol=bintree<int>(num);
	arbol.insert_left(arbol.root(),izq );
	arbol.insert_right(arbol.root(),der);

	return arbol;
	
}

bintree<string> pasar_a_string(bintree<char> arbol) {

	bintree<string> ret;

	if (arbol.empty()) return ret;

	bintree<string> izq,der;
	bintree<char> izq1,der1;

	izq1.replace_subtree(izq1.root(),arbol,arbol.root().left());
	der1.replace_subtree(der1.root(),arbol,arbol.root().right());

	izq=pasar_a_string(izq1);
	der=pasar_a_string(der1);

	char texto[100];
	sprintf(texto,"%c",*arbol.root());

	string str(texto);
	ret=bintree<string>(str);
	ret.insert_left(ret.root(),izq);
	ret.insert_right(ret.root(),der);

	return ret;

}

bintree<string> pasar_a_string(bintree<int> arbol) {

	bintree<string> ret;

	if (arbol.empty()) return ret;

	bintree<string> izq,der;
	bintree<int> izq1,der1;

	izq1.replace_subtree(izq1.root(),arbol,arbol.root().left());
	der1.replace_subtree(der1.root(),arbol,arbol.root().right());

	izq=pasar_a_string(izq1);
	der=pasar_a_string(der1);

	char texto[100];
	sprintf(texto,"%d",*arbol.root());

	string str(texto);
	ret=bintree<string>(str);
	ret.insert_left(ret.root(),izq);
	ret.insert_right(ret.root(),der);

	return ret;

}

void dibujar(bintree<string>::node arbol,int x,int y,int nivel) {

	if (arbol.null()) return;


	if (nivel==0) {
		Texto(x,y,(*arbol).c_str(),0,0,255);
	}

	nivel++;

	if (!arbol.left().null()) {
		Texto(x-100/nivel,y+80/nivel,(*arbol.left()).c_str(),0,0,255);
		Linea(x,y,x-100/nivel,y+80/nivel,255,0,0);
		dibujar(arbol.left(),x-100/nivel,y+80/nivel,nivel);
	}

	if (!arbol.right().null()) {
		Texto(x+100/nivel,y+80/nivel,(*arbol.right()).c_str(),0,0,255);
		Linea(x,y,x+100/nivel,y+80/nivel,255,0,0);
		dibujar(arbol.right(),x+100/nivel,y+80/nivel,nivel);
	}
	

}



void click() {
	int x,y;ObtenerClick(x,y);
}

bool existe(bintree<int> arbol,int valor) {

	bintree<int>::inorder_iterator it;

	it=arbol.begin_inorder();
	bool enc;
	while (it!=arbol.end_inorder() && !enc) {
		enc=(*it==valor);
		it++;
	}
	return enc;
}

bintree<int> insertar_abb(bintree<int> arbol,int valor){

	if (arbol.empty()) {
		return bintree<int>(valor);
	}

	bintree<int> arbol2;

	if (valor<*arbol.root()) {
		arbol2.replace_subtree(arbol2.root(),arbol,arbol.root().left());
		arbol2=insertar_abb(arbol2,valor);
		arbol.insert_left(arbol.root(),arbol2);
	}
	else {
		arbol2.replace_subtree(arbol2.root(),arbol,arbol.root().right());
		arbol2=insertar_abb(arbol2,valor);
		arbol.insert_right(arbol.root(),arbol2);
	}

	return arbol;
}

