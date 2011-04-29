#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <vector>
using namespace std;

template <class KeyClass, class DefClass>
class hash_table {

class casillas;

public:
  class const_iterator;
  typedef const_iterator iterator;

 /**
    Constuye una tabla de tamaño tama

    @param tama El tamaño de la tabla
  */
hash_table(int tama=111);
 /**
    Constructor de copia
*/
hash_table(const hash_table &th);
/**
  @brief Inserta dato en la tabla

  @param dato El dato que se inserta

  Si la clave ya aparece en la tabla no se hace nada
*/
void insert(const pair<KeyClass, DefClass> &dato);

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
const_iterator find(const KeyClass &dato) const;

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


/**
    Destruye la table hash
*/
~hash_table();

const_iterator begin() const;
const_iterator end() const;

class const_iterator{
public:
  const_iterator() {};
  const_iterator operator++();
  pair<KeyClass, DefClass> operator*() const
  {return (*latabla)[casilla_actual].dato;};
  bool operator==(const const_iterator &it) const
  {
    return (latabla==it.latabla &&
      casilla_actual==it.casilla_actual);
  };
  bool operator!=(const const_iterator &it) const
  {return !(*this==it);};
private:
  friend class hash_table;

  vector<casillas> const *latabla;
  int casilla_actual;
};

private:
  static const char LIBRE = 'L';
  static const char OCUPADA = 'O';
  static const char BORRADA = 'B';

  class casillas {
    friend class hash_table;
    friend class const_iterator;

    pair<KeyClass, DefClass> dato;
    char estado; // Si está LIBRE, OCUPADA o BORRADA
    
    public:
      casillas() {estado= LIBRE;};
  };

  int num_datos; // Para comprobar si está llena
  vector<casillas> tabla;
  /**
    Calcula la función hash y las de resolución de colisiones

    @param dato dato sobre el que se calcula la función
    @param intento número de intento para colocar el valor
  */
  int funcion_hash(KeyClass dato, int intento) const;

  /**
    Realiza la redistribución de una tabla a una más grande
  */
  void realizar_rehashing();
};

#include "hash_table.template"
#endif
