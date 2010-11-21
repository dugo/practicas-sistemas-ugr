#ifndef __VT_ALG_HH__
#define __VT_ALG_HH__

#include <vector>

#include "Stretch.hh"
#include "Crossroads.hh"
#include "CGraph.hh"
#include "VTalg.hh"

/**
@brief Implementacion del algoritmo Busqueda Primero en Profundidad
@param mimapa Grafo que representa al mapa
@param ini Cruce inicial
@param fin Cruce objetivo
@return Numero de nodos explorados
*/
unsigned int BPP(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino);
/**
@brief Implementacion del algoritmo Busqueda Primero en Anchura
@param mimapa Grafo que representa al mapa
@param ini Cruce inicial
@param fin Cruce objetivo
@return Numero de nodos explorados
*/
unsigned int BPA(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino);
/**
@brief Implementacion del algoritmo Busqueda por Maxima Pendiente
@param mimapa Grafo que representa al mapa
@param ini Cruce inicial
@param fin Cruce objetivo
@return Numero de nodos explorados
*/
unsigned int BMP(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino);
/**
@brief Implementacion del algoritmo Busqueda Primero el Mejor. A*
@param mimapa Grafo que representa al mapa
@param ini Cruce inicial
@param fin Cruce objetivo
@param W Factor de peso de la funciones g y h
@return Numero de nodos explorados
*/
unsigned int BPM(CGraph<Crossroads> &mimapa, const Crossroads &ini, const Crossroads &fin, std::vector<Crossroads> &camino, const float &W);
/**
@brief Devuelve la longitud de una camino dado
@param way El camino
@return Longitud
*/
float lengthPath(std::vector<Crossroads> &way);

#endif
