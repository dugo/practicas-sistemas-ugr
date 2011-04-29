#include <iostream>
#include <time.h>
#include "hash_table.h"

using namespace std;


int main() {
    
    srand( (unsigned)time( NULL ) ); // init Rand() function   
    

    int len; 
    int datos;
    string str;

    datos=(rand() % 100000) + 900000;

    hash_table<int,string> tabla(datos);
    
    pair<int,string> p;

    cout << "Probando con "<<datos<<" datos aleatorios."<<endl<<endl;


    for (int i=0;i<datos;i++) {
    
     len=(rand() % 20) + 10;

     str="";
     for (int j=0;j<len;j++)
            str+= static_cast<char>((rand() % 25) + 65);
     
     p.first=i;
     p.second=str;
     
     tabla.insert(p);
     }

     cout<<"Listo."<<endl;

     int busca;
     string dato;     
     do {
     cout << "Buscar:\t";
     cin>>busca;
     } while(busca<0 || busca >= datos);
     
     hash_table<int,string>::const_iterator it;
     
     int tiempo=(unsigned)time( NULL );
     it=tabla.find(busca);
     tiempo-=(unsigned)time( NULL );
     if (it!=tabla.end() ) {
        cout<<"\nEncontrado en "<<tiempo<<" segundos: \t"<<(*it).second;
        }
     else cout<<"No encontrado.";
     
     cout<<endl<<endl;system("pause");
     
}
