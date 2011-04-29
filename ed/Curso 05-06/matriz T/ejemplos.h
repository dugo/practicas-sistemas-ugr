//fichero ejemplos.h
#ifndef __EJEMPLOS_H
#define __EJEMPLOS_H

#include <list>
#include "matriz.h"

template <class T>
class coordenadas{

  public:
    coordenadas(T d, int f, int c);
    int nfila() const;
    int ncol() const;
    T dato() const;

  private:
    T dat;
    int fila;
    int columna;
};

template <class T>
bool operator<(const coordenadas<T> &d,const coordenadas<T> &c);

#include "ejemplos.template"


bool magica(const matriz<int> &entrada);

template <class T>
list<T> minimos_fila(const matriz<T> &entrada);

matriz<int> multiplicar(const list<matriz<int> > &entrada);

template <class T>
list<coordenadas<T> > ordenada(const matriz<T> &entrada);

#endif
