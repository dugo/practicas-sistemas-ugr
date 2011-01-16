#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>


using namespace std;

void iter_rango (const vector < pair<float,float> > S, vector<float> &rango);
void dyv_rango_1 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral);
void dyv_rango_2 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral);

void rellena(vector<pair<float, float> > &v, const unsigned int &n)
{
    v.resize(n);
    for (unsigned int i=0;i<n;i++)
    {
        v[i].first = (float) rand()/RAND_MAX;
        v[i].second = (float) rand()/RAND_MAX;
    }
}

int main(int argc, char **argv)
{
    vector<float> rango;
    vector<pair<float, float> > v;
    const unsigned int FASES=15;
    double tiempos[3][FASES];

    clock_t antes,despues;
    unsigned int i,j,n=1,veces;
    const unsigned int NUM_PEQ=100000, NUM_GRANDE=1;
    
    srand(time(NULL));

    for (j=0;j<12;j++)
	{
        veces = ((j>5)?NUM_GRANDE:NUM_PEQ);
        
        rellena(v, n);

        fprintf(stderr, "%d iter\n",n);
        antes = clock ( ) ;
        for ( i =0 ; i<veces; i++)
        {
            iter_rango (v, rango);
        }
        despues = clock ( ) ;
        tiempos[0][j] = ( ( double ) ( despues-antes) / (double)(CLOCKS_PER_SEC * veces) );

        
		fprintf(stderr, "%d dyv1\n",n);		
		antes = clock ( ) ;
		for ( i =0 ; i<veces; i++)
		{
			dyv_rango_1 (v, rango, 1);
        }
        despues = clock ( ) ;
		tiempos[1][j] = ( ( double ) ( despues-antes) / (double)(CLOCKS_PER_SEC * veces) );
		
        fprintf(stderr, "%d dyv2\n",n);
		antes = clock ( ) ;
		for ( i =0 ; i<veces; i++)
		{
			dyv_rango_2 (v, rango, 1);
        }
        despues = clock ( ) ;
		tiempos[2][j] = ( ( double ) ( despues-antes) / (double)(CLOCKS_PER_SEC * veces) );

		n = n * ((j%2)?2:5);
	}
	
	for(i=0;i<3;i++)
	{
	    n=1;
	    for(j=0;j<FASES;j++)
	        cout<<n<<' '<<tiempos[i][j]<<endl;
        
        n = n * ((j%2)?2:5);
    }
}
