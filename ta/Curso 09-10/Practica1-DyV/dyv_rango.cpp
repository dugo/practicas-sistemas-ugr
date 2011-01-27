/**
@file dyv_rango.cpp
@brief Soluciones al problema de los rangos
*/
#include <map>
#include <vector>

/**
@brief Halla la diferencia absoluta entre dos floats
*/
#define DIFFABS(x,y) (float)(((x-y)<0.0)?(x-y)*-1.0:(x-y))
/**
@brief Umbral para la selección del pivote
*/
#define RANGO_QS_UMBRAL_PIVOTE 10

using namespace std;


/**
@brief Función principal para el cálculo de rangos de forma iterativa
*/
void iter_rango (const vector < pair<float,float> > S, vector<float> &rango)
{
    const unsigned int size = S.size();
    
    // Tengo que asegurarme que los rangos tienen el tamaño adecuado
    rango.resize(size);
    
    // Fácil pero ineficiente
    for (unsigned int i=0;i<size;i++)
    {
        rango[i] = 0.0;
        for (unsigned int j=0;j<size;j++)
        {
            if (i!=j &&
                S[i].first > S[j].first &&
                S[i].second > S[j].second)
                    rango[i]++;
        }
    }

}

/**
@brief Ordena mediante el algoritmo quicksort en forma creciente
@param S Vector a ordenar. ES MODIFICADO
@param P Vector de posiciones (explicación abajo). ES MODIFICADO
@param ini Marca el comienzo del subconjunto a ordenar (inclusive). NO ES MODIFICADO
@param fin Marca el final del subconjunto a ordenar (inclusive). NO ES MODIFICADO

Esta función ordena de forma creciente el vector S y también modifica el vector P
según el mismo criterio, de esta forma se puede reconstruir el vector original S.

El pivote utilizado por el algoritmo es elegido según:

    1. Primer elemento del conjunto (cuando el número de elementos es menor a RANGO_QS_UMBRAL_PIVOTE).
    2. Hallando el elemento más próximo a la media aritmética del conjunto (en caso contrario).
*/
void dyv_rango_qs (vector<float> &S, vector<unsigned int> &P, const unsigned int &ini, const unsigned int &fin)
{
    /*** Casos particulares ***/
    
    // Conjunto con un único elemento o vacío
    if (fin-ini+1<=1) return;

    // Conjunto con dos elementos
    if (fin-ini+1==2)
    {
        if (S[ini]>S[fin])
        {
            swap(S[ini],S[fin]);
            swap(P[ini],P[fin]);
        }
        return;
    }

    /*
        La elección del pivote la considero primordial sobre todo en casos
        en los que haya gran cantidad de elementos.
        
        Por lo que voy a elegir como pivote el elemento más próximo a la media
        cuando el número de elementos es mayor al valor indicado en la macro
        RANGO_QS_UMBRAL_PIVOTE (por defecto 10), en caso contrario elegiré
        el primer elemento.
        
        Teniendo como finalidad siempre la eficiencia.
    */

    unsigned int der=fin,izq=ini+1,posmedia,pospivote=ini,i;
    float pivote=S[ini]; 

    if (fin-ini+1>RANGO_QS_UMBRAL_PIVOTE)
    {
        // Hallo la media aritmetica
        float media = 0.0;
        for (i=ini;i<=fin;i++)
        {
            media += S[i];
        }
        media = media/static_cast<float>(fin-ini+1);
        
        // Ahora busco el valor más próximo a esta media
        for (i=ini+1;i<=fin;i++)
        {
            if ( DIFFABS(media, S[i]) < DIFFABS(media,pivote) )
            {
                pivote = S[i];
                pospivote = i;
            }
        }
        
        // Lo pongo al comienzo del conjunto (si no esta ya!)
        if (pospivote != ini)
        {
            swap(S[ini], S[pospivote]);
            swap(P[ini], P[pospivote]);
        }
    }

    // Realizo el intercambio de elementos
    while (izq < der)
    {
        while (izq<der && S[izq] <= pivote) izq++;
        while (izq<der && S[der]  > pivote) der--;

        swap(S[izq],S[der]);
        swap(P[izq],P[der]);
    }

    // Elijo la posicion media
    posmedia = (pivote>S[izq])?izq:izq-1;

    if (ini!=posmedia)
    {
        swap(S[ini], S[posmedia]);
        swap(P[ini], P[posmedia]);
    }
    
    dyv_rango_qs(S, P, ini, posmedia-1);
    dyv_rango_qs(S, P, posmedia+1, fin); 
}

