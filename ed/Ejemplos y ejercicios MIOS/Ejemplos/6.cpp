#include <iostream>
#include <time.h>
#include <stack>

using namespace std;

void Mostrar(stack<int> &pila){

     if (pila.empty()) return;
 
          int ultimo=pila.top();
          pila.pop();
          cout<<ultimo;
          
          if (!pila.empty()) cout<<",";

          Mostrar(pila);
          
          pila.push(ultimo);
          
}   
          
     

bool Sombrero(stack<int> &pila1,stack<int> &pila2){

     if (pila2.empty()) return false;
   
          int ultimo2=pila2.top();
          pila2.pop();
          Sombrero(pila1,pila2);
          pila1.push(ultimo);
   
     }

int main() {

  srand( (unsigned)time( NULL ) ); // init Rand() function

  stack<int> pila,pila2,pila3;
  

  int j;
  int viejo,nuevo;
  for (int i=0;i<10;i++) {
          j=rand() % 100;
          //cout<<j<<',';
          pila.push(j);

          if (i%4==0)  pila2.push(j);
          }

  pila3.push(100);

  cout << "Pila1:"; 
  Mostrar(pila);

  cout<<endl<<"Pila2:";
  Mostrar(pila2);

  cout<<endl<<"Pila3:";
  Mostrar(pila3);

  
  cout << endl;
  system("pause");
  
}
