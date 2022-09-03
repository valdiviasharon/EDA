#include <string>
#include <iostream>

using namespace std;

namespace sharon
{
  string nombres = "Sharon Daniela";
  string apellidos = "Valdivia Begazo";
  int edad = 20;
}
int main()
{
  cout<<sharon::nombres<<endl;
  cout<<sharon::apellidos<<endl;
  cout<<sharon::edad;
}

