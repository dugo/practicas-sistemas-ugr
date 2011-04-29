#include <iostream>
#include <time.h>
#include <queue>

using namespace std;

int main() {

  srand( (unsigned)time( NULL ) ); // init Rand() function

  queue<int> q;
  

  int j;
  int viejo,nuevo;
  for (int i=0;i<10;i++) {
          j=rand() % 100;
          cout<<j<<',';
          q.push(j);
          }

  cout<<endl;

  while(!q.empty()) {
                    cout<<q.front()<<',';
                    q.pop();
                    }
  
  cout << endl;
  system("pause");
  
}
