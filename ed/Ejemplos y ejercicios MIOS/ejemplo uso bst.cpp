#include <iostream>
#include <time.h>
//#include <pair.h>
#include "bst.h"

using namespace std;

int main() {
    

    const int num=30;


    srand( (unsigned)time( NULL ) ); // init Rand() function   
   
    cout << "Numeros aleatorios:"<<endl<<endl;

    //BST<int,char> arb;
    pair<int,char> p;
   
    for (int i=0;i<num;i++) {  //Doy un valor aleatorio a cada uno de los nodos

        if (i!=0)         cout << ',';
        
        p.first = (rand() % 1000) + 1;
        p.second = static_cast<char>((rand() % 93) + 33);
        
                cout << p.first<<','<<p.second;
        }


    cout<<endl<<endl;
    system("pause");      
}
