#include <vector> 
#include <list>
#include <iostream>

using namespace std;

template <typename Container>

void Write(Container &ds)
{
  for(auto iter=ds.begin(); iter != ds.end() ; iter++ )
    cout<<*iter<< "\n";
}
int main()
{
  list<float> mylist;
  vector<float> myvector;
  for( int i = 0 ; i < 10 ; i++ )
  {
    mylist .push_back(i);
    myvector.push_back(i+50);
  }
  Write(mylist);
  Write(myvector);
}