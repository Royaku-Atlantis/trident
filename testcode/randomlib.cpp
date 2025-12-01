#include <iostream>
#include "randomlib.hpp"
using namespace std;

void foo::dothing(){
        cout<<"action of foo"<<endl;
}
void bar::dothing(){
        cout<<"action of... child of foo? bar!!! : ";
        cin>>val;
        cout<<" - val is "<<val<<endl;
}