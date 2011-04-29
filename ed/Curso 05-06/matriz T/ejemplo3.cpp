//fichero ejemplo3.cpp
#include <iostream>
#include <list>
#include "matriz.h"
#include "ejemplos.h"

int main() {

matriz<int> m1(2,3);
matriz<int> m2(3,3);
matriz<int> m3(3,3);

m1.set(0,0,3);
m1.set(0,1,2);
m1.set(0,2,10);
m1.set(1,0,4);
m1.set(1,1,9);
m1.set(1,2,6);

m2.set(0,0,4);
m2.set(0,1,3);
m2.set(0,2,12);
m2.set(1,0,2);
m2.set(1,1,5);
m2.set(1,2,8);
m2.set(2,0,10);
m2.set(2,1,20);
m2.set(2,2,1);

m3.set(0,0,7);
m3.set(0,1,20);
m3.set(0,2,4);
m3.set(1,0,1);
m3.set(1,1,5);
m3.set(1,2,12);
m3.set(2,0,4);
m3.set(2,1,6);
m3.set(2,2,7);

cout<<"Matriz1:"<<m1;
cout<<"Matriz2:"<<m2;
cout<<"Matriz3:"<<m3;

list<matriz<int> > l;
l.push_back(m1);
l.push_back(m2);
l.push_back(m3);


cout<<"Matriz1*Matriz2*Matriz3:"<<multiplicar(l);

return 0;
}

matriz<int> multiplicar(const list<matriz<int> > &entrada) {

  list<matriz<int> >::const_iterator i;
  matriz<int> aux, salida;
  int g, k, h, t;
  bool imposible;

  if (entrada.size() == 1)
    return *entrada.begin();

  if (entrada.size() == 0)
    return matriz<int>();

  salida = *entrada.begin();
  i = ++entrada.begin();

  imposible = false;
  while(i!=entrada.end() && !imposible) {
    aux = salida;
    if (aux.ncols() != i->nfilas())
      imposible = true;
    else {
      salida = matriz<int>(aux.nfilas(), i->ncols());
      for (g = 0;g<salida.nfilas();g++)
        for (k = 0;k<salida.ncols();k++) {
          h = t = 0;
          while (h<aux.ncols()) {
            t += aux.get(g,h) * i->get(h,k);
            h++;
          }
          salida.set(g,k,t);
        }
    }
  ++i;
  }

  if (imposible)
    return matriz<int>();
  else
    return salida;

}
