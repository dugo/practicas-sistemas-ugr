#include <vector>

/**
@brief Macro para compilar el programa para un determinado número de focos.

Por defecto 10.
*/
#define NFOCOS 10

/**
@brief Macro para compilar el programa en modo "verbose".

Compila al programa para que devuelva el número de podas y expansiones realizadas.
Por defecto desactivada.
*/
#define __VERBOSE__

#ifdef __VERBOSE__
#include <iostream>
#endif


#ifdef __VERBOSE__
void bombillas_BK (const std::vector<int> T,std::vector<int> &A, int &tiempo, register unsigned int &NEXP, register unsigned int &NPODAS);
void BK(const std::vector<int> &T,std::vector<int> X,std::vector<int> &A,std::vector<int> &F,int &tiempo, int k, register unsigned int &NEXP, register unsigned int &NPODAS);
#else
void bombillas_BK (const std::vector<int> T,std::vector<int> &A, int &tiempo);
void BK(const std::vector<int> &T,std::vector<int> X,std::vector<int> &A,std::vector<int> &F,int &tiempo, int k);
#endif

inline int Min(const std::vector<int> &V);
inline bool Factible(const std::vector<int> &X,const int &flibres, const int &k);

#ifdef __VERBOSE__
void bombillas_BK (const std::vector<int> T,std::vector<int> &A, int &tiempo, register unsigned int &NEXP, register unsigned int &NPODAS)
#else
void bombillas_BK (const std::vector<int> T, std::vector<int> &A, int &tiempo)
#endif
{
	int k = 0;
	tiempo = 0; // Objetivo a maximizar

	std::vector<int> X(T.size(),0), F(NFOCOS,0);


	#ifdef __VERBOSE__
	BK(T,X,A,F,tiempo,k,NEXP,NPODAS);
	#else
	BK(T,X,A,F,tiempo,k);
	#endif
}

/**
@brief Función recursiva de la implementación backtracking.
@param T Vector con los tiempos de los focos.
@param X Vector de la solución parcial.
@param A Vector con la solución final (óptima). ES MODIFICADO
@param F Vector con los tiempos de los focos acumulados. ES MODIFICADO
@param tiempo Tiempo mínimo del vector de soluciones. ES MODIFICADO
@param k Fase (en profundidad) por la que va el algoritmo, inicialmente 0.
@param NEXP Número de nodos total que se expanden en la ejecución del algoritmo. ES MODIFICADO
@param NPODAS Número de podas total que se realizan en la ejecución del algoritmo. ES MODIFICADO

Los dos últimos parámetros (NEXP y NPODAS) sólo serán necesarios cuando se active la macro __VERBOSE__.
*/
#ifdef __VERBOSE__
void BK(const std::vector<int> &T,std::vector<int> X,std::vector<int> &A,std::vector<int> &F,int &tiempo,int k, register unsigned int &NEXP, register unsigned int &NPODAS)
#else
void BK(const std::vector<int> &T,std::vector<int> X,std::vector<int> &A,std::vector<int> &F,int &tiempo,int k)
#endif
{	
	if(k>=X.size())
	{
		int min = Min(F);
		// Si es esta solucion mejor que la que tengo ya
		if(min>tiempo)
		{
			// La almaceno, funcion Actualizar()
			tiempo = min;
			A = X;
		}
	}
	else
	{
		for(register int i=1;i<=NFOCOS;i++)
		{
			// Cuento los focos libres para la funcion Factible()
			int flibres = 0;
			for (register int j=0;j<NFOCOS;j++)
				if (F[j] == 0) flibres++;
			
			if (F[i-1] == 0) flibres--;
			
			X[k] = i;
			if(Factible(X,flibres,k))
			{
				#ifdef __VERBOSE__
				NEXP++;
				#endif
				
				// Sumo a F el tiempo de la bombilla k
				F[i-1] += T[k];

				// Recursividad!
				#ifdef __VERBOSE__
				BK(T,X,A,F,tiempo,k+1, NEXP, NPODAS);
				#else
				BK(T,X,A,F,tiempo,k+1);
				#endif

				// Resto a F el tiempo de la bombilla k
				F[i-1] -= T[k];                                                      
			}
			#ifdef __VERBOSE__
			else NPODAS++;
			#endif
		}
	}
}

/**
@brief Obtiene el mínimo de un vector.
@param V Vector.
@return Mínimo del vector.
*/
inline int Min(const std::vector<int> &V)
{
	int minimo = V[0];

	for(unsigned int i=1;i<V.size();i++)
		if(V[i]<minimo) minimo = V[i];                                         

	return minimo;
}

/**
@brief Comprueba si una solución parcial cumple las restricciones implícitas.
@param X Vector de la solución parcial.
@param flibres Focos libres en dicha solución.
@param k Fase (profundidad en el árbol de estados) por la que iba la solución.
*/ 
inline bool Factible(const std::vector<int> &X,const int &flibres, const int &k)
{
	register unsigned int blibres = 0, i = 0;

	// Cuento las bombillas libres
	for (;i<X.size();i++)
		if (X[i]==0) blibres++;
		
	// Restriccion (1); deben quedar igual o mas bombillas sin asignar que focos libres
	if (blibres < flibres);
	// Restriccion (2); no se podra colocar una bombilla en un foco > foco anterior +1
	// esto evita soluciones repetidas
	else if (k>0 && X[k]>X[k-1]+1);
	else return true;

	return false;
}
