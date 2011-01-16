/**
@file dyv_tornillos_y_tuercas.cpp
@brief Solución al problema de los tornillos y las tuercas
*/
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "objeto.hpp"

using namespace std;

/**
@brief Función recursiva para el cálculo tornillos y tuercas
@param tor Vector con los tornillos a ordenar. ES MODIFICADO
@param tuer Vector con las tuercas a ordenar. ES MODIFICADO
@param ini Marca el comienzo del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
@param fin Marca el final del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
*/
void dyv_tornillos_y_tuercas_rec (vector<tornillo> &tor,
                                  vector<tuerca> &tuer,
                                  const unsigned int &ini,
                                  const unsigned int &fin)
{
    if (fin-ini+1<=1) return;

    unsigned int i, izq=ini+1,der=fin, posmedia;
    
    // Posicion aleatoria
    unsigned int pos = ini+static_cast<int> (static_cast<double>(fin-ini+1)*rand()/(RAND_MAX+1.0));
    
    tornillo miTor = tor[pos];
    tuerca miTuer;
    bool salir = false;

    // Pongo al principio el tornillo
    if (pos!=ini)
        swap(tor[pos], tor[ini]);

    // Obtengo la tuerca y la pongo al principio
    for (i=ini;i<=fin && !salir;i++)
        if (!compara(miTor, tuer[i]))
        {
            miTuer = tuer[i];
            if (i!=ini)
                swap(tuer[i], tuer[ini]);
            salir = true;
        }
    

    // Ordeno las tuercas
    while (izq < der)
    {
        while (izq<der && (compara(miTor,tuer[izq])==1)) izq++;
        while (izq<der && (compara(miTor,tuer[der])==-1)) der--;

        swap(tuer[izq],tuer[der]);
    }
    
    posmedia = (compara(miTor,tuer[izq])==1)?izq:izq-1;
    if(posmedia!=ini) swap(tuer[posmedia], tuer[ini]);
    
    // Ordeno los tornillos
    izq = ini+1; der = fin;
    while (izq < der)
    {
        while (izq<der && (compara(tor[izq],miTuer)==-1)) izq++;
        while (izq<der && (compara(tor[der],miTuer)==1)) der--;

        swap(tor[izq],tor[der]);
    }
    
    posmedia = (compara(tor[izq],miTuer)==-1)?izq:izq-1;
    if(posmedia!=ini) swap(tor[posmedia], tor[ini]);
    
    /*
     De ini a posmedia-1:   Elementos menores que el pivote
     posmedia:              El pivote
     De posmedia+1 a fin:   Elementos mayores que el pivote
    */
    dyv_tornillos_y_tuercas_rec(tor, tuer, ini, posmedia-1);
    dyv_tornillos_y_tuercas_rec(tor, tuer, posmedia+1, fin);
}

/**
@brief Función principal para el cálculo tornillos y tuercas
*/
void dyv_tornillos_y_tuercas (const vector<tornillo> tor,
                              const vector<tuerca> tuer,
                              vector<tornillo> &tor_ordenado,
                              vector<tuerca> &tuer_ordenado)
{
    srand(time(NULL));
    
    tor_ordenado = tor;
    tuer_ordenado = tuer;
    
    dyv_tornillos_y_tuercas_rec(tor_ordenado, tuer_ordenado, 0, tor.size()-1);
}

void dyv_tornillos_y_tuercas (const vector<tornillo> tor,
                              const vector<tuerca> tuer,
                              vector<tornillo> &tor_ordenado,
                              vector<tuerca> &tuer_ordenado);
