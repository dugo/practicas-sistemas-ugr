//fichero ejemplo1.cpp
#include <iostream>
#include "ejemplos.h"
#include "matriz.h"

using namespace std;

int main() {

matriz<int> m(4,4);

//Construimos una matriz "mágica" de dimensiones 4x4
m.set(0,1,5);
m.set(1,3,5);
m.set(2,2,5);
m.set(3,0,5);


cout<<"Matriz:"<<m;
cout<<"Mágica (0/1): "<<magica(m)<<endl<<endl;

m.set(0,1,6);
cout<<"Matriz:"<<m;
cout<<"Mágica (0/1): "<<magica(m)<<endl;

  return 0;
}

bool magica(const matriz<int> &entrada) {

  if (entrada.nfilas() != entrada.ncols())
    return false;

  bool magica = true;
  int i , g , valor, aux, f , c;

  valor = 0;
  f = entrada.nfilas();
  c = entrada.ncols();

  for (i = 0; i < c; i++)
    valor+=entrada.get(0,i);        //Suma de la primera fila.

  i = 0;
  while(i<f && magica) {  //Bucle para las filas.

    aux = 0;
    for (g = 0; g < c; g++)
      aux+=entrada.get(i , g);

    if (aux != valor)
      magica = false;

  i++;
  }


  i = 0;
  while(i<c && magica) {  //Bucle para las columnas.

    aux = 0;
    for (g = 0; g < f; g++)
      aux+=entrada.get(g , i);

    if (aux != valor)
      magica = false;

  i++;
  }


  if (magica) { //Para la diagonal principal.
    aux = 0;
    for (i = 0; i < f; i++)
        aux+=entrada.get(i , i);

      if (aux != valor)
        magica = false;
  }

  if (magica) { //Para la diagonal secundaria.
    aux = 0;
    for (i = 0; i < f; i++)
        aux+=entrada.get(i , c - i -1);

      if (aux != valor)
        magica = false;
  }

  return magica;
}
