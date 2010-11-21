#ifndef __VT_IO_HH__
#define __VT_IO_HH__

#include <vector>
#include <map>
#include <string>
#include "Crossroads.hh"
#include "Stretch.hh"
#include "CGraph.hh"

/**
@brief Carga los cruces desde un fichero
@param file Fichero origen
@param crossroads Asociacion de los cruces a sus nombres
*/
void loadCrossroads(const std::string &file, std::map<std::string, Crossroads> &crossroads);
/**
@brief Carga los tramos desde un fichero
@param Fichero origen
@param stretchs Tramos
*/
void loadStretch(const std::string &file, std::vector<Stretch> &stretchs);
/**
@brief Construye el mapa en un grafo
@param crossroads Asociacion de los cruces a sus nombres
@param stretchs Vector con los cruces
@param mymap Mapa resultante
*/ 
void buildMap(std::map<std::string, Crossroads> &crossroads, std::vector<Stretch> &stretchs, CGraph<Crossroads> &mymap);
/**
@brief Escrite una ruta o camino en un fichero
@param file Fichero destino
@param way Ruta
*/
void writePath(const std::string &file, const std::vector<Crossroads> &way);
/**
@brief Devuelve el nombre de un cruce por su identificador numerico
@param cross La asociacion de los cruces a sus nombresç
@param id Identificador numerico del cruce
@return El nombre del cruce
*/
std::string getCrossName(std::map<std::string, Crossroads> cross, const int &id);
	
#endif
