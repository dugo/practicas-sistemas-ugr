// Ejemplo de utilización de una tabla hash

#include <iostream>
#include "hash_table.h"

using namespace std;

int main()
{
  hash_table<int,unsigned char> th(23);
  int i;

  for (i=1; i<134; i+=2){cout<<i<<endl;
    th.insert(i);}

  hash_table<int,unsigned char> th_2 = th;

  // Borramos algunos elementos (distintos para las 2 tablas hash)
  for (i= 35; i<134; i+=6) {
    th.erase(i);
    th_2.erase(i+2);
  }

  unsigned char aux;
  for (i=0; i<134; i++)
    if (th.find(i,aux))
      cout << i << " aparece en la tabla" << endl;

  hash_table<int,unsigned char>::const_iterator ite, ite_2;

  cout << endl << "pos dato" << endl;
  int k = 0;
  ite_2 = th_2.begin();
  for (ite = th.begin(); ite!=th.end(); ite++) {
    cout.width(2);
    cout << k << ": ";
    cout.width(3);
    cout << (*ite).first;
    if (ite_2!=th_2.end()) {
      cout << " ";
      cout.width(3);
      cout << (*ite_2).first;
      ite_2++;
    }
    cout << endl;
    // No se puede hacer esto *ite = 234
    k++;
  }

  return 0;
}
