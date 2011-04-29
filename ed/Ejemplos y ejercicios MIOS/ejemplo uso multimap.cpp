#include <iostream>
#include <map>

using namespace std;

int main() {

	multimap<int,int> mapa;

	srand(time(NULL)); // aki generamos la semilla.....

	for (int i=0;i<10;i++) {
		mapa.insert(pair<int,int>(i,rand()%100));
	}

	for (int i=0;i<10;i++) {
		if ((i+1)%3==0) mapa.insert(pair<int,int>(i,rand()%100));
	}

	multimap<int,int>::const_iterator it=mapa.begin();

	for (;it!=mapa.end();it++)
		cout<<(*it).first<<','<<(*it).second<<endl;

	cout<<mapa.count(8)<<endl;
}

