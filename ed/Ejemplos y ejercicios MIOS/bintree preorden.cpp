#include <iostream>
#include "bintree.h"

using namespace std;

void insertar(bintree<char> &arb,const bintree<char>::node &n,char *c,int &i);

int main(){
    
    char c[12]="+*aj-/dc*ba";
  
   
    bintree<char> arb(c[0]);
    
    int i=1;
    insertar(arb,arb.root(),c,i);
    

    cout << "Cadena original en Preorden: \t"<<c<<endl<<endl;

    cout << "Lectura en Postorden: \t";    
    for(bintree<char>::postorder_iterator it=arb.begin_postorder();it!=arb.end_postorder();++it) cout<<*it;
    cout<<endl<<endl;
    cout << "Lectura en Preorden: \t";    
    for(bintree<char>::preorder_iterator it1=arb.begin_preorder();it1!=arb.end_preorder();++it1) cout<<*it1;    
    cout<<endl<<endl;
                                          
    
    
    system("pause");
    
    return 0;
    }

//Va llenando la izquierda y cuando la tiene llena pasa a la derecha.
void insertar(bintree<char> &arb,const bintree<char>::node &n,char *c,int &i) {
     
     if (c[i]=='\0') return;
     
     
     arb.insert_left(n,c[i]);
     i++;
     
     
     insertar(arb,n.left(),c,i);
     insertar(arb,n.right(),c,i);
     }

