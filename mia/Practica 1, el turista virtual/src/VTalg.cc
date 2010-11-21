#include <stack>
#include <queue>
#include <set>
#include <cmath>
#include <map>

#include "Stretch.hh"
#include "Crossroads.hh"
#include "CGraph.hh"
#include "VTalg.hh"

// Esto me permite saltarme la encapsulacion y acceder directamente al contenedor
// de una cola con prioridad
template <class T, class S, class C>
S& Container(std::priority_queue<T, S, C>& q)
{
	struct HackedQueue : private std::priority_queue<T, S, C>
	{
		static S& Container(std::priority_queue<T, S, C>& q)
		{
			return q.*&HackedQueue::c;
		}
	};
	return HackedQueue::Container(q);
}

/**
@brief Macro para calcular la distancia de un cruce a unas coordenadas x e y

Uso interno.
*/
#define DISTANCE(c,x,y) sqrtf(powf(c.getX()-x,2.0)+powf(c.getY()-y,2.0))

/**
@brief Clase para comparar la cola con prioridad en el algoritmo BMP

Uso interno.
*/
class BMPComparador
{
	public:
		BMPComparador(const float &x=0.0, const float &y=0.0, const float &w=0.5) { myx = x; myy = y; }
		bool operator()(const Crossroads &n1, const Crossroads &n2)
		{
			return (DISTANCE(n1,myx,myy)>DISTANCE(n2,myx,myy));
		}
	
	private:
		float myx,myy;
};

/**
@brief Registro con la informacion necesaria para procesar un nodo en el algoritmo BPM

Uso interno.
*/
struct BPMNodo
{
	BPMNodo() { }
	BPMNodo(const Crossroads &n,const Crossroads &p, const float &g_, const float &h_) { nodo=n; padre=p; g=g_; h=h_; }
	Crossroads nodo,padre;
	float g,h;
};

/**
@brief Clase para comparar en la cola con prioridad utilizada en la implementacion del algoritmo BPM

Uso interno.
*/
class BPMComparador
{
	public:
		BPMComparador(const float &w=0.5) { myw=w;}
		bool operator()(const BPMNodo &n1, const BPMNodo &n2)
		{
			return ( (myw*n1.g+(1.0-myw)*n1.h)>(myw*n2.g+(1.0-myw)*n2.h) );
		}
	
	private:
		float myw;
};

/**
@brief Funcion para reconstruir el camino seguido hasta dos nodos.
@param parents Map de cruces, donde el segundo representa el padre del primero
@param ini Cruce inicial
@param fin Nodo final

Uso interno.
*/
void rebuildPath(std::map<Crossroads, Crossroads> &parents, const Crossroads &ini, Crossroads fin, std::vector<Crossroads> &way);

unsigned int BPP(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino)
{
	camino.clear();
	
	if (ini==fin)
		return 0;
	
	unsigned int nodos = 0;
	std::vector<Crossroads> sucesores;
	// Utilizo un contenedor LIFO
	std::stack<Crossroads> abiertos;
	Crossroads actual;
	// La lista CERRADOS, la utilizare tambien para almacenar el padre del nodo actual
	// para mas tarde reconstruir el camino
	std::map<Crossroads,Crossroads> cerrados;
	bool terminado = false, contado;
	register unsigned int i;

	// Inserto el nodo inicial
	abiertos.push(ini);
	cerrados[ini] = Crossroads();

	do
	{
		contado=false;
		actual = abiertos.top();
		abiertos.pop();
		
		if (actual==fin)
			terminado = true;
		else
		{
			// Obtengo los sucesores
			sucesores = mimapa.getNeighbourgs(actual);
			for (i=0;i<sucesores.size();i++)
			{
				// Si no estan ya en CERRADOS los inserto en ABIERTOS
				if (cerrados.find(sucesores[i])==cerrados.end())
				{
					if (!contado)
					{
						contado = true;
						nodos++;
					}
					abiertos.push(sucesores[i]);
					cerrados[sucesores[i]] = actual;
				}
			}
		}
	}
	while (!abiertos.empty() && !terminado);
	
	if (terminado)
	{
		rebuildPath(cerrados, ini, fin, camino);
	}
	
	return nodos;
}

