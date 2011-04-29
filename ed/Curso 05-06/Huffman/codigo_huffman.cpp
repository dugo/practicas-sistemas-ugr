/**
@file Fichero de codigo de la clase codigo_huffman
*/
#include "codigo_huffman.h"

codigo_huffman::codigo_huffman(const map<char,int > & mf)
{
  map<char,int > mapa = mf;
  priority_queue<pair<int,list<char> > > Q;

  list<char> chars;
  list<bit> bits;
  typedef pair<int,list<char> > parQ;
  typedef pair<char,list<bit> > parC;


  //Meto todo el mapa en priority_queue Q.
  bits.clear();
  for (int i=0;i<256;i++) {
    if (mapa.find(static_cast<char>(i)) != mapa.end()) {

      if (i==10 && mapa['\n']==1);
      else {
        chars.clear();
        chars.push_back(static_cast<char>(i));
        parQ p1(mapa[ static_cast<char>(i) ]*-1,chars);
        Q.push( p1 );

        this->C[ static_cast<char>(i) ] = bits;
      }
    }
  }

  list<char>::const_iterator i;
  bool salir;
  int freq;

  //Genermos el codigo.
  salir=false;
  while(!salir){
    chars.clear();

    freq = Q.top().first;
    for ( i=Q.top().second.begin() ; i != Q.top().second.end(); ++i) {
      this->C[ *i ].push_front( 1 );
      chars.push_back(*i);
    }
    Q.pop();

    if (!Q.empty()) {

      freq += Q.top().first;
      for ( i=Q.top().second.begin() ; i != Q.top().second.end(); ++i) {
        this->C[ *i ].push_front( 0 );
        chars.push_back(*i);
      }

      Q.pop();
    }

    if (Q.empty())  salir = true;

    parQ p1(freq,chars);
    Q.push( p1 );
  }

}

codigo_huffman::~codigo_huffman()
{
  (this->C).clear();
}

codigo_huffman::codigo_huffman(const codigo_huffman &p)
{
  if (&p == this) return;

  this->~codigo_huffman();

  this->C = p.C;
}

codigo_huffman&
codigo_huffman::operator=(const codigo_huffman &p)
{
  if (&p != this) {
    this->~codigo_huffman();

    this->C = p.C;
  }

  return *this;
}

pair<list<bit>,bool>
codigo_huffman::devolver_codigo( char c)
{
  list<bit> bits;
  bits.clear();

  pair<list<bit>,bool> p(bits,false);

  if ((this->C).find(c) != (this->C).end()) {
    p.second = true;
    p.first = this->C[ c ];
  }

  return p;
}

pair<char,bool>
codigo_huffman::devolver_caracter(const list<bit> & cd)
{
  pair<char,bool> p('\0',false);

  int i=0;
  while (i<256 && !p.second) {
    if ((this->C).find(static_cast<char>(i) ) != (this->C).end()) {
      if (this->C[static_cast<char>(i)] == cd) {
        p.first=static_cast<char>(i);
        p.second=true;
      }
	
  i++;
    }
  }

  return p;
}


