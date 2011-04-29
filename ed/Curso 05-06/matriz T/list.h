/**
  @brief TDA list
  @file list.h
  
 */
 
#ifndef __LIST__
#define __LIST__

/**
  TDA list

  TDA list::list, empty, clear, size, insert, erase,
          begin, end, push_back, push_front,
          pop_back, pop_front, back_front, ~list

  Cada objeto del TDA lista de T, modela listas de
  objetos del dominio T. Cada objeto (instancia)
  del TDA lista tiene vinculado un conjunto de
  posiciones distinto.
  
  Son mutables.
  Residen en memoria din�ica.
    

*/
template <class T>
class list {
public:
  class iterator;
  class const_iterator;
  typedef unsigned int size_type;

  /**
    @brief Constructor primitivo.
    Crea una lista vac�.
  */
  list();

  /** 
    @brief Constructor de copia.
    @param l: lista que se copia.
    Crea una lista que es copia de l.
  */
  list(const list<T> & l);
  
  /**
    @brief Constructor de copia de un rango.
    @param inicio: apunta al elemento inicial a copiar.
    @param final: apunta al elmento final a copiar.
    Crea un nuevo conjunto que es copia del rango
            [inicio,final).
  */
  list(iterator inicio, iterator final);

  /**
    @brief Informa si la lista est�vac�.     
    @return true, si la lista est�vac�.
            false, en otro caso.
  */
  bool empty() const;

  /**
    @brief Borra todos los elementos del contenedor.
    Deja el contenedor completamente vac�.
        Eficiencia: lineal.
  */
  void clear ();

  /**
    @brief Devuelve el nmero de elementos de la lista.
    @return nmero de elementos de la lista.
  */
  size_type size() const;
  
  /**
    @brief Inserta un elemento en la lista.   
    @param p: posici� delante de la que se inserta. Debe
          ser una posici� v�ida para el objeto lista
          receptor.
    @param elemento: elemento que se inserta.
    @return posici� del elemento insertado.
    Inserta un elemento con el valor 'elemento' en la
          posici� anterior a 'p'. MODIFICA al objeto
          receptor.
  */
  iterator insert(iterator p, const T & elemento);

  /**
    @brief Elimina un elemento de la lista. 
    @param p: posici� del elemento que se borra. Debe
              ser una posici� v�ida para el objeto
              lista receptor.
    @return posici� siguiente a la del elemento borrado.
    @doc Destruye el objeto que ocupa la posici� 'p'
        en el objeto lista receptor.
  */
  iterator erase(iterator p);

  /**
    @brief Obtiene la primera posici� de la lista.     
    @return la primera posici� de la lista receptora.
  */
  iterator begin();
  
  /**
    @brief Obtener la primera posici� de la lista.    
    @return la primera posici� de la lista receptora.
  */
  const_iterator begin() const;
  
  /**
    @brief Obtener la posici� posterior al ltimo
          elemento de la lista.
    @return la posici� siguiente al ltimo elemento de
            la lista receptora.
  */
  iterator end();

  /**
    @brief Obtener la posici� posterior al ltimo
          elemento de la lista.
    @return la posici� siguiente al ltimo elemento de
            la lista receptora.
  */
  const_iterator end() const;
  
  /**
    @brief A�de un elemento al final de la lista.
    @param dato Elemento a a�dir al final de la lista.
  */
  void push_back(const T &dato);
  
  /**
    @brief A�de un elemento al principio de la lista.
    @param dato Elemento a a�dir al final de la lista.
  */
  void push_front(const T &dato);
  
  /**
    @brief Elimina el elemento del final de la lista.
  */
  void pop_back();
  
  /**
    @brief Elimina el elemento del principio de la lista.
  */
  void pop_front();
  
  /**
    @brief Devuelve el elemento al final de la lista.
  */
  T & back();
  
  /**
    @brief Devuelve el elmento del principio de la lista.
  */
  T & front();

  /**
    @brief Devuelve el elemento al final de la lista.
  */
  const T & back() const;
  
  /**
    @brief Devuelve el elmento del principio de la lista.
  */
  const T & front() const;


  /**
    @brief Operador de asignaci�.
    @param l: lista que se asigna.
    Asigna al receptor una copia de l. Devuelve el receptor.
  */
  list<T> & operator=(const list<T> & l);

  /**
    @brief Comparaci� de igualdad.
    @param l: lista con que se compara el receptor.
    @return true: si el receptor y l son iguales.
            false: en caso contrario.
  */
  bool operator==(const list<T> & l) const;

  /**
    @brief Intercambia el contenido del receptor y 
            del argumento.
    @param l: lista a intercambiar con el receptor.
              ES MODIFICADO.
    Este m�odo asigna el contenido del receptor al par�etro
    y el del par�etro al del receptor.
  */
  void swap (list<T> & l);

  /**
    @brief Destructor.
    @post El receptor es MODIFICADO.
  
    El receptor es destruido liberando todos los 
    recursos que usaba.
    Eficiencia: lineal.
  */
  ~list();

  
private:
  struct nodo_lista {
    nodo_lista * anterior;
    T elemento;
    nodo_lista * siguiente;
  };

public:
  class iterator {
  public:
    iterator();
    iterator(const iterator & i);
    T & operator*();
    iterator & operator++();
    iterator & operator--();
    bool operator==(const iterator &i) const;
    bool operator!=(const iterator &i) const;
  private:
    iterator(nodo_lista * p);

    nodo_lista * eliterador;
    friend class list;
    friend class const_iterator;
  };

  class const_iterator {
  public:
    const_iterator();
    const_iterator(const const_iterator & i);
    const_iterator(const iterator & i);
    T operator*() const;
    const_iterator & operator++();
    iterator & operator--();
    bool operator==(const const_iterator &i) const;
    bool operator!=(const const_iterator &i) const;
  private:
    const_iterator(nodo_lista * p);

    nodo_lista * eliterador;
    friend class list;
  };

private:
  typedef nodo_lista * Posicion;
  Posicion cab;
  size_type num_elem;
};

#include "list.template"

#endif 
