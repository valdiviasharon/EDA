#include <iostream>

using namespace std;

// Class CVector definition
class CVector
{
  private:
    int *m_pVect = NULL, 
        m_nCount = 0, 
        m_nMax = 0, 
        m_nDelta; 
  void Resize(); 
  public:
    CVector(int delta = 5)
    {
      m_nDelta = delta;
    }
    void Insert(int elem);

};
void CVector::Resize()
{
  int delta = 5; 
  
  int *pTemp;
  pTemp = new int[m_nMax + m_nDelta]; 
  for(int i = 0 ; i < m_nMax ; i++) 
    pTemp[i] = m_pVect[i];
  delete [] m_pVect; 
  m_pVect = pTemp; 
  
  m_nMax += m_nDelta; 
  cout<<"Se aumentó el tamaño"<<endl;
}
void CVector::Insert(int elem)
{
  if( m_nCount == m_nMax ) 
    Resize(); 
  m_pVect[m_nCount++] = elem; 
}

int main() 
{
  //Primer Vect
  CVector A;

  //Segundo Vect
  CVector B;

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
  while(cont2<7)  
  { 
    cout<<"2do vect: ";
    cin>>elem; 
    B.Insert(elem);  
    cont2++;
  }
}