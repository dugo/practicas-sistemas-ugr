/* ============================================================
   
   Estructuras de datos y algoritmos
   F.I. - U.P.V.

   FICHERO abb.h

   ============================================================= */

#ifndef _ABB_
#define _ABB_

#include <iostream>
using namespace std;

struct nodo_abb { // clase auxiliar para representar un nodo
  int valor;
  nodo_abb *izq, *der;
  // métodos
  void borrar_hijos();
  nodo_abb(int v,  nodo_abb *i=0, nodo_abb *d=0) : valor(v), izq(i), der(d) {};
  nodo_abb* buscar(int v);
  nodo_abb* insertar(int v);
  nodo_abb* insertar(nodo_abb* nodo);
  nodo_abb* maximo();
  nodo_abb* minimo();
  nodo_abb* predecesor(int v);
  nodo_abb* sucesor(int v);
  void imprime_arbol(ostream &s);
  void imprime_inorden(ostream &s);
  void imprime_preorden(ostream &s);
  void imprime_postorden(ostream &s);
};

class abb { // clase árbol binario de búsqueda
  nodo_abb *raiz;
public:
  abb(); // constructor
  ~abb(); // destructor
  bool maximo(int& v);
  bool minimo(int& v);
  bool buscar(int v);
  bool borrar(int v);
  bool predecesor(int &v);
  bool sucesor(int &v);
  void insertar(int elemento);
  void imprime_arbol(ostream &s);
  void imprime_inorden(ostream &s);
  void imprime_preorden(ostream &s);
  void imprime_postorden(ostream &s);
};

ostream& operator << (ostream& s, abb &el_abb);

#endif // _ABB_
