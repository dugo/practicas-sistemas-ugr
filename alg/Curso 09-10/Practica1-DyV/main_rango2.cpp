#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>


using namespace std;

void dyv_rango_1 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral);
void dyv_rango_2 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral);

void rellena(vector<pair<float, float> > &v, const unsigned int &n)
{
    v.resize(n);
    for (unsigned int i=0;i<n;i++)
    {
        v[i].first = (float) rand()/RAND_MAX;
        v[i].second = (float) rand()/RAND_MAX;
    }
}
        

int main(int argc, char **argv)
{
    vector<float> rango;
    vector<pair<float, float> > v;

    clock_t antes,despues;
    unsigned int i=0,n=10000, umbral=1, NUM=100;
    double tiempo1=0.0, tiempo2;
    unsigned int fase = 0;

    srand(time(NULL));

    do
    {
        tiempo2=0.0;
        for (i=0;i<NUM;i++)
        {
            rellena(v, n);
            
            antes = clock();
            dyv_rango_1(v, rango, umbral);
            dyv_rango_2(v, rango, umbral);
            despues = clock();
            
            tiempo2 = tiempo2 + ( (double)(despues-antes) / (double)(CLOCKS_PER_SEC) );
        }
        
        tiempo2 = tiempo2 / (2.0*NUM);
        
        cout<<fase<<','<<umbral<<','<<tiempo2<<endl;
        
        if (tiempo2<tiempo1)
        {
            if (fase==0)
                umbral = umbral/2;
            else umbral--;
            
            fase++;
        }
        else if (fase!=2)
                umbral = (fase==0)?(umbral * 2):(umbral+1);
        
        tiempo1=tiempo2;
                
    }
    while (fase!=2);
    
    cout<<"El umbral optimo es:"<<umbral<<endl;
}

