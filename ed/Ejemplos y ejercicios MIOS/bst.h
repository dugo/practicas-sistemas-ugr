//-*-Mode: C++;-*-

/*
  $Id: bst.h,v 1.1 2006/05/24 15:51:42 jmbs Exp $
*/
/*
  $Log: bst.h,v $
  Revision 1.1  2006/05/24 15:51:42  jmbs
  A�adiendo bst.h bst.template
  Versi�n inicial (incompleta) de BST

*/

/**
  * @file BST.h
  * @brief Definici�n de la clase BST
  *
  */

#ifndef __BST_H__
#define __BST_H__


/**
 *  @brief T.D.A. BST
 *
 * TDA BST::BST, insert, erase, find, size, empty
 * clear, begin, end, ~BST
 *
 * El TDA BST representa objetos que aBSTraen el concepto de Arbol
 * Binario de Busqueda (Binary Search Tree). Es un tipo contenedor,
 * cuyos componentes son Entradas formados por dos partes {clave,
 * valor}, de tipos Key y T, respectivamente.
 *
 * Los objetos de tipo Key deben tener las operaciones:
 * - bool operator<(const Key & a, const Key & b);
 * - bool operator==(const Key & a, const Key & b);
 *
 * Los objetos de tipo T deben tener las operaciones:
 * - bool operator==(const T & a, const T & b);
 *
 *
 */

using namespace std;

#include "bintree.h"

template <typename Key, typename T>
class BST {
private:
  struct entry;
  
  /**
   *  @brief BST<Key, T>::entry
   *
   * Es el tipo de dato base contenido en ABB
   */
  typedef pair<Key, T> entry;

  /**
       * @page repABB Rep del TDA ABB
       *
       * @section invABB Invariante de la representaci�n
       *
       * Un objeto v�lido @e rep del TDA ABB debe cumplir
       * - @c rep.arbolb.Etiqueta(n).clave != rep.arbolb.Etiqueta(m).clave para todo \e n,m 
       *   del �rbol binario
       * - Para todo nodo @c n se verifica que la @c rep.arbolb.Etiqueta(n).clave es mayor que
       *   @c rep.arbolb.Etiqueta(m).clave para todo @c m descendiente a la izquierda de @c n y
       *   menor que @c rep.arbolb.Etiqueta(u).clave para todo @c u es descendiente a la derecha de @c n
       *
       * @section faABB Funci�n de aBSTracci�n
       *
       * Un objeto v�lido @e rep del TDA ABB queda representado por el �rbol \e arbolb
       *
    */

  bool encontrar(const pair<Key, T> & e,
    typename bintree<pair<Key, T> >::node & n,
    typename bintree<pair<Key, T> >::node & nodo_padre) const;
    
void borrar_nodo(
  typename bintree<typename BST<Key, T>::entry>::node nodo,
  typename bintree<typename BST<Key, T>::entry>::node nodo_padre);


  bintree<entry> arbolb;
  
public:

  class const_iterator;
  class iterator;
  typedef unsigned int size_type;


 /**
     @brief Constructor primitivo por defecto.

     Crea un BST vac�o.
  */
  BST();

  /**
      @brief Inserta o actualiza una entrada en el BST.

      @param entrada:  Entrada a insertar en el receptor.

      Si no existe una entrada con clave igual a entrada.first,
      inserta entrada en el receptor.  Si ya existe, su
      valor asociado es reemplazado por entrada->second.
  */
  void insert(const pair<Key, T> & entrada);


  /**
     @brief Buscar una clave en el BST

     @param clave: Clave a buscar en el BST.
     @return  iterador a la posici�n del BST con la clave
              'clave', si est� en el BST. end, en otro caso.

  */
  const_iterator find(const Key & clave) const;


  /**
     @brief Eliminar una entrada en el BST.

     @param clave: Clave a buscar en el BST.

     @return true: posici�n del siguiente elemento,si 'clave'
                   existe en el receptor.end, en otro caso.

    Busca 'clave' entre las entradas del receptor.  Si la encuentra,
    la elimina y devuelve la posicici�n del siguiente elemento.
    En otro caso, devuelve la posici�n final del recorrido.
  */
  const_iterator erase(const Key & clave);


  /**
     @brief Devuelve el n�mero de entradas del receptor.

     @return  N�mero de entradas del receptor.
  */
  size_type size() const;


  /**
     @brief Vac�a el receptor.

     Elimina todas las entradas del receptor.
  */
  void clear();

  /**
     @brief Indica si el receptor est� vac�o.

     @return true, si el receptor no tiene entradas;
             false, en otro caso.
  */
  bool empty() const;


