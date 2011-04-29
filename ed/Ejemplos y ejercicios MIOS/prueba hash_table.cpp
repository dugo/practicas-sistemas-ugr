#include <iostream>
#include "hash_table.h"
//#include <map>

using namespace std;

int main() {
    
    hash_table<int,char> tabla(12);
    
    pair<int,char> p;
    
    char c[13]="ABCDEFGHIJKL";
    int e[12]={1,2,3,4,4,5,6,7,7,8,9,10};
    
    for (int i=0;i<12;i++) {
        p.first = e[i];
        p.second = c[i];
        tabla.insert(p);
        }

    hash_table<int,char>::const_iterator it=tabla.begin();
    
    while (it!=tabla.end()){
    
    cout << (*it).first<<','<<(*it).second<<endl;
    
    ++it;      
    }

    cout<<endl<<endl;
    
    tabla.erase(7);
    tabla.erase(7);
    //tabla.erase(7);

    it=tabla.begin();
    
    while (it!=tabla.end()){
    
    cout << (*it).first<<','<<(*it).second<<endl;
    
    ++it;      
    }
    
    //cout << (*it).first<<','<<(*it).second<<endl;
    
    cout<<endl;
    
    system("pause");

    return 0;    
}
