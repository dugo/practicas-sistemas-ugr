/**
@file Fichero de codigo de la clase decodigo_huffman

Solo para decodificacion con arboles binarios.
*/
#include "decodigo_huffman.h"
#include <string>
#include <math.h>
#include "bintree.h"


decodigo_huffman::decodigo_huffman()
{
  this->decodificando=0;
}

decodigo_huffman::decodigo_huffman(const decodigo_huffman &p)
{
  if (&p == this) return;

  this->~decodigo_huffman();

  this->A=p.A;
  this->C=p.C;
}

decodigo_huffman::~decodigo_huffman()
{

  (this->C).clear();
}

decodigo_huffman&
decodigo_huffman::operator=(const decodigo_huffman &p)
{

  if (&p != this) {
  this->~decodigo_huffman();

  this->A=p.A;
  this->C=p.C;
  }

  return *this;
}

void
decodigo_huffman::insertar_codigo(const pair<char,list<bit> > & c)
{
  (this->C).push_back(c);

}

pair<char,bool>
decodigo_huffman::decodifica( bit actual )
{

}

void
decodigo_huffman::listo()
{


 
}

bool
decodigo_huffman::lex(const list<bit> & bits2, const list<bit> & bits1)
{
  list<bit>::const_iterator it;
  string str1,str2;

  for (it=bits1.begin();it!=bits1.end();++it)
    str1 = str1 + static_cast<char>(48+*it);

  for (it=bits2.begin();it!=bits2.end();++it)
     str2 = str2 + static_cast<char>(48+*it);

  return (str1>str2);
}




