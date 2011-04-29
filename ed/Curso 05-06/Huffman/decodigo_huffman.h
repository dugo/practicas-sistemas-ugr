/**
@file Fichero de cabecera de la clase decodigo_huffman
*/
#include <queue>
#include <list>
#include <map>
#include "bintree.h"

typedef bool bit;

using namespace std;

/**
@brief Clase decodigo_huffman

Encargada de la decodificacion.
*/
class decodigo_huffman {

  public:
/**
@brief Constructor por defecto

Inicializa la clase como vacia.
*/
    decodigo_huffman();

/**
@brief Destructor
*/
    ~decodigo_huffman();
/**
@brief Constructor de copia
@param p: clase que va a ser copiada.
*/
    decodigo_huffman(const decodigo_huffman &p);

/**
@brief Operador de asignacion
@param p: clase que va a ser asignada.
*/
    decodigo_huffman &operator=(const decodigo_huffman &p);

/**
@brief Inserta un codigo
@param c: Par<caracter, lista de bits>

Inserta el par c en la lista de codigos.
*/

    void insertar_codigo(const pair<char,list<bit> > & c);
/**
@brief Decodifica
@param actual: bit por el que vamos decodificando.
@return Par<caracter,booleano>
*/
    pair<char,bool> decodifica( bit actual );
/**
@brief Listo

Ordena los codigos lexicamente en el caso de la decodificacion lineal,
en el caso de la decodificacion mediante arboles binarios, genera todos
los arboles.
*/
    void listo();

  private:
    bintree<char> A;
    list<pair<char,list<bit> > > C;
    list<pair<char,list<bit> > >::const_iterator itr_dec1, itr_dec2;
    bool lex(const list<bit> & bits2, const list<bit> & bits1);
    int decodificando;

};