unsigned int BPA(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino)
{
	camino.clear();
	
	if (ini==fin)
		return 0;
	
	unsigned int nodos = 0;
	std::vector<Crossroads> sucesores;
	// Utilizo un contenedor FIFO
	std::queue<Crossroads> abiertos;
	Crossroads actual;
	// La lista CERRADOS, la utilizare tambien para almacenar el padre del nodo actual
	// para mas tarde reconstruir el camino
	std::map<Crossroads,Crossroads> cerrados;
	bool terminado = false, contado;
	register unsigned int i;

	// Inserto el nodo inicial
	abiertos.push(ini);
	cerrados[ini] = Crossroads();

	do
	{
		contado = false;
		actual = abiertos.front();
		abiertos.pop();
		
		if (actual==fin)
			terminado = true;
		else
		{
			// Obtengo los sucesores
			sucesores = mimapa.getNeighbourgs(actual);
			for (i=0;i<sucesores.size();i++)
			{
				// Si no estan ya en CERRADOS los inserto en ABIERTOS
				if (cerrados.find(sucesores[i])==cerrados.end())
				{
					if (!contado)
					{
						contado = true;
						nodos++;
					}
					abiertos.push(sucesores[i]);
					cerrados[sucesores[i]] = actual;
				}
			}
		}
	}
	while (!abiertos.empty() && !terminado);
	
	if (terminado)
	{
		rebuildPath(cerrados, ini, fin, camino);
	}
	
	return nodos;
}

unsigned int BMP(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino)
{
	camino.clear();
	
	if (ini==fin)
		return 0;
	
	unsigned int nodos = 0;
	std::vector<Crossroads> sucesores;
	// Utilizo una cola con prioridad especial que realiza las comparaciones segun
	// la distancia del nodo a unas coordenadas x e y (normalmente del nodo final)
	typedef std::priority_queue<Crossroads, std::vector<Crossroads>, BMPComparador> mypq_type;
	mypq_type abiertos((BMPComparador(fin.getX(), fin.getY())));
	Crossroads actual;
	// La lista CERRADOS, la utilizare tambien para almacenar el padre del nodo actual
	// para mas tarde reconstruir el camino
	std::map<Crossroads,Crossroads> cerrados;
	bool terminado = false,contado;
	register unsigned int i;

	// Inserto el nodo inicial
	abiertos.push(ini);
	cerrados[ini] = Crossroads();

	do
	{
		contado=false;
		actual = abiertos.top();
		abiertos.pop();
		
		if (actual==fin)
			terminado = true;
		else
		{
			// Obtengo los sucesores
			sucesores = mimapa.getNeighbourgs(actual);
			for (i=0;i<sucesores.size();i++)
			{
				// Si no estan ya en CERRADOS los inserto en ABIERTOS
				if (cerrados.find(sucesores[i])==cerrados.end())
				{
					if (!contado)
					{
						contado = true;
						nodos++;
					}
					abiertos.push(sucesores[i]);
					cerrados[sucesores[i]] = actual;
				}
			}
		}
	}
	while (!abiertos.empty() && !terminado);
	
	if (terminado)
	{
		rebuildPath(cerrados, ini, fin, camino);
	}
	
	return nodos;
}

