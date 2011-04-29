#include <iostream>
#include "bintree.h"

using namespace std;

void insertar(bintree<char> &arb,const bintree<char>::node &n,char *c,int &i);

int main(){
    
    char c[12]="ab*cd/-ja*+";
  
   
    bintree<char> arb(c[11]);
    
    int i=10;
    insertar(arb,arb.root(),c,i);
    

    cout << "Cadena original en Postorden: \t"<<c<<endl<<endl;

    cout << "Lectura en Postorden: \t";    
    for(bintree<char>::postorder_iterator it=arb.begin_postorder();it!=arb.end_postorder();++it) cout<<*it;
    cout<<endl<<endl;
    cout << "Lectura en Preorden: \t";    
    for(bintree<char>::preorder_iterator it1=arb.begin_preorder();it1!=arb.end_preorder();++it1) cout<<*it1;    
    cout<<endl<<endl;
                                          
    
    
    system("pause");
    
    return 0;
    }

//Va llenando la derecha y cuando la tiene llena pasa a la izquierda.
void insertar(bintree<char> &arb,const bintree<char>::node &n,char *c,int &i) {
     
     if (i==-1) return;
     
     
     arb.insert_right(n,c[i]);
     i--;
     
     
     insertar(arb,n.right(),c,i);
     insertar(arb,n.left(),c,i);
     }

