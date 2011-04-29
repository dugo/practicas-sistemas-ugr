/**
@file Fichero que contiene el codigo de la codificacion
*/
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include "codigo_huffman.h"

using namespace std;

/**
@brief Lee un fichero
@param nombre: Nombre del fichero
@param len: Longitud del fichero, es MODIFICADo.
@return Contenido del fichero

Lee un fichero completo y devuelve su contenido y longitud.
*/
char*  Leer_fichero(const char *nombre, int &len);

/**
@brief Funcion principal
@param argc: Numero de argumentos
@param argv: Argumentos

Funcion principal del programa de codificacion.
*/
int main(int argc, char** argv) {

  if (argc!=2) {
    cout << "Formato: codifica f_entrada >fsalida.huf" << endl;
    exit(0);
  }

  typedef map<char,int > mapa_frec;
  mapa_frec mf;
  char *datos;
  int len,i;

  datos = Leer_fichero(argv[1], len);

  mf.clear();

//Primera pasada, conteo de frecuencias
  i=0;
  while ( i < len ) {

    if (mf.find(datos[i]) != mf.end())
      mf[ datos[i] ] ++;
    else mf[ datos[i] ]=1;
    i++;
  }

//Obtenemos la codificación
  codigo_huffman codigo(mf);



  list<bit> bits;
  list<bit>::const_iterator it;
  pair<list<bit>,bool> p;
  char c;

//Contamos el numero de caracteres diferentes y lo escribimos
  c=0;
  for ( i=0; i < 256; i++) {
    p = codigo.devolver_codigo(static_cast<char>(i));
    if (p.second)  c++;
  }

  cout<<static_cast<int>(c)<<endl;

//Escribimos todos los carácteres y su correspondiente código
  for ( i=0; i < 256; i++) {
    p = codigo.devolver_codigo(static_cast<char>(i));
    if (p.second) {
      cout.put(static_cast<char>(i));
      cout << " ";
      for (it=p.first.begin();it != p.first.end();++it)  cout << *it;

      cout << endl;
    }
  }

//Segunda pasada, sustituimos cada carácter por su código
  i=0;
  while (i < len) {
    p = codigo.devolver_codigo(datos[i]);
    if (p.second) {
      for (it=p.first.begin();it != p.first.end();++it) {
        cout << *it;
      }
    i++;
    }
  }


  cout.flush();

  delete [] datos;
}

char*  Leer_fichero(const char *nombre, int &len) {

  ifstream f_entrada; //Fichero Base Datos;
  char *datos;
  char aux;
 
  f_entrada.open(nombre);

  if (!f_entrada) {
    cout << "Error abriendo el fichero de entrada de datos.\n";
    exit(0);
  }


  aux=0;
  len=-1;  //Cuento los bytes para reservar memoria
  do {
    f_entrada.get(aux);
    len++;
  } while (f_entrada);

  f_entrada.close();
  f_entrada.open(nombre);

  datos = new char[len];

  for (int i=0;i<len;i++)
    f_entrada.get(datos[i]);  //lee caracter del fichero de entrada

   f_entrada.close();

  return datos;
}