/**
@brief Función auxiliar para el cálculo de rangos de forma iterativa
@param y Vector con las coordenadas y. NO ES MODIFICADO
@param rango Vector con los rangos calculados. ES MODIFICADO
@param ini Marca el comienzo del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
@param fin Marca el final del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
*/
void dyv_rango_it (vector<float> y, vector<float> &rango, const unsigned int &ini, const unsigned int &fin)
{
    // Sólo necesito comparar los valores de y anteriores
    for (unsigned int i=ini;i<=fin;i++)
        for (unsigned int j=ini;j<i;j++)
        {
            if (y[i]>y[j]) rango[i]++;
        }
}

/**
@brief Función recursiva para el cálculo de rangos versión 1.
@param y Vector con las coordenadas y. NO ES MODIFICADO
@param posy Vector con las posiciones y originales (antes de ordenar). NO ES MODIFICADO
@param rango Vector con los rangos calculados. ES MODIFICADO
@param ini Marca el comienzo del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
@param fin Marca el final del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
@param umbral Umbral bajo el que se aplicará el método iterativo. NO ES MODIFICADO
*/
void dyv_rango_1_rec (vector<float> &y, vector<unsigned int> &posy, vector<float> &rango, const unsigned int &ini, const unsigned int &fin, const unsigned int &umbral)
{
    // Caso base
    if (fin-ini+1<=1) return;

    /* Aplico el método iterativo,
       en lugar de adaptar la función iter_rango para utilizarla aquí
       he preferido copiar el código y adaptarlo a estas necesidades.
       Aprovecho que el vector de y's se encuentra ya ordenado por x.
    */
    if (fin-ini+1<=umbral)
    {
        dyv_rango_it(y, rango, ini, fin);
        return;
    }

    unsigned int posmedia = (ini+fin)/2,i;
    float puntosS1 = 0.0;

    dyv_rango_1_rec(y, posy, rango, ini, posmedia, umbral); // S1
    dyv_rango_1_rec(y, posy, rango, posmedia+1, fin, umbral); // S2

    // Ordeno el conjunto S por y 
    dyv_rango_qs(y, posy, ini, fin);

    for (i=ini;i<=fin;i++)
    {
        // Busco un valor de y que corresponda a un elemento de S2
        if (posy[i] > posmedia)
        {
            // Entonces los elementos de S1 anteriores a él son dominados
            rango[posy[i]]+=puntosS1;
        }
        else puntosS1++;
    }
}

/**
@brief Función principal para el cálculo de rangos versión 1
*/
void dyv_rango_1 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral)
{
    unsigned int i;
    const unsigned int size=S.size();
        
    vector<float> x(size),y(size), rango_desordenado(size);
    vector<unsigned int> posx(size), posy(size);
     
    for (i=0;i<size;i++)
    {
        x[i] = S[i].first;
        posx[i] = i;
        rango_desordenado[i] = 0.0;
    }
    
    // Ordenamos por x
    dyv_rango_qs(x,posx,0,size-1);
    
    // Este orden deben tenerlo tambien los vectores y y posy
    for (i=0;i<size;i++)
    {
        y[i] = S[posx[i]].second;
        posy[i] = i;
    }
    
    // Llamada principal a la funcion recursiva
    dyv_rango_1_rec(y, posy, rango_desordenado, 0, size-1, umbral);
    
    // Me aseguro que el vector de rangos tiene el tamaño adecuado
    rango.resize(size);
    
    // Sólo queda copiar los rangos
    for (i=0;i<size;i++)
    {
        rango[posx[i]] = rango_desordenado[i];
    }
}

