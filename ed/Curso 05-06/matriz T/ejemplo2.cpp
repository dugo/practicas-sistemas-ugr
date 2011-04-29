//fichero ejemplo2.cpp
#include <iostream>
#include <list>
#include "matriz.h"
#include "ejemplos.h"

using namespace std;

int main() {

  matriz<double> m(4,4,50.0);

  m.set(0,3,4.5);
  m.set(0,2,4.0);
  m.set(0,1,5.0);
  m.set(1,0,34.0);
  m.set(1,3,1.0);
  m.set(2,0,10.0);
  m.set(2,1,6.0);
  m.set(2,3,7.0);
  m.set(3,0,10.0);
  m.set(3,1,7.0);
  m.set(3,2,5.0);
  m.set(3,3,-3.0);

  cout<<"Matriz:"<<m;
  list<double> l;
  l = minimos_fila(m);
  list<double>::const_iterator i;

  cout << endl<<"Lista de los mínimos ordenada: ";
  for (i = l.begin();i!=l.end();++i) {

    if (i!=l.begin())
      cout<<",";

      cout <<*i;
  }

  cout<<endl;

  return 0;
}

template <class T>
list<T> minimos_fila(const matriz<T> &entrada) {

  list<T> lista;
  int i;

  for (i = 0;i<entrada.nfilas(); i++)
    lista.push_back(entrada.minimo_fila(i));

  lista.sort();

  return lista;
}
