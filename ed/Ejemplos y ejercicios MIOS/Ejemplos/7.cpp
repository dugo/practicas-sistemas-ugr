#include <iostream>
#include <vector>

using namespace std;

void Mostrar(const vector<int> &v) {

	vector<int>::const_iterator it;

	for (it=v.begin();it!=v.end();it++) {
		cout<<*it<<',';
	}

	cout<<endl;
}

int main() {

	
	//Inicializamos el vector con 10 elementos
	  vector<int> v(10);

	  srand( (unsigned)time( NULL ) ); // init Rand() function


	cout<<"Capacidad maxima del vector: "<<v.max_size()<<endl;
	cout<<"Tamaño actual del vector: "<<v.size()<<endl;

	  int j;
	  for (int i=0;i<10;i++) {
	          j=rand() % 100;
	          v[i]=j;
	  }

	v.resize(11);

	vector<int>::iterator it;

	cout<<"Vector original:"<<endl;
	Mostrar(v);

	int insertar=100;

	it=v.begin();
	j=rand()%v.size();
	for (int i=0;i<j;i++,it++);

	cout<<"Insertamos "<<insertar<<" en la posicion " <<j<<endl;

	v.insert(it,insertar);

	Mostrar(v);

	it=v.begin();
	j=rand()%v.size();
	for (int i=0;i<j;i++,it++);

	cout<<"Eliminamos el valor en la posicion " <<j<<endl;

	v.erase(it);

	Mostrar(v);
}