  /**
     @brief Posici�n de la primera entrada.

     @return Posici�n inicial del recorrido del receptor
     (posici�n del primer elemento).
  */
  const_iterator begin() const;

  /**
    @brief Posici�n final del ABB.

    @return Posici�n final del recorrido del receptor
    (posici�n posterior al �ltimo elemento).
  */
  const_iterator end() const;
  
#ifdef ITERATOR_BST
  
/**
     @brief Posici�n de la primera entrada.

     @return Posici�n inicial del recorrido del receptor
     (posici�n del primer elemento).
  */
  iterator begin();

  /**
    @brief Posici�n final del ABB.

    @return Posici�n final del recorrido del receptor
    (posici�n posterior al �ltimo elemento).
  */
  iterator end();
#endif
  /**
     Destructor.

     @doc
     Liberar todos los recursos asociados al receptor.
  */
  ~BST();

  class const_iterator {
  public:
    /**
       @brief Constructor primitivo por defecto.
    */
    const_iterator();
  
    /**
       @brief Constructor de copia.
    */
    const_iterator(const const_iterator & ite);

    /**
       @brief Operador de incremento.
       
       @pre El BST asociado NO ha sido modificado despu�s
       de la creaci�n del iterador receptor.
       @pre El iterador receptor NO est� al final del recorrido:
       (receptor) != end()
       
       @return  Posici�n actual en el recorrido creciente del BST
                asociado.

	Modifica el (iterador) receptor haci�ndolo apuntar al
	siguiente elemento en el recorrido creciente del
	BST asociado.
    */
    const_iterator & operator++();
    
    /**
       @brief Obtener el elemento al que apunta el const_iterator.
       
       @pre El BST asociado NO ha sido modificado despu�s
       de la creaci�n del iterador receptor.
       @pre El iterador receptor NO est� al final del recorrido:
       (receptor) != end()
       
       @return
       El par <Key,T> correspondiente al dato de la posici�n actual
       del recorrido.
    */
    pair<Key,T> operator*() const;


    /**
       @brief Comparaci�n de igualdad.
       
       @param i: Segundo iterador en la comparaci�n.
       @return true, si el receptor e i tienen el mismo valor.
       false, en caso contrario.
    */
    bool operator==(const const_iterator &i) const;

    /**
       Comparaci�n de igualdad.
       
       @param i: Segundo iterador en la comparaci�n.
       @return false, si el receptor e i tienen el mismo valor.
       true, en caso contrario.
    */
    bool operator!=(const const_iterator &i) const;
    
    const_iterator & operator=(const const_iterator &i);

  private:
    friend class BST;

    typename bintree<pair<Key, T> >::const_inorder_iterator eliterador;
    
    const_iterator(const typename bintree<pair<Key, T> >::const_inorder_iterator & i);
  };
  

#ifdef ITERATOR_BST
class iterator {
  public:
    /**
       @brief Constructor primitivo por defecto.
    */
    iterator();
  
    /**
       @brief Constructor de copia.
    */
    iterator(const iterator & ite);

    /**
       @brief Operador de incremento.
       
       @pre El BST asociado NO ha sido modificado despu�s
       de la creaci�n del iterador receptor.
       @pre El iterador receptor NO est� al final del recorrido:
       (receptor) != end()
       
       @return  Posici�n actual en el recorrido creciente del BST
                asociado.

 Modifica el (iterador) receptor haci�ndolo apuntar al
 siguiente elemento en el recorrido creciente del
 BST asociado.
    */
    iterator & operator++();
    
    /**
       @brief Obtener el elemento al que apunta el iterator.
       
       @pre El BST asociado NO ha sido modificado despu�s
       de la creaci�n del iterador receptor.
       @pre El iterador receptor NO est� al final del recorrido:
       (receptor) != end()
       
       @return
       El par <Key,T> correspondiente al dato de la posici�n actual
       del recorrido.
    */
    pair<Key,T> operator*();


    /**
       @brief Comparaci�n de igualdad.
       
       @param i: Segundo iterador en la comparaci�n.
       @return true, si el receptor e i tienen el mismo valor.
       false, en caso contrario.
    */
    bool operator==(const iterator &i) const;

    /**
       Comparaci�n de igualdad.
       
       @param i: Segundo iterador en la comparaci�n.
       @return false, si el receptor e i tienen el mismo valor.
       true, en caso contrario.
    */
    bool operator!=(const iterator &i) const;
    
    iterator & operator=(const iterator &i);

  private:
    friend class BST;

    typename bintree<pair<Key, T> >::inorder_iterator eliterador;
    
    iterator(const typename bintree<pair<Key, T> >::inorder_iterator & i);
  };

#endif

};

#include "bst.template"

#endif


