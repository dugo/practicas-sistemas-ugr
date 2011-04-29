//fichero ejemplos.cpp
#include "ejemplos.h"

void tecla() {
char c;
cout<<endl<<">>> Escriba cualquier carácter y pulse intro para continuar.";
cin>>c;
}

int main() {

//Prueba del constructor por defecto.
cout<<endl<<"Prueba del constructor por defecto.";
matriz<int> m1;
cout<<m1;
tecla();

//Prueba del constructor por defecto, dándole los valores de filas y columnas.
cout<<endl<<"Prueba del constructor por defecto, dándole los valores de filas y columnas, debe construir una matriz 3x3.";
matriz<int> m2(3,3);
cout<<m2;
tecla();

//Prueba del constructor baso de un dato de tipo T.
cout<<endl<<"Prueba del constructor baso de un dato de tipo T, debe de construir una matriz 3x3 siendo todos sus valores 2.";
matriz<int> m3(3,3,2);
cout<<m3;
tecla();

//Prueba del comparador de igualdad.
cout<<endl<<"Prueba del comparador de igualdad, devuelve 1 si son iguales, 0 en caso contrario."<<endl;
cout<<endl<<(m3==m2)<<endl;
m2=m3;
cout<<(m3==m2)<<endl;
tecla();

//Prueba del comparador de desigualdad.
cout<<endl<<"Prueba del comparador de desigualdad, devuelve 0 si son iguales, 1 en caso contrario."<<endl;
cout<<endl<<(m3==m2)<<endl;
m2=matriz<int>(4,2);
cout<<(m3==m2)<<endl;
tecla();

//Numero de filas y columnas.
cout<<endl<<"Devuelve el numero de filas y columnas de una matriz 4x2, mediante las funciones nfilas() y ncols()."<<endl;
m1=matriz<int>(4,2,5);
cout<<endl<<"Filas:"<<m1.nfilas()<<endl;
cout<<"Columnas:"<<m1.ncols()<<endl;
tecla();

//Cambia el numero de filas.
cout<<endl<<"Tenemos una matriz 4x3 y cambiamos sus dimensiones a 2x3 mediante el método nfilas(int n)."<<endl;
m1=matriz<int>(4,3);
for (int i = 0;i<4;i++)
  for (int g= 0;g<3;g++)
    m1.set(i,g,i+g);
cout<<endl<<"Matriz original:"<<m1;
m1.nfilas(2);
cout<<"Matriz cambiada:"<<m1;
tecla();

//Cambia el numero de columnas.
cout<<endl<<"Tenemos una matriz 4x4 y cambiamos sus dimensiones a 4x3 mediante el método ncols(int n)."<<endl;
m1=matriz<int>(4,4);
for (int i = 0;i<4;i++)
  for (int g= 0;g<4;g++)
    m1.set(i,g,i+g);
cout<<endl<<"Matriz original:"<<m1;
m1.ncols(3);
cout<<"Matriz cambiada:"<<m1;
tecla();

//Obtenemos datos.
cout<<endl<<"Tenemos una matriz 4x4 y obtenemos los siguientes datos mediante la función get:"<<endl;
m1=matriz<int>(4,4);
for (int i = 0;i<4;i++)
  for (int g= 0;g<4;g++)
    m1.set(i,g,i+g);
cout<<m1;
cout<<"Dato en posicion 3,2:"<<m1.get(3,2)<<endl;
cout<<"Dato en posicion 2,1:"<<m1.get(2,1)<<endl;
cout<<"Dato en posicion 0,0:"<<m1.get(0,0)<<endl;
cout<<"Dato en posicion 3,3:"<<m1.get(3,3)<<endl;
tecla();

//Cambiamos datos.
cout<<endl<<"Tenemos una matriz 4x4 y cambiamos los datos en las posiciones 0,2 y 3,1 por 23 y 17 respecticamete usando el método set."<<endl;
m1=matriz<int>(4,4);
for (int i = 0;i<4;i++)
  for (int g= 0;g<4;g++)
    m1.set(i,g,i+g);
cout<<endl<<"Matriz original:"<<m1;
m1.set(0,2,23);
m1.set(3,1,17);
cout<<"Matriz cambiada:"<<m1;
tecla();

//Minimos y maximos.
cout<<endl<<"Tenemos una matriz 3x4 y obtenemos sus minimos y maximos, de toda la matriz y de algunas filas, usamos para ello las funciones maximo, minimo, maximo_fila y minimo_fila:"<<endl;
m1=matriz<int>(3,4);
m1.set(0,0,3);
m1.set(0,1,2);
m1.set(0,2,10);
m1.set(0,3,67);
m1.set(1,0,4);
m1.set(1,1,9);
m1.set(1,2,6);
m1.set(1,3,-12);
m1.set(2,0,1);
m1.set(2,1,-5);
m1.set(2,2,4);
m1.set(2,3,7);

cout<<endl<<"Matriz:"<<m1;
cout<<"Minimo de toda la matriz:"<<m1.minimo()<<endl;
cout<<"Maximo de toda la matriz:"<<m1.maximo()<<endl;
cout<<"Minimo de la fila 0:"<<m1.minimo_fila(0)<<endl;
cout<<"Minimo de la fila 1:"<<m1.minimo_fila(1)<<endl;
cout<<"Maximo de la fila 1:"<<m1.maximo_fila(1)<<endl;
cout<<"Maximo de la fila 2:"<<m1.maximo_fila(2)<<endl;
tecla();

//Simetria.
cout<<endl<<"Tenemos dos matrices, la primera es simétrica y la segunda no. Devuelve 1 si es simétrica, 0 en caso contrario, utilizando la función simetrica()"<<endl;
m1=matriz<int>(3,3);
m1.set(0,0,7);
m1.set(0,1,20);
m1.set(0,2,8);
m1.set(1,0,20);
m1.set(1,1,-4);
m1.set(1,2,2);
m1.set(2,0,8);
m1.set(2,1,2);
m1.set(2,2,0);

m2=matriz<int>(3,3);
m2.set(0,0,7);
m2.set(0,1,6);
m2.set(0,2,8);
m2.set(1,0,12);
m2.set(1,1,-4);
m2.set(1,2,2);
m2.set(2,0,-9);
m2.set(2,1,32);
m2.set(2,2,89);

cout<<endl<<"Matriz1:"<<m1;
cout<<"Matriz2:"<<m2;
cout<<"¿Es simétrica Matriz1?"<<m1.simetrica()<<endl;
cout<<"¿Es simétrica Matriz2?"<<m2.simetrica()<<endl;
tecla();

//Traspuesta.
cout<<endl<<"Tenemos una matriz 3x2 y obtenemos su traspuesta, mediante la función traspuesta()."<<endl;
m1=matriz<int>(3,2);
m1.set(0,0,7);
m1.set(0,1,20);
m1.set(1,0,20);
m1.set(1,1,-4);
m1.set(2,0,8);
m1.set(2,1,2);
cout<<"Matriz original:"<<m1;
cout<<"Matriz traspuesta:"<<m1.traspuesta();
tecla();

//Operador de extracción.
cout<<endl<<"No creo que sea necesario probar la funcionalidad del operador de extracción, puesto que todas las matrices escritas han sido mediante él.";
tecla();

cout<<endl<<">>> Fin de los ejemplos."<<endl<<endl;
}
