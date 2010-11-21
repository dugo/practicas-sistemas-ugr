#include <iostream>
#include <cstdlib>
#include <cassert>

#include "Stretch.hh"
#include "Crossroads.hh"
#include "CGraph.hh"
#include "VTio.hh"
#include "VTalg.hh"

using namespace std;

int main(int argc, char **argv)
{
	if (argc<6 || argc>7)
	{
		cout<<"Uso: pathfinder <cruces.txt> <tramos.txt> <cruce_origen>  <cruce_dest> <fichero_camino> [<w>]\n";
		exit(0);
	}
	
	cout<<"Leyendo datos...\n";
	
	string fcruces = argv[1], ftramos = argv[2],orig,dest;
	
	float w = 0.5;

	
	if (argc>6)
	{
		w = strtof(argv[6], (char **)NULL);
		assert(w>=0.0 && w<=1.0);
	}
	
	map<string, Crossroads> cruces;
	vector<Stretch> tramos;
	
	// Cargo cruces y tramos
	loadCrossroads(fcruces,cruces);
	loadStretch(ftramos, tramos);
	
	// Obtengo los nombres de los cruces para procesarlos
	orig = getCrossName(cruces,atoi(argv[3]));
	dest = getCrossName(cruces,atoi(argv[4]));
	assert(orig.length()>0 && dest.length()>0);
	
	// Construyo el grafo con la informacion anterior
	CGraph<Crossroads> mimapa(cruces.size());
	buildMap(cruces, tramos, mimapa);

	vector<Crossroads> camino;
		
	cout<<"Procesando...\n";
	int nodos = BPM(mimapa, cruces[orig], cruces[dest], camino, w);
	
	if (camino.size()>0)
	{
		writePath(argv[5], camino);
		cout<<"Camino escrito en el fichero "<<argv[5]<<endl;
	}
	else cout<<"No se ha encontrado un camino entre los dos nodos\n";
	
	cout<<"Numero de nodos explorados: "<<nodos<<endl;
	cout<<"Longitud del camino: "<<lengthPath(camino)<<endl;
}

#include "CGraph.cc"
