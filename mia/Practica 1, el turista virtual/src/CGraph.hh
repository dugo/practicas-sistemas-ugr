#ifndef __VT_CGRAPH_H__
#define __VT_CGRAPH_H__

#include <map>
#include <vector>

/**
@brief Plantilla para representacion de grafos
*/
template <class T>
class CGraph
{

private:
	int NumNodes;
	// Asociacion del nodo a su indice en la matriz de adyaciencia
	std::map<T,int> mymap;
	// Matriz de adyaciencia
	bool *matrix;
	// Numero de nodo por el que voy añadiendo a la matriz de adyaciencia
	int k;
	
public:
	/**
	@brief Constructor por defecto
	@param dim Dimension del grafo (numero de nodos)
	
	Inicializa la clase con un determinado numero de nodos para despues añadirle
	las aristas.
	Una vez inicializada la clase podra ser redimensionada.
	*/
	CGraph(const int &dim);
	/**
	@brief Destructor
	*/
	~CGraph();
	/**
	@brief Constructor de copia
	*/
	CGraph(const CGraph &src);
	/**
	@brief Operador de asignacion
	*/
	CGraph& operator=(const CGraph &src);
	/**
	@brief Funcion para saber si dos nodos estan conectados
	@param node1 Primer nodo
	@param node2 Segundo nodo
	@retval Verdadero si estan conectados, falso en caso contrario.
	*/
	bool isNeighbourg(const T &node1, const T &node2);
	/**
	@brief Funcion para obtener el numero de nodos
	@return Numero de nodos
	*/
	int getNumNodes() const;
	/**
	@brief Obtiene un vector los adyancentes a un nodo determinado
	@param node Nodo
	@return Vector con los nodos adyacentes
	*/
 	std::vector<T> getNeighbourgs(const T &node);
 	/**
 	@brief Funcion para añadir una arista entre dos nodos
 	@param node1 Primer nodo
 	@param node2 Segundo nodo
 	@retval Verdadero si se ha añadido la arista correctamente, falso en caso
 	contrario.
 	*/
 	bool addNeighbourgs(const T &node1, const T &node2);
};

#endif
