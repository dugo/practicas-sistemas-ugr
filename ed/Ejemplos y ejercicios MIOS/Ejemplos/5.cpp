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
          
     

void Reemplazar(stack<int> &pila,int viejo,int nuevo){

     if (pila.empty()) return;     
   
	int ultimo = (pila.top()==viejo)?nuevo:pila.top();
	pila.pop();
	Reemplazar(pila,viejo,nuevo);
	pila.push(ultimo);

     
     
     }

int main() {

  srand( (unsigned)time( NULL ) ); // init Rand() function

  stack<int> pila;

  int j;
  int viejo,nuevo;
  for (int i=0;i<10;i++) {
          j=rand() % 5;
          //cout<<j<<',';
          pila.push(j);
          }
 
  Mostrar(pila);

  cout << endl << "Valor viejo: ";
  cin>>viejo;
  cout << "Valor nuevo: ";
  cin>>nuevo;
  
  Reemplazar(pila,viejo,nuevo);
  
  Mostrar(pila);
  
  cout << endl;
  
}
