/**
@file Fichero de codigo de la clase codigo_huffman

Solo para decodificacion lineal.
*/
#include "decodigo_huffman.h"
#include <string>
#include <math.h>

decodigo_huffman::decodigo_huffman()
{
  this->decodificando = 0;
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
  list<bit>::const_iterator it;
  pair<char,bool> p('\0',false);
  int i=0;

  if (this->decodificando==0) {
    this->itr_dec1 = (this->C).begin();
    this->itr_dec2 = (this->C).begin();
  }

  it = (this->itr_dec1)->second.begin();

  for (i=0; i<this->decodificando;i++ ) ++it;

  while(*it != actual) {
    ++this->itr_dec1;

    it = (this->itr_dec1)->second.begin();
    for (i=0; i<this->decodificando;i++ ) ++it;
  }


  if (decodificando==0) {
    i=0;
    it = (this->itr_dec2)->second.begin();
    for (i=0; i<this->decodificando;i++ ) ++it;

    while(*it == actual) {
      ++this->itr_dec2;

      it = (this->itr_dec2)->second.begin();
      for (i=0; i<this->decodificando;i++ ) ++it;
    }

  --this->itr_dec2;
  }
  else {
    i=0;
    it = (this->itr_dec2)->second.begin();
    for (i=0; i<this->decodificando;i++ ) ++it;

    while(*it != actual && this->itr_dec2!=this->itr_dec1) {
      --this->itr_dec2;

    it = (this->itr_dec2)->second.begin();
    for (i=0; i<this->decodificando;i++ ) ++it;

    }
  }

  this->decodificando++;

  if (this->itr_dec1 == this->itr_dec2) {
    p.first = this->itr_dec1->first;
    p.second = true;
    this->decodificando=0;
  }

  return p;
}

void
decodigo_huffman::listo()
{                               

  list<pair<char,list<bit> > >::iterator itr, ant;
  itr = (this->C).begin();
  ++itr;                       
  while (itr != (this->C).end()) {
    ant = itr;
    --ant;
    if( lex(ant->second,itr->second) ) { 
      for (; lex(ant->second,itr->second) && ant!=(this->C).begin(); --ant);

      if (ant==(this->C).begin() && lex(ant->second,itr->second) )
        (this->C).insert((this->C).begin(),*itr);

      else {
        ant++;
        (this->C).insert(ant,*itr);
      }
      itr = (this->C).erase(itr);
    }
    else ++itr;
  }

  (this->C).reverse();

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





