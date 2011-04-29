#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <vector>
#include <list>
using namespace std;

template <class KeyClass, class DefClass>
class hash_table {

class casilla;

public:
class const_iterator;

 /**
    Constuye una tabla de tamaño tama

    @param tama El tamaño de la tabla
  */
hash_table(int tama);
 /**
    Constructor de copia
*/
hash_table(const hash_table &th);
/**
  @brief Inserta dato en la tabla

  @param dato El dato que se inserta

  Si la clave ya aparece en la tabla no se hace nada
*/
void insert(const KeyClass &dato, const DefClass &elem=DefClass());

/**
  #brief Elimina la clave dato de la tabla

  @param dato El dato que se borra

  @return true si el elemento ha sido borrado

  Si la clave no aparece no se hace nada
*/
bool erase(const KeyClass &dato);

/**
  @brief Comprueba si existe una clave

  @param dato El dato que se busca
  @param elem Si el elemento existe devuelve la definición

  @return true si el elemento aparece en la tabla
*/
bool find(const KeyClass &dato, DefClass &elem) const;

/**
  @brief Devuelve el número de elementos.

  @return Número de elementos.
    */
int size( ) const;


/**
  @brief Determina si la tabla hash está vacía

  @return true, si no tiene elementos,
               false, en caso contrario.

  Indica si la tabla hash está vacía o no
*/
bool empty( ) const;

const_iterator begin() const;
const_iterator end() const;

/**
    Destruye la table hash
*/
~hash_table();

private:
  class casilla {
    friend class hash_table;
    public:
      casilla(KeyClass dat, DefClass de) {dato = dat; def = de;};
      pair<KeyClass, DefClass> datos() const {
	return pair<KeyClass, DefClass>(dato, def);
	}; 
    private:
    KeyClass dato;
    DefClass def;
  };

  int num_datos;
  vector< list<casilla> > tabla;

  /**
    Calcula la función hash

    @param dato dato sobre el que se calcula la función
  */
  int funcion_hash(KeyClass dato) const;

  /**
    Realiza la redistribución de una tabla a una más grande
  */
  void realizar_rehashing();
  
public:
class const_iterator {
public:
  friend class hash_table;

  const_iterator() {};
  const_iterator operator++(int);
  pair<KeyClass, DefClass> operator*() const {return (*posicion_actual).datos();};
  bool operator==(const const_iterator &it) const
  {
    return posicion_actual==it.posicion_actual;
  };
  
  bool operator!=(const const_iterator &it) const
  {return !(*this==it);};
  
private:

  vector<list<casilla> > const *latabla;
  int list_actual;
  typename list<casilla>::const_iterator posicion_actual;
};


};




#include "hash_table.template"
#endif
