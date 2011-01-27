#include <vector>
#include <queue>

/**
@brief Macro para compilar el programa para un determinado número de focos.

Por defecto 10.
*/
#define NFOCOS 10

/**
@brief Macro para compilar el programa en modo "verbose".

Compila al programa para que devuelva el número de podas, expansiones realizadas
y el tamaño mayor alcanzado en la lista de nodos vivos.
Por defecto desactivada.
*/
#define __VERBOSE__


#ifdef __VERBOSE__
#include <iostream>
#endif

/**
@brief Estructura necesaria para almacenar un nodo en la lista de nodos vivos.
*/
struct Nodo
{
	Nodo() { };
	Nodo(std::vector<int> x, std::vector<int> f, double c, double m, int q) { X=x;F=f;CLocal=c;M=m;k=q; }
	std::vector<int> X,F;
	double CLocal, M;
	int k;
};

/**
@brief Clase para que priority_queue pueda ordenar los nodos.
*/
class ComparadorNodo
{
	public:
		bool operator()(Nodo a, Nodo b)
		{
			return a.M < b.M;
		}
};

inline bool Factible(const std::vector<int> &X,const int &flibres, const int &k);
inline double CotaSuperior(const std::vector<int> &T, const std::vector<int> &X, std::vector<int> F);
inline double CotaInferior(const std::vector<int> &T, std::vector<int> F, const int &k);
void bombillas_BB_qs (std::vector<int> &S, std::vector<int> &P,const unsigned int &ini, const unsigned int &fin);
void bombillas_BB_qs (std::vector<int> &S, const unsigned int &ini, const unsigned int &fin);
inline int Min(const std::vector<int> &F);


#ifdef __VERBOSE__
void bombillas_BB (const std::vector<int> T,std::vector<int> &A, int &tiempo, register unsigned int &NEXP, register unsigned int &NPODAS, register unsigned int &MAXNV)
#else
void bombillas_BB (const std::vector<int> T, std::vector<int> &A, int &tiempo)
#endif
{
	Nodo actual; // Nodo que estamos procesando actualmente
	register int i;
	int miny;
	double CGlobal, CIy, CSy; // Cota global, cota inferior y cota superior para un nodo y
	unsigned int n = T.size();
	tiempo = 0;
	
	// Cola con prioridad para la lista de nodos vivmos
	std::priority_queue<Nodo, std::vector<Nodo>, ComparadorNodo> vivos;
		

	std::vector<int> TOrd(T), TPos(T.size()), X(n,0),F(NFOCOS,0);

	for (i=0;i<T.size();i++)
		TPos[i] = i;

	// Ordeno el vector de bombillas que será necesario para la función CotaInferior
	bombillas_BB_qs(TOrd, TPos, 0, n-1);
	
	// Convierto el orden ascendente en descendente (invierto)
	for (i=0;i<n/2;i++)
	{
		std::swap(TOrd[i],TOrd[n-i-1]);
		std::swap(TPos[i],TPos[n-i-1]);
	}
	
	CGlobal = CotaInferior(TOrd,F,-1);
	
	// Relleno el nodo raiz y lo meto en la cola
	actual.F = F;
	actual.X = X;
	actual.k = -1;
	actual.CLocal = CotaSuperior(TOrd,X,F);
	actual.M = (actual.CLocal+CGlobal)/2.0;
	vivos.push(actual);
	
	// Bucle principal BB
	while(!vivos.empty())
	{
		#ifdef __VERBOSE__
		MAXNV = (vivos.size()>MAXNV)?vivos.size():MAXNV;
		#endif
		
		// Cojo el nodo mejor estimado
		actual = vivos.top();
		vivos.pop();
	
		// Si su cota es mejor o igual que la cota global actual
		// lo proceso, en otro caso lo descarto
		if (actual.CLocal >= CGlobal)
		{
			// Genero los hijos, uno por foco
			for (i=1;i<=NFOCOS;i++)
			{
				// Cojo los valores que me interesan
				X = actual.X;
				X[actual.k+1] = i;
				F = actual.F;
				F[i-1] += TOrd[actual.k+1];

				// Cuento los focos libres para la funcion Factible()
				// igual que en BK
				int flibres = 0;
				for (register int j=0;j<NFOCOS;j++)
					if (F[j] == 0) flibres++;

				if (Factible(X, flibres, actual.k +1))
				{
					#ifdef __VERBOSE__
					NEXP++;
					#endif
					if (actual.k+2 >= n) // Se trata de un nodo hoja
					{
						// Si la hoja alcanzada es mejor que la solucion actual
						if ((miny=Min(F))>tiempo)
						{
							// La almaceno
							tiempo = miny;
							A = X;
							// y actualizo la cota global
							CGlobal = CotaInferior(TOrd,F,actual.k +1);
						}
					}
					else
					// Si no es hoja compruebo su cota
					if ((CSy = CotaSuperior(TOrd,X,F)) >= CGlobal)
					{
						CIy = CotaInferior(TOrd,F,actual.k +1);
						// Lo meto en la lista de nodos vivos con sus valores
						vivos.push(Nodo(X, F, CSy, (CSy+CGlobal)/2.0, actual.k +1));
						// Si es mas prometedor que la cota global actual
						if (CIy > CGlobal)
						{
							// Lo tomo como la solucion actual
							CGlobal = CIy;
							tiempo = Min(F);
							A = X;
						}
					}
				}
				#ifdef __VERBOSE__
				else
				NPODAS++;
				#endif
			}
		}
		#ifdef __VERBOSE__
		else
		NPODAS++;
		#endif
	}
	
	// Reordenados la solucion
	X = A;
	for (i=0;i<n;i++)
	{
		A[TPos[i]] = X[i];
	}
}

