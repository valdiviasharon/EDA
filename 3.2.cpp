#include <iostream>

using namespace std;

void Resize(int *& rpVect, int& rnMax)
{
  int delta = 5; 
  
  int *pTemp;
  pTemp = new int[rnMax + delta]; 
  for(int i = 0 ; i < rnMax ; i++) 
    pTemp[i] = rpVect[i];
  delete [] rpVect; 
  rpVect = pTemp; 
  
  rnMax += delta; 
  cout<<"Se aumentó el tamaño"<<endl;
}
void Insert(int *& rpVect, int& rnCount, int& rnMax, int elem)
{
  if( rnCount == rnMax ) 
    Resize(rpVect, rnMax); 
  rpVect[rnCount] = elem; 
  rnCount++;
}

int main() 
{
  //Primer Vect
  int gnCount = 0; 
  int *gpVect = NULL;
  int gnMax = 0;

  //Segundo Vect
  int gnCount2 = 0; 
  int *gpVect2 = NULL;
  int gnMax2 = 0;
  
  int elem;
  //Primer Vect
  while(gnCount<20)  
  { 
    cout<<"1er vect: ";
    cin>>elem; 
    Insert(gpVect, gnCount, gnMax, elem);  
  }
  //Segundo vect
  cout<<endl;
  while(gnCount2<11)  
  { 
    cout<<"2do vect: ";
    cin>>elem; 
    Insert(gpVect2, gnCount2, gnMax2, elem);  
  }
}