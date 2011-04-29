#include <iostream>
#include <list>
#include <queue>
#include "matriz.h"
#include "ejemplos.h"

int main() {

  matriz<int> m(3,3);
  m.set(0,0,4);
  m.set(0,1,3);
  m.set(0,2,12);
  m.set(1,0,2);
  m.set(1,1,5);
  m.set(1,2,8);
  m.set(2,0,10);
  m.set(2,1,20);
  m.set(2,2,1);

  cout<<"Matriz:"<<m;
  list<coordenadas<int> > l;
  l = ordenada(m);
  list<coordenadas<int> >::const_iterator i;

  cout << endl<<"Listado de las tripletas que componen la matriz: "<<endl;
  cout << "Ordenadas según el dato."<<endl;
  cout << " {dato, fila, columna}"<<endl;
  for (i = l.begin();i!=l.end();++i)
    cout<<" {"<<i->dato()<<", "<<i->nfila()<<", "<<i->ncol()<< "}"<<endl;

}

template <class T>
list<coordenadas<T> > ordenada(const matriz<T> &entrada){

  int i,g;
  priority_queue<coordenadas<T> > cola;
  list<coordenadas<T> > salida;

  for (i=0;i<entrada.nfilas();i++)
    for (g=0;g<entrada.ncols();g++) {
      cola.push(coordenadas<T>(entrada.get(i,g),i,g));
    }

  while (!cola.empty()) {
    salida.push_back(cola.top());
    cola.pop();
  }

  return salida;
}
