#include "CGraph.hh"

template <class T>
CGraph<T>::CGraph(const int &dim)
{
	matrix = new bool[dim*dim];
	NumNodes = dim;
	k=0;
}

template <class T>
CGraph<T>::~CGraph()
{
	if (NumNodes>0)
		delete [] matrix;
}


template <class T>
CGraph<T>::CGraph(const CGraph &src)
{
	NumNodes = src.dim;
	matrix = new T[NumNodes*NumNodes];
	
	for (int i=0;i<NumNodes;i++)
		matrix[i] = src.matrix[i];
	
	mymap = src.mymap;
	k=src.k;
}

template <class T>
CGraph<T>&
CGraph<T>::operator=(const CGraph &src)
{
	if (&src!=this)
	{
		if (matrix>0) delete [] matrix;
		
		NumNodes = src.dim;
		matrix = new T[NumNodes*NumNodes];
		
		for (int i=0;i<NumNodes;i++)
			matrix[i] = src.matrix[i];
		
		mymap = src.mymap;
		k=src.k;
	}
	return *this;
}

template <class T>
bool
CGraph<T>::isNeighbourg(const T &node1,const T &node2)
{
	return matrix[mymap[node1]*NumNodes+mymap[node2]];
}

template <class T>
int
CGraph<T>::getNumNodes() const
{
	return NumNodes;
}

template <class T>
std::vector<T>
CGraph<T>::getNeighbourgs(const T &node)
{
	std::vector<int> tmp;
	std::vector<T> ret;
	if (mymap.count(node)>0)
	{
		int i = mymap[node];
		for (int j=0;j<NumNodes;j++)
		{
			if (matrix[i*NumNodes+j])
				tmp.push_back(j);
		}

		bool enc;
		class std::map<T,int>::iterator it;
		for (unsigned int i=0;i<tmp.size();i++)
		{
			enc = false;
			for (it = mymap.begin();it!=mymap.end() && !enc;it++)
				if ((*it).second == tmp[i])
				{
					enc = true;
					ret.push_back((*it).first);
				}
		}
	}
	return ret;
}

template <class T>
bool
CGraph<T>::addNeighbourgs(const T &node1, const T &node2)
{
	if (node1==node2) return false;
	
	if (mymap.count(node1)==0)
	{
		if (k>=NumNodes) return false;
		else
		{
			mymap[node1] = k;
			k++;
		}
	}
	
	if (mymap.count(node2)==0)
	{
		if (k>=NumNodes) return false;
		else
		{
			mymap[node2] = k;
			k++;
		}
	}
	
	matrix[mymap[node1]*NumNodes+mymap[node2]] = true;
	matrix[mymap[node2]*NumNodes+mymap[node1]] = true;

	return true;
}

