#include <iostream>
#include <list>

using namespace std;

void Mostrar(const list<int> &lista) {

	list<int>::const_iterator it;

	for (it=lista.begin();it!=lista.end();it++) {
		cout<<*it<<',';
	}

	cout<<endl;
}

int main() {

	  list<int> lista;

	  srand( (unsigned)time( NULL ) ); // init Rand() function


	  int j;
	  for (int i=0;i<10;i++) {
	          j=rand() % 100;
	          lista.push_back(j);
	  }

	cout<<"Lista original:"<<endl;
	Mostrar(lista);
	
	list<int>::iterator it;


	int insertar=100;

	it=lista.begin();
	j=rand()%lista.size();
	for (int i=0;i<j;i++,it++);

	cout<<"Insertamos "<<insertar<<" en la posicion " <<j<<endl;

	lista.insert(it,insertar);

	Mostrar(lista);

	it=lista.begin();
	j=rand()%lista.size();
	for (int i=0;i<j;i++,it++);

	cout<<"Eliminamos el valor en la posicion " <<j<<endl;

	lista.erase(it);

	Mostrar(lista);

	cout<<"Cambio el valor del primer y ultimo elemento por 101"<<endl;

	lista.back()=101;
	lista.front()=101;

	Mostrar(lista);

	cout<<"Ordenamos:"<<endl;
	lista.sort();
	Mostrar(lista);

	cout<<"Invertimos:"<<endl;
	lista.reverse();
	Mostrar(lista);
}
