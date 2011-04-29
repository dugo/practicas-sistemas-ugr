#ifndef _T_HASH_
#define _T_HASH_

#include <vector>
#include <list>
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
void insertar(TClave dato, TDef elem);

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

struct casilla;

friend class iterador{
public:
  iterador() {};
  iterador operator++(int);
  const TClave &operator*() const
  {
    return (*posicion_actual).dato;
  };
  bool operator==(const iterador &it) {
    return posicion_actual==it.posicion_actual;};
  bool operator!=(const iterador &it) {
    return !(*this==it);
  };
private:
  friend class tHash;
  vector<list<casilla> > const *latabla;
  int Lista_actual;
  typename list<casilla>::const_iterator posicion_actual;
};

iterador begin() const;
iterador end() const;

private:
  struct casilla {
    TClave dato;
    TDef def;
  };

  int num_datos;
  vector< list<casilla> > tabla;

  int funcion_hash(TClave dato) const;
};

#include "tHash.template"

#endif
