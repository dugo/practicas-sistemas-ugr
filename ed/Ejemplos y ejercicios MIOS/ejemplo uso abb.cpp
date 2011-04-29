#include <iostream>
#include <time.h>

using namespace std;

class Nodo {
  Nodo *izq;
  Nodo der;
  int valor;     
};

Nodo BST;

Nodo init(int valor) {

     Nodo n;
     n.izq=n.der=0;
     n.valor=valor;
     
     return n;
      }

void add(Nodo &nuevo,Nodo &voy) {
     
     
     if (&voy == 0)  voy = nuevo;
     else {
          if (nuevo.valor >= voy.valor)
             voy = voy.der;
          else
             voy = voy.izq;
             
             add(nuevo,voy);
          
          }
     }

void Mostrar(Nodo &n) {
          
          
          if (n!=0) {
                    cout << n.valor << ',' << n->izq.valor << ',' << n.der->valor<<endl;
                    Mostrar(n.der);
                    Mostrar(n.izq);
                    }
     }

int main(){
    
    &BST = 0;

  srand( (unsigned)time( NULL ) ); // init Rand() function

  int j;
  for (int i=0;i<10;i++) {
      
      //if (i==0) BST = init(j);
      
          j=rand() % 100;
          cout<<j<<',';
          add(init(j) , BST );
          }    

   cout << endl;

   Mostrar(BST);
   
   system("pause");
}
