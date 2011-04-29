#ifndef __BINTREEUTILS__
#define __BINTREEUTILS__
#include <string>
#include "bintree.h"

using namespace std;

bintree<char> construir_char(int altura);
bintree<int> construir_int(int altura,int num);
bintree<string> pasar_a_string(bintree<char> arbol);
bintree<string> pasar_a_string(bintree<int> arbol);
void dibujar(bintree<string>::node arbol,int x,int y,int nivel);
void click();
bool existe(bintree<int> arbol,int valor);
bintree<int> insertar_abb(bintree<int> n,int valor);

#endif
