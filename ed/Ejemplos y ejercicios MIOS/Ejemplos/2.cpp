#include <iostream>
#include <pair.h>
#include <string>
#include <queue>
#include <list>

using namespace std;

int main() {

	list<pair<int,string> > lista;

	lista.push_back(pair<int,string>(5,"polla"));
	lista.push_back(pair<int,string>(7,"Tengo"));
	lista.push_back(pair<int,string>(3,"un"));
	lista.push_back(pair<int,string>(4,"como"));
	lista.push_back(pair<int,string>(1,"vino"));
	lista.push_back(pair<int,string>(6,"la"));
	lista.push_back(pair<int,string>(2,"litro"));

	priority_queue<pair<int,string> > cola;

	for (list<pair<int,string> >::iterator it=lista.begin();it!=lista.end();it++)
		cola.push(*it);

	while(!cola.empty()) {
		cout<<cola.top().second<<' ';
		cola.pop();
	}
	cout<<endl;

}