unsigned int BPM(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino, const float &W)
{
	camino.clear();
	
	if (ini==fin)
		return 0;
	
	unsigned int nodos = 0;
	std::vector<Crossroads> sucesores;
	// Utilizo una cola con prioridad como la lista ABIERTOS
	// La defino para que tenga en cuenta el factor W
	typedef std::priority_queue<BPMNodo, std::vector<BPMNodo>, BPMComparador> mypq;
	mypq abiertos((BPMComparador(W)));
	// Utilizo este set para buscar en ABIERTOS (busquedas logaritmicas)
	std::set<Crossroads> abiertos2;
	BPMNodo mejor, viejo;
	Crossroads actual;
	// La lista CERRADOS, la utilizare tambien para almacenar el padre del nodo actual
	// para mas tarde reconstruir el camino
	std::map<Crossroads,Crossroads> cerrados;
	bool terminado = false,contado;
	register unsigned int i;
	// Valores x e y del nodo final
	const float x = fin.getX(), y = fin.getY();
	float g;
	// De esta forma accedo al contenedor de ABIERTOS para recorrerlo secuencialmente
	std::vector<BPMNodo>& contenedorAB = Container(abiertos);
	std::vector<BPMNodo>::iterator it;

	// Inserto en ABIERTOS el nodo inicial
	abiertos.push(BPMNodo(ini,Crossroads(),0.0,DISTANCE(ini,x,y)));
	abiertos2.insert(ini);

	do
	{
		contado = false;
		// Obtengo el mejor nodo y lo inserto en CERRADOS
		mejor = abiertos.top();
		abiertos.pop();
		abiertos2.erase(mejor.nodo);
		cerrados[mejor.nodo] = mejor.padre;
		
		if (mejor.nodo==fin)
			terminado = true;
		else
		{
			// Obtengo los sucesores del nodo actual
			sucesores = mimapa.getNeighbourgs(mejor.nodo);
			for (i=0;i<sucesores.size();i++)
			{	
				// Compruebo que el sucesor no esta ya en CERRADOS
				if (cerrados.find(sucesores[i])==cerrados.end())
				{
					// Inicializo viejo.nodo a null
					viejo.nodo = Crossroads();
					// Compruebo que el elemento no este ya en ABIERTOS
					if (abiertos2.find(sucesores[i])!=abiertos2.end())
					{
						// Lo busco en el contenedor
						for (it=contenedorAB.begin();(*it).nodo!=sucesores[i];it++);
						
						// Lo cojo y lo elimino
						viejo = (*it);
						contenedorAB.erase(it);
					}
					
					// Calculo g(SUCESOR)
					g = mejor.g+DISTANCE(sucesores[i],mejor.nodo.getX(),mejor.nodo.getY());
					// Compruebo si SUCESOR existia ya en ABIERTOS y si g(SUCESOR)<g(VIEJO)
					if (!viejo.nodo.null())
					{
						if (g < viejo.g)
						{
							viejo.padre = mejor.nodo;
							viejo.g = g;
						}
						
						// Lo vuelvo a insertar
						abiertos.push(viejo);
					}
					else
					{
						if (!contado)
						{
							contado = true;
							nodos++;
						}
						// Si NO esta ya en ABIERTOS lo inserto
						abiertos.push(BPMNodo(sucesores[i],mejor.nodo,g,DISTANCE(sucesores[i],x,y)));
						abiertos2.insert(sucesores[i]);
					}
				}
			}
		}
	}
	while (!abiertos.empty() && !terminado);

	if (terminado)
	{
		rebuildPath(cerrados, ini, fin, camino);
	}

	return nodos;
}

void rebuildPath(std::map<Crossroads, Crossroads> &parents, const Crossroads &ini, Crossroads fin, std::vector<Crossroads> &way)
{
	Crossroads tmp;
	way.push_back( fin );
	do
	{
		fin = parents[fin];
		way.push_back(fin);
	}
	while(fin!=ini);
	// Invierto el orden
	for (unsigned int i=0;i<way.size()/2;i++)
	{
		tmp=way[i];
		way[i]=way[way.size()-1-i];
		way[way.size()-1-i]=tmp;
	}
}

float lengthPath(std::vector<Crossroads> &way)
{
	float len = 0.0;
	
	if (!way.empty())
	{	
		float x = way[0].getX(), y = way[0].getY();
		for (unsigned int i=1;i<way.size();i++)
		{
			len += DISTANCE(way[i],x,y);
			x = way[i].getX();
			y = way[i].getY();
		}
	}
	
	return len;
}

#include "CGraph.cc"
