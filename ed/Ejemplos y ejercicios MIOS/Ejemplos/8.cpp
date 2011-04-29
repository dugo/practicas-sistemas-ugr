#include <iostream>
#include <math.h>

using namespace std;

int main(){

    int c[7]={1,2,4,5,3,6,7};
    int salida[7];
    int nodos=7;
    int niveles;
    
    niveles=log10(nodos+1)/log10(2);   
    
    for (int i=niveles;i>=0;i--) {
        
        for (int g=0;g<pow(2,i);g++) {
            cout<<pow(2,i)<<endl;
            
            }
        
        }
    
    
    cout<<endl<<endl;system("pause");
    
}
