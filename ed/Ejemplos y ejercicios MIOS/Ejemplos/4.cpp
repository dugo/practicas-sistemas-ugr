#include <iostream>
#include <time.h>
#include <set>

using namespace std;

int main() {

  srand( (unsigned)time( NULL ) ); // init Rand() function

  set<int,greater<int> > conjunto;

  int j;
  int viejo,nuevo;
  for (int i=0;i<10;i++) {
          j=rand() % 100;
          cout<<j<<',';
          conjunto.insert(j);
          }
 cout<<endl;
  set<int,greater<int> >::iterator it;
  
  for (it=conjunto.begin();it!=conjunto.end();it++)
      cout<<*it<<',';
  
  cout<<endl<<"Buscar: ";
  cin>>j;
  
  if (conjunto.find(j) == conjunto.end())
     cout<<"No encontrado";
  else cout << "Encontrado";
  
  
  cout << endl;
  system("pause");
  
}
