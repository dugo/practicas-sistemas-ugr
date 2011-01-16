#include <iostream>
#include <vector>
#include <cstdlib>

#define VECES 20

using namespace std;

void bombillas_BK (const std::vector<int> T,std::vector<int> &A, int &tiempo, register unsigned int &NEXP, register unsigned int &NPODAS);

inline void init(vector<int> &V)
{
	for (int i=0;i<V.size();i++)
		V[i] = 1+static_cast<int>( (100.0*rand()/(RAND_MAX+1.0)));
}

int main()
{

	srand(time(NULL));
	vector<int> A;
	vector<vector<int> > T(VECES);
	int tiempo=0;
	register int j;
	clock_t antes, despues;
	
	register unsigned int NEXP=0,NPODAS=0; // Contadores de nodos expandidos y nodos podados resp
	int TEXP=0,TPODAS=0;

	for (int i=11;i<20;i++)
	{
		for (j=0;j<VECES;j++)
		{
			T[j].resize(i);
			init(T[j]);
		}
		A.resize(i);
		
		cout << "n=" << i <<": ";
		
		antes = clock();
		for ( j =0 ; j<VECES; j++)
		{
			bombillas_BK(T[j],A,tiempo,NEXP,NPODAS);
			TEXP+=NEXP; TPODAS+=NPODAS;
		}
		despues = clock();

		cout << " [( ";
		for (j=0;j<i;j++)
			cout<<T[VECES-1][j]<<'-'<<A[j]<<' ';
		cout << "),tiempo=" <<tiempo<<"] "<<TEXP/VECES<<' '<<TPODAS/VECES<<' '<<( ( double ) ( despues-antes) / (double)(CLOCKS_PER_SEC*VECES) )<<endl;
		
	}
}


