#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>


typedef struct {
   int grosor;
} tornillo;
typedef struct {
   int anchura;
} tuerca;

using namespace std;

void dyv_tornillos_y_tuercas (const vector<tornillo> tor,
                              const vector<tuerca> tuer,
                              vector<tornillo> &tor_ordenado,
                              vector<tuerca> &tuer_ordenado);

void rellena(vector<tornillo> &t, vector<tuerca> &u, const unsigned int &n)
{
    int pos;
    
    t.resize(n);
    u.resize(n);
    
    for (unsigned int i=0;i<n;i++)
    {
        t[i].grosor = -1;
        u[i].anchura = -1;
    }
    
    for (unsigned int i=0;i<n;i++)
    {
        do
        {
            pos = static_cast<int> (static_cast<double>(n)*rand()/(RAND_MAX+1.0));
        }
        while (t[pos].grosor != -1);
        
        t[pos].grosor = i;
        
        do
        {
            pos = static_cast<int> (static_cast<double>(n)*rand()/(RAND_MAX+1.0));
        }
        while (u[pos].anchura != -1);
        
        u[pos].anchura = i;
    }
}

int main()
{
    vector<tornillo> t1,t2;
    vector<tuerca> u1,u2;
    

    clock_t antes,despues;
    unsigned int i,j,n=1,veces;
    const unsigned int NUM_PEQ=100000, NUM_GRANDE=10;
    double tiempo;
    
    srand(time(NULL));

    for (j=0;j<12;j++)
	{
        veces = ((j>5)?NUM_GRANDE:NUM_PEQ);
        
        rellena(t1,u1, n);

        antes = clock ( ) ;
        for ( i =0 ; i<veces; i++)
        {
            dyv_tornillos_y_tuercas(t1,u1,t2,u2);
        }
        despues = clock ( ) ;
        tiempo = ( ( double ) ( despues-antes) / (double)(CLOCKS_PER_SEC * veces) );
        
        cout<<n<<' '<<tiempo<<endl;

		n = n * ((j%2)?2:5);
	}
    
    dyv_tornillos_y_tuercas(t1,u1,t2,u2);
}

