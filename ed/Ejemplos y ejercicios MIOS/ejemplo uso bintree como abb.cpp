#include <iostream>
#include <time.h>
#include <map>
#include "bintree.h"

using namespace std;

void insertar(bintree<pair<int,char> > &arb,const bintree<pair<int,char> >::node &n,const pair<int,char> &p);

int main() {
    

    const int num=30;


    srand( (unsigned)time( NULL ) ); // init Rand() function   
   
    cout << "Numeros aleatorios:"<<endl;

    bintree<pair<int,char> > arb;
    pair<int,char> p;
   
    for (int i=0;i<num;i++) {  //Doy un valor aleatorio a cada uno de los nodos

        cout << endl;

        p.first = (rand() % 1000) + 1;
        p.second = static_cast<char>((rand() % 93) + 33);
        
                cout << p.first<<','<<p.second;
                
                
        if (i==0)
           arb=bintree<pair<int,char> >(p);
        else
            insertar(arb,arb.root(),p);

        }

    cout << "\n\nLectura en Inorden: \n\n";    
    for(bintree<pair<int,char> >::inorder_iterator it=arb.begin_inorder();it!=arb.end_inorder();++it) cout << (*it).first<<','<<(*it).second<<endl;

    cout<<endl<<endl;
    system("pause");      
}

void insertar(bintree<pair<int,char> > &arb,const bintree<pair<int,char> >::node &n,const pair<int,char> &p) {
     
     
     if (p.first>=(*n).first) {
                             if (n.right().null())
                                arb.insert_right(n,p);
                             else
                                 insertar(arb,n.right(),p);
                             }
     else {
                             if (n.left().null())
                                arb.insert_left(n,p);
                             else
                                 insertar(arb,n.left(),p);
                             }
     
     }