/**
@brief Función recursiva para el cálculo de rangos versión 2.
@param y Vector con las coordenadas y. NO ES MODIFICADO
@param posy Vector con las posiciones y originales (antes de ordenar). NO ES MODIFICADO
@param rango Vector con los rangos calculados. ES MODIFICADO
@param ini Marca el comienzo del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
@param fin Marca el final del subconjunto en el que vamos a operar (inclusive). NO ES MODIFICADO
@param umbral Umbral bajo el que se aplicará el método iterativo. NO ES MODIFICADO
*/
void dyv_rango_2_rec (const vector<float> &y, const vector<unsigned int> &posy, vector<float> &rango, const unsigned int &ini, const unsigned int &fin, const unsigned int &umbral)
{

    // Caso base
    if (fin-ini+1<=1) return;

    /* Aplico el método iterativo,
       en lugar de adaptar la función iter_rango para utilizarla aquí
       he preferido copiar el código y adaptarlo a estas necesidades.
       Aprovecho que el vector de y's se encuentra ya ordenado por x.
    */
    if (fin-ini+1<=umbral)
    {
        dyv_rango_it(y, rango, ini, fin);
        return;
    }

    unsigned int posmedia = (ini+fin)/2,i;
    float puntosS1 = 0.0;

    dyv_rango_2_rec(y, posy, rango, ini, posmedia, umbral); // S1
    dyv_rango_2_rec(y, posy, rango, posmedia+1, fin, umbral); // S2

    for (i=0;i<y.size();i++)
    {
        /* Compruebo si el valor pertenece al conjunto S.
           Lo hago por índices, en lugar de hacerlo por la coordenada x que
           me daría eficiencia cuadrática. */
        if (posy[i] >=ini && posy[i]<=fin)
        {
            // Busco un valor de y que corresponda a un elemento de S2
            if (posy[i] > posmedia)
            {
                // Entonces los elementos de S1 anteriores a él son dominados
                rango[posy[i]]+=puntosS1;
            }
            else puntosS1++;
        }
    }
}

/**
@brief Función principal para el cálculo de rangos versión 2
*/
void dyv_rango_2 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral)
{
    unsigned int i;
    const unsigned int size=S.size();
    
    vector<float> x(size),y(size), rango_desordenado(size);
    vector<unsigned int> posx(size),posy(size);
   
    for (i=0;i<size;i++)
    {
        x[i] = S[i].first;
        posx[i] = i;
        rango_desordenado[i] = 0.0;
    }
    
    // Ordenamos por x
    dyv_rango_qs(x,posx,0,size-1);
    
    // Este orden deben tenerlo tambien los vectores y y posy
    for (i=0;i<size;i++)
    {
        y[i] = S[posx[i]].second;
        posy[i] = i;
    }
    
    // Ordenamos por y
    dyv_rango_qs(y,posy,0,size-1);
    
    // Llamada principal a la funcion recursiva
    dyv_rango_2_rec(y, posy, rango_desordenado, 0, size-1, umbral);
    
    // Me aseguro que el vector de rangos tiene el tamaño adecuado
    rango.resize(size);
    
    // Sólo queda copiar los rangos
    for (i=0;i<size;i++)
    {
        rango[posx[i]] = rango_desordenado[i];
    }
}

void iter_rango (const vector < pair<float,float> > S, vector<float> &rango);
void dyv_rango_1 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral);
void dyv_rango_2 (const vector < pair<float,float> > S, vector<float> &rango, const int umbral);
