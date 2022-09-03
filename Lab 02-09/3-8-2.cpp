#include <vector> 
#include <list>
#include <iostream>

using namespace std;
float Addition(float a, float b)
{
  return a + b;
}
float Subtraction(float a, float b)
{
  return a - b;
}
float Multiplication(float a, float b)
{
  return a * b;
}
float Division(float a, float b)
{
  return a / b;
}
int main()
{
  typedef float (*lpfnOperation)(float, float);
  lpfnOperation vpf[4] = {&::Addition, &::Subtraction, &::Multiplication, &::Division};
  float a, b, c; int opt;
  
  cin >> a >> b;
  cin >> opt;
  while(opt == 3 && b==0)
  {
    cout<<"Valor inválido, vuelva a ingresar b: "; cin>>b;
  }
  c = (*vpf[opt])(a, b);

  cout<<c;
}
