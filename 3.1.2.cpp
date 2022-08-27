#include <iostream>

using namespace std;

//int gVect[10];
int gnCount = 0; 
int *gpVect = NULL;
int gnMax = 0;

// memory
void Resize()
{
  int delta = 5; 
  
  int *pTemp;
  pTemp = new int[gnMax + delta]; 
  for(int i = 0 ; i < gnMax ; i++) 
    pTemp[i] = gpVect[i];
  delete [] gpVect; 
  gpVect = pTemp; 
  
  gnMax += delta; 
  cout<<"Se aumentó el tamaño"<<endl;
}
void Insert(int elem)
{
  if( gnCount == gnMax ) 
    Resize(); 
  gpVect[gnCount] = elem; 
  gnCount++;
}

int main() 
{
  int elem;
 
  while(gnCount>=0)  
  { 
    cout<<"I: ";
    cin>>elem; 
    Insert(elem); 
  }
}