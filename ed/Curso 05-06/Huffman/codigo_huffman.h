/**
@file Fichero de cabecera de la clase codigo_huffman
*/
#include <queue>
#include <list>
#include <map>

typedef bool bit;

using namespace std;

/**
@brief	Clase codigo_huffman

Encargada de la gestion de los codigos.
*/
class codigo_huffman {

  public:
/**
@brief	Constructor por defecto
@param mf: Mapa de frecuencias.

Construye la clase y obtiene los codigos mediante un
mapa de frecuencias.
*/
    codigo_huffman(const map<char,int> & mf);
/**
@brief Destructor
*/
    ~codigo_huffman();
/**
@brief Constructor de copia
@param p: clase que va a ser copiada.
*/
    codigo_huffman(const codigo_huffman &p);

/**
@brief Operador de asignacion
@param p: clase que va a ser asignada.
*/
    codigo_huffman &operator=(const codigo_huffman &p);

/**
@brief Inserta un codigo
@param c: Par<caracter, lista de bits>

Inserta el par c en la lista de codigos.
*/

/**
@brief	Devuelve el codigo correspondiente a un caracter.
@param c: Caracter.
@return Par <lista de bits,booleano>
*/
    pair<list<bit>,bool> devolver_codigo( char c);

/**
@brief	Devuelve un caracter teniendo su codigo.
@param cd: Lista de bits, el código.
@return Par <caracter,booleano>
*/
    pair<char,bool> devolver_caracter(const list<bit> & cd);

  private:
    map<char,list<bit> > C;

};
