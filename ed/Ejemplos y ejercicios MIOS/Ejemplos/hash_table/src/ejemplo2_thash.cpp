// Ejemplo de utilización de una tabla hash

#include <iostream>
#include "hash_table.h"

using namespace std;

int main()
{
  hash_table<int,int> th(23);
  int i;

	th.insert(10,10);
	th.insert(20,30);

	int c;

cout<<(typeof(c) == typeof(int)) <<endl;
	cout<<th.find(20,c)<<endl;
	cout<<static_cast<int>(c)<<endl;

  return 0;
}
