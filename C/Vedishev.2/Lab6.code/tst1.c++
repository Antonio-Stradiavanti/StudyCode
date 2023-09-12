#include<iostream>
#include<set>
#include<algorithm>
#include<string>
using namespace std;
int main()
{
    string A, tmp;
    A.assign(10, 'E'); tmp.assign(10, 'W');
    A+=tmp;
    while (A.size()!=2)
    {
        cout<<A<<endl;
      
        A.erase(A.begin()); 
        A.erase(A.end()-1);
    }
    cout<<"Last"<<A<<endl;
    return 0;
}