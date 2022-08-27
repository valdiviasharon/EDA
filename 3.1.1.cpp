#include <iostream>

using namespace std;

int gVect[10];
int gnCount = 0; 

void Insert(int elem)
{
  if( gnCount < 100 ) // we can only insert if there is space
    gVect[gnCount++] = elem; // Insert the element at the end
  else
    gnCount = 0;
}

int main() 
{
  int elem;
  for(int i=0; i<10; i++)
  {
    cin>>elem; 
    Insert(elem);   
  }
}