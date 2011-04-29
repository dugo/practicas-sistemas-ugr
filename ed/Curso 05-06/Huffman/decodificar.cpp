/**
@file Fichero de codigo para el decodificador
*/
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include "decodigo_huffman.h"

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
@brief Convierte de cadena de caracteres (cstring) a enteros.
@param cstring: cadena de caracteres a convertir.
@return valor entero.

Convierte una cadena de caracteres a enteros, tambien comprueba que
esta corresponda a un numero.
*/
int cstring2int(char *cstring);

/**
@brief Convierte un caracter a bit.
@param c: caracter.
@retval false si el caracter es '0', true en caso contrario.
*/
bit char2bit(const char &c);

/**
@brief Lee una linea
@param datos: Vector que almacena los caracteres
@param i: Posicion a partir de la cual ahi que leer, es MODIFICADO.
@return Linea completa
*/
char* Leer_linea(char *datos,int &i);

/**
@brief Funcion principal
@param argc: Numero de argumentos
@param argv: Argumentos

Funcion principal del programa de decodificacion.
*/
int main(int argc, char** argv) {

  if (argc!=2) {
    cout << "Formato: "<<argv[0]<<"  datos.huf >datos.txt" << endl;
    exit(0);
  }

  char *datos,*linea;
  int len,cars,i,g,h;
  pair<char,list<bit> > p;
  pair<char, bool> pc;

  datos = Leer_fichero(argv[1], len);

  i=0;
  cars = cstring2int(Leer_linea(datos, i));

  decodigo_huffman dec;

//Leemos los caracteres y los ordenamos
  for (g=0;g<cars;g++) {
    linea = Leer_linea(datos,i);
    p.first = linea[0];
    p.second.clear();

    h=2;
    while(linea[h] != '\0') {
      p.second.push_back( char2bit(linea[h]) );
      h++;
    }
    dec.insertar_codigo(p);
  }

  dec.listo();

  for(; i < len; i++) {
    pc = dec.decodifica( char2bit(datos[i]) );

    if (pc.second) cout << pc.first;
  }

  cout << endl;

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


int cstring2int(char *cstring) {
  int i,g,ret;
  bool neg=false;

  if (cstring[0] == '-')  {
    neg = true;
    cstring++;
  }

  i=0;
  while (cstring[i]!='\0'&&cstring[i]!='.')
    i++;

  ret=0;
  for (g = 0; g < i ; g++ )
    ret+=static_cast<int>((cstring[g] - 48) * pow(10.0, (i - g - 1)));

  return (neg) ? (ret*-1) : (ret); 
}

char* Leer_linea(char *datos,int &i) {
  int g,len;
  char *ret;

  //Cuento los caracteres
  len=1;
  while(datos[i+len]!='\n')  len++;

  ret = new char[len+1];

  ret[0] = datos[i];

  for (g=0;g<len;g++) {
    ret[g] = datos[i];    
    i++;
  }
  i++;

  ret[len] = '\0';

  return ret;
}

bit char2bit(const char &c) {

  return (c!='0');

}

