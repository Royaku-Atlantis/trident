#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <vector>
using namespace std;

int main(){
    ifstream file;
    file.open("errortest.txt");
    string blabla1;
    char blabla2;
    float blabla3;
    file >> blabla1 >> blabla2 >> blabla3;
    cout<<"text:" <<blabla1 <<endl;
    cout<<"char:" <<blabla2 <<endl;
    cout<<"number:"<<blabla3<<endl;
    return 0;
}
