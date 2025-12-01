#include <iostream>
#include <vector>
#include "randomlib.hpp"
using namespace std;

int main(){
    vector<foo *> list;
    bar test;
    test.dothing();

    list.reserve(2);
    list.push_back(new foo ());
    list.push_back(new bar ());
    list.push_back(new bar ());

    for (foo* i : list){
        i->dothing();
    }
}