/**
@brief Obtiene la cota superior según lo definido en el enunciado de la práctica
@param T Vector con los tiempos de las bombillas.
@param X Vector solución parcial.
@param F Vector con las duraciones de los focos acumulados para la solución parcial X.
@return La cota superior.
*/
inline double CotaSuperior(const std::vector<int> &T, const std::vector<int> &X, std::vector<int> F)
{
	register unsigned int i = 0, resto = 0;
	double obj;
	int aux;
	
	// Calculo el tiempo de los focos que me quedan
	for (;i<T.size();i++)
		if (X[i]==0) resto += T[i];
	
	// Ordenamos F de forma ascendente
	bombillas_BB_qs(F,0,NFOCOS-1);
	
	// Este es el algoritmo descrito en el enunciado de la práctica
	obj = F[0];
	for (i=0;i<NFOCOS-1 && resto>0;i++)
	{
		aux = (i+1) * (F[i+1]-obj);
		aux = (resto<aux)?resto:aux;
		resto -= aux;
		obj+= static_cast<double>(aux)/static_cast<double>(i+1);
	}
	
	if (resto>0) obj += static_cast<double>(resto)/10.0;
	
	return obj;
}

/**
@brief Obtiene la cota superior según lo definido en el enunciado de la práctica
@param T Vector con los tiempos de las bombillas.
@param k Bombilla que se está procesando actualmente.
@return La cota inferior.
*/
inline double CotaInferior(const std::vector<int> &T, std::vector<int> F, const int &k)
{
	register unsigned int i = 0;
	
	// Ordenamos F de forma ascendente
	bombillas_BB_qs(F,0,NFOCOS-1);

	// Comienza el algoritmo Greedy partiendo desde k
	for (i=k+1;i<T.size();i++)
	{
		F[0] += T[i];
		
		// Volvemos a ordenar
		bombillas_BB_qs(F,0,NFOCOS-1);
	}

	return static_cast<double>(F[0]);
}

/**
@brief Obtiene el mínimo para un vector.
@param F Vector para obtener el mínimo
@return El mínimo del vector.
*/
inline int Min(const std::vector<int> &F)
{
	register int i = 0, minimo = F[0];

	for(;i<F.size();i++)
		if(F[i]<minimo) minimo = F[i];                                         

	return minimo;
}


/**
@brief Ordena mediante el algoritmo quicksort en forma creciente
@param S Vector a ordenar. ES MODIFICADO
@param P Vector de posiciones (explicación abajo). ES MODIFICADO
@param ini Marca el comienzo del subconjunto a ordenar (inclusive). NO ES MODIFICADO
@param fin Marca el final del subconjunto a ordenar (inclusive). NO ES MODIFICADO

Esta función ordena de forma creciente el vector S y también modifica el vector P
según el mismo criterio, de esta forma se puede reconstruir el vector original S.

NOTA: Esta función es la función utilizada por mi para ordenar en la práctica 1 modificada
según las necesidades de esta.
*/
void bombillas_BB_qs (std::vector<int> &S, std::vector<int> &P, const unsigned int &ini, const unsigned int &fin)
{
    /*** Casos particulares ***/
    
    // Conjunto con un único elemento o vacío
    if (fin-ini+1<=1) return;

    // Conjunto con dos elementos
    if (fin-ini+1==2)
    {
        if (S[ini]>S[fin])
        {
            std::swap(S[ini],S[fin]);
            std::swap(P[ini],P[fin]);
        }
        return;
    }

    unsigned int der=fin,izq=ini+1,posmedia,i;
    float pivote=S[ini]; 

    // Realizo el intercambio de elementos
    while (izq < der)
    {
        while (izq<der && S[izq] <= pivote) izq++;
        while (izq<der && S[der]  > pivote) der--;

        std::swap(S[izq],S[der]);
        std::swap(P[izq],P[der]);
    }

    // Elijo la posicion media
    posmedia = (pivote>S[izq])?izq:izq-1;

    if (ini!=posmedia)
    {
        std::swap(S[ini], S[posmedia]);
        std::swap(P[ini], P[posmedia]);
    }
    
    bombillas_BB_qs(S, P, ini, posmedia-1);
    bombillas_BB_qs(S, P, posmedia+1, fin); 
}

/**
@brief Ordena mediante el algoritmo quicksort en forma creciente
@param S Vector a ordenar. ES MODIFICADO
@param ini Marca el comienzo del subconjunto a ordenar (inclusive). NO ES MODIFICADO
@param fin Marca el final del subconjunto a ordenar (inclusive). NO ES MODIFICADO

NOTA: Esta función es la función utilizada por mi para ordenar en la práctica 1 modificada
según las necesidades de esta.
*/
void bombillas_BB_qs (std::vector<int> &S, const unsigned int &ini, const unsigned int &fin)
{
    /*** Casos particulares ***/
    
    // Conjunto con un único elemento o vacío
    if (fin-ini+1<=1) return;

    // Conjunto con dos elementos
    if (fin-ini+1==2)
    {
        if (S[ini]>S[fin])
        {
            std::swap(S[ini],S[fin]);
        }
        return;
    }

    unsigned int der=fin,izq=ini+1,posmedia,i;
    float pivote=S[ini]; 

    // Realizo el intercambio de elementos
    while (izq < der)
    {
        while (izq<der && S[izq] <= pivote) izq++;
        while (izq<der && S[der]  > pivote) der--;

        std::swap(S[izq],S[der]);
    }

    // Elijo la posicion media
    posmedia = (pivote>S[izq])?izq:izq-1;

    if (ini!=posmedia)
    {
        std::swap(S[ini], S[posmedia]);
    }
    
    bombillas_BB_qs(S, ini, posmedia-1);
    bombillas_BB_qs(S, posmedia+1, fin); 
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
