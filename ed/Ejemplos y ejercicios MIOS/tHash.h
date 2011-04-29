#ifndef _THASH_
#define _THASH_

#include <vector>
using namespace std;

template <class TClave, class TDef>
class tHash {
public:
 /**
    Constuye una tabla de tamaño tama

    @param tama El tamaño de la tabla
  */
tHash(int tama);
 /**
    Constructor de copia
*/
tHash(const tHash &th);
/**
  @brief Inserta dato en la tabla

  @param dato El dato que se inserta

  Si la clave ya aparece en la tabla no se hace nada
*/
void insertar(TClave dato);

/**
  #brief Elimina la clave dato de la tabla

  @param dato El dato que se borra

  @return true si el elemento ha sido borrado

  Si la clave no aparece no se hace nada
*/
bool borrar(TClave dato);

/**
  @brief Comprueba si existe una clave

  @param dato El dato que se busca
  @param elem Si el elemento existe devuelve la definición

  @return true si el elemento aparece en la tabla
*/
bool Existe(TClave dato, TDef &elem) const;

/**
    Destruye la table hash
*/
~tHash();

class iterador;
class casillas;

iterador begin() const;
iterador end() const;

class iterador{
public:
  iterador() {};
  iterador operator++();
  TClave operator*() const
  {return (*latabla)[casilla_actual].dato;};
  bool operator==(const iterador &it) const
  {
    return (latabla==it.latabla &&
      casilla_actual==it.casilla_actual);
  };
  bool operator!=(const iterador &it) const
  {return !(*this==it);};
private:
  friend class tHash;

  vector<casillas> const *latabla;
  int casilla_actual;
};

private:
  static const char LIBRE = 'L';
  static const char OCUPADA = 'O';
  static const char BORRADA = 'B';

  class casillas {
    friend class tHash;
    friend class iterador;

    TClave dato;
    TDef def;
    char estado; // Si está LIBRE, OCUPADA o BORRADA
  public:
    inline casillas() {estado= LIBRE;};
  };

  int num_datos; // Para comprobar si está llena
  vector<casillas> tabla;
  /**
    Calcula la función hash y las de resolución de colisiones

    @param dato dato sobre el que se calcula la función
    @param intento número de intento para colocar el valor
  */
    int funcion_hash(TClave dato, int intento) const;

  /**
    Realiza la redistribución de una tabla a una más grande
  */
  void realizar_rehashing();
};

#include "tHash.template"
#endif
