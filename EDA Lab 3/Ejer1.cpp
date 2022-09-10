#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>

using namespace std;

int random(int n)
{
  return rand()%n;
}
vector<int> generar_punto(int dim, int n)
{
  vector<int> punto(dim);
  for(int i=0; i<dim; i++)
    punto[i]=random(n);
  return punto;
  
}
int distancia(vector<int> A, vector<int> B)
{
  int dist = 0;
  for(int i=0; i<A.size(); i++)
    dist+=pow(A[i]-B[i],2);   
  return sqrt(dist);
  
}

vector<int> size = {1000,10000,50000};

int main() 
{
  int dim =3;
  for(int e=0; e<3; e++)
  {
    int n = size[e];

    //Punto Inicial
    vector<int> punto_inicial = generar_punto(dim,n);
    
    unsigned t0, t1;
   
    t0=clock();
  
    for(int i=0; i<n; i++)
    {
      //Punto aleatorio
      vector<int> punto_aleatorio = generar_punto(dim,n);

      int dist = distancia(punto_inicial, punto_aleatorio);
    }
    
    t1 = clock();
   
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time of " << n << " :"<< time << endl;
  }

  

}