#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

#define NOLINE -1

struct foo{
    string str = "";
    int numb = 0;

    foo (string balisename){
        str = balisename;
        numb = rand() % 50;
    }
};

ostream& operator <<(ostream& stream,const foo & balise){
    return stream << '[' << balise.str << ':' << balise.numb <<']';
}

int find_balise(string balisename,const vector<foo> & balises){
    for (int i=0; i<balises.size() ; i++){
        if (balises[i].str == balisename)
            return balises[i].numb;
    }
    return NOLINE;
}

int main() {
    
    cout << "Hello World!" << endl;

    vector<string> balisesnames = {"a","kwaku","blbl","cdef","crwasan","endif"};
    vector<foo> balises;

    for (int i= balisesnames.size()-1; 0<=i; i--){
        balises.push_back(foo (balisesnames[i]));
    }

    for (foo baliz : balises) {
        cout << baliz << "\n";
    }

    string balisename;
    do{
        cout << "search balise : ";
        cin >> balisename;
        cout << endl << find_balise(balisename, balises) << endl;
    }while (balisename!="stop");
    return 0;
}
