#include <iostream>

using namespace std;
template <typename Type> 
class CVector
{
  private:
    Type*m_pVect = NULL; // Pointer to the buffer
    int m_nCount = 0, // Control how many elements are actually used
        m_nMax = 0, // Control the number of allocated elements
        m_nDelta; // To control the growing
    void Resize(); // Resize the vector when occurs an overflow
  public:
    CVector(int delta = 5)
    {
      m_nDelta = delta;
    }
    void Insert(Type elem); // Insert a new element
};
template <typename Type> 
void CVector<Type>::Resize()
{
  Type *pTemp;
  pTemp = new Type[m_nMax + m_nDelta]; 
  for(int i = 0 ; i < m_nMax ; i++) 
    pTemp[i] = m_pVect[i];
  delete [] m_pVect; 
  m_pVect = pTemp; 
  
  m_nMax += m_nDelta; 
  cout<<"Se aumentó el tamaño"<<endl;
}
template <typename Type> 
void CVector<Type>::Insert(Type elem)
{
  if( m_nCount == m_nMax ) 
    Resize(); 
  m_pVect[m_nCount++] = elem; 
}
int main() 
{
  //Primer Vect
  CVector<int> A;

  //Segundo Vect
  CVector<char> B;

  int cont = 0, cont2 =0;
  int elem;
  //Primer Vect
  while(cont<10)  
  { 
    cout<<"1er vect: ";
    cin>>elem; 
    A.Insert(elem);  
    cont++;
  }
  //Segundo vect
  cout<<endl;
  char elemt;
  while(cont2<7)  
  { 
    cout<<"2do vect: ";
    cin>>elemt; 
    B.Insert(elemt);  
    cont2++;
  }
}