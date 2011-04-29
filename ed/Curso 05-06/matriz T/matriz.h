//fichero matriz.h
#ifndef __MATRIZ_H
#define __MATRIZ_H

#include <iostream>

using std::ostream;

template <class T>
class matriz{

  private:
    T ** items;
    int _filas, _cols;
    void reservar(int f,int c);

  public:
  /**
    @brief Constructor por defecto.
    @param f: numero de filas.
    @param c: numero de columnas.
    Crea una matriz con un numero de filas y columnas
    determinado, si no se definen estos valores, se
    sobreentiende que es una matriz 4x4.
  */
    matriz(int f = 4,int c = 4); //Constructor por defecto.
  /**
    @brief Constructor basado en un dato de tipo T.
    @param f: numero de filas.
    @param c: numero de columnas.
    @param valor: dato de tipo T.
    Crea una matriz con un numero de filas y columnas
    determinado y ha todos los datos les asigna el valor
    expresado.
  */
    matriz(int f, int c, T valor);
  /**
    @brief Constructor de copia.
    @param m: matriz que va a ser copiada.
    Crea una una matriz que es copia de m.
  */
    matriz(const matriz<T> & m); //Constructor de copia.
  /**
    @brief Destructor.
    Elimina los datos de la memoria y pone
    el número de filas y columnas a cero.
  */
    ~matriz();
  /**
    @brief Comparación de igualdad.
    @param m: matriz con la que se compara el receptor.
    @return true: si el receptor y m son iguales.
            false: en caso contrario.
  */
    bool operator==(const matriz<T> & m) const;
  /**
    @brief Comparación de desigualdad.
    @param m: matriz con la que se compara el receptor.
    @return false: si el receptor y m son iguales.
            true: en caso contrario.
  */
    bool operator!=(const matriz<T> & m) const;
  /**
    @brief Devuelve el número de filas.
  */
    int nfilas() const;
  /**
    @brief Devuelve el número de columnas.
  */
    int ncols() const;
  /**
    @brief Asigna un número de filas.
    @param n: número de filas a asignar.
    Asigna un número diferente de filas a la
    matriz, en caso de que sea menor del actual
    las filas sobrantes serán eliminadas.
  */
    void nfilas(int n);
  /**
    @brief Asigna un número de columnas.
    @param n: número de columnas a asignar.
    Asigna un número diferente de columnas a la
    matriz, en caso de que sea menor del actual
    las columnas sobrantes serán eliminadas.
  */
    void ncols(int n);
  /**
    @brief Devuelve un dato.
    @param nf: número de fila del dato.
    @param nc: número de columna del dato.
    @return dato situado en la fila nf y columna nc.
    Devuelve el dato situado en la fila nf y la
    columna nc. Se entiende como 0 la primera fila y
    como 0 la primera columna.
  */
    T get(int nf, int nc) const;
  /**
    @brief Asigna un valor.
    @param nf: número de fila.
    @param nc: número de columna.
    @param dato: valor a asignar.
    Asigna el valor dato a un elemente situado en
    la fila nf y la columna nc. Se entiende como
    0 la primera fila y como 0 la primera columna.
  */
    void set(int nf, int nc, const T &dato);
  /**
    @brief Devuelve el valor más pequeño de la matriz.
    @return el valor más pequeño de la matriz.
  */
    T minimo() const;
  /**
    @brief Devuelve el valor más pequeño de una fila.
    @param fila: una fila determinada
    @return el valor más pequeño de la fila 'fila'.
  */
    T minimo_fila(int fila) const;
  /**
    @brief Devuelve el valor más grande de la matriz.
    @return el valor más grande de la matriz.
  */
    T maximo() const;
  /**
    @brief Devuelve el valor más grande de una fila.
    @param fila: una fila determinada
    @return el valor más grande de la fila 'fila'.
  */
    T maximo_fila(int f) const;
  /**
    @brief Simetría.
    @return true: si la matriz es simétrica respecto a
    su diagonal principal.
           false: en caso contrario.
  */
    bool simetrica() const;
  /**
    @brief Devuelve la matriz traspuesta.
    @return la matriz traspuesta.
  */
    matriz<T> traspuesta() const;
  /**
    @brief Operador de asignación.
    @param m: matriz que se asigna.
    Asigna al receptor una copia de m.
  */
    void operator=(const matriz<T> & m);

};

/**
  @brief Operador de extracción.
  @param m: matriz que se escribe.
  @param s: flujo de salida, es MODIFICADO.
  Escribe las filas y las columnas de la matriz.
*/
template <class T>
ostream & operator<<(ostream & s, const matriz<T> & m);

#include "matriz.template"
#endif

