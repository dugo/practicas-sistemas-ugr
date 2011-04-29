#include <iostream>
#include "pot.h"

using namespace std;

int main() {
    
    int e[8]={2,4,5,8,5,10,6,10};
    
    POT<int> arbol;
    
    for (int i=0;i<8;i++)
        arbol.insert(e[i]);

    while(!arbol.empty()) {
                          cout<<arbol.top()<<',';
                          arbol.pop();
                          }

    cout<<endl;
    system("pause");

    }
