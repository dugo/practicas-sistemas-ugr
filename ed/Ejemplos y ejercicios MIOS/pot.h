#ifndef APO_H_
#define APO_H_

#include <vector>
#include <function.h>

/**
   TDA MIAPO.

   Representa un �rbol parcilamente ordenado (MIAPO o Heap) con nodos etiquetados con  datos del tipo T.

  
   T debe tener definidas las operaciones:

   - T & operator=(const T & e);
   - bool operator!=(const T & e);
   - bool operator==(const T & e);
   - bool operator<(const T & e);

   Son mutables.
   Residen en memoria din�mica.


*/


using namespace std;

#include <iostream>

template<class T,  class comparar=less<T> >
class POT
  {
  public:
 
/**
     @brief Constructor primitivo por defecto.

     Crea un POT nulo.
  */
  POT();

/**
     @brief Constructor primitivo.

     @param valor: elemento a ser insertado en el POT.

     Crea un POT con un unico elemento  etiquetado con valor.
*/
  POT(const T& valor);

/**
     @brief Constructor de copia.

     @param a: POT que se copia.

     Crea un POT duplicado exacto de a.
*/
  POT(const POT<T,comparar>& a);

/**
     @brief Insertar un elemento en el �rbol.

     @param valor: elemento a insertar en el �rbol.
     @return true si la inserci�n se ha realizado de forma correcta o false en caso contrario.

     En caso de ser necesario, la estructura del �rbol se reajusta para cumplir la propiedad APO.

     EFICIENCIA: logaritmica
*/
  void insert(const T & valor);


/** comparar()(el_POT[Padre(n)],el_POT[n])
     @brief Borra el elemento de mayor valor en el APO.

     EFICIENCIA: logaritmica
*/
  void pop();



/** 
    @brief Elimina todos los valores del �rbol

    Hace que el  POT sea vac�o.

   EFICIENCIA: lineal, O(n)
*/

  void clear();

/**
     @brief Vevuelve el elemento de mayor  valor en el �rbol.

     El APO no se modifica

     EFICIENCIA: logaritmica
*/
  const T& top( void ) const;



  /** 
      @brief Cheque si el �rbol no tiene elementos.

      @return true si el POT est� vac�o, false en caso contrario.
  */
  bool empty() const;


/** 
      @brief N�mero de elementos en el �rbol.

      @return N�mero de elementos en el �rbol. 

*/
  int size() const
  {
    return el_POT.size();
  }

/** 
      @brief Libera todos los recursos consumidos por el POT.
*/
  ~POT();
  

  private:
  vector<T> el_POT;

  comparar comp;

  static const int NULO = -1; // Posicion no valida en el arbol

  int Hijo_Izq(int n){
    if (2*n+1 > el_POT.size()-1) return -1;
    else return 2*n + 1;
   }

  int Hijo_Dcha(int n)
  { if (2*n+2 > el_POT.size()-1) return -1;
     else return 2*n+2; 
  }

  int  Padre(int n)
  {  if ((n-1)/2 < 0) return -1; 
     else return (n-1)/2;
  }

  void intercambia(int a, int b)
  { 
    swap(el_POT[a], el_POT[b]);
  }

};

#include "pot.template"



#endif
