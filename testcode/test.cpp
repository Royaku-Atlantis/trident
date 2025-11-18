#include <iostream>
using namespace std;


int main() {
    cout << "Hello, World!" << (unsigned char)138 << (unsigned char)130 << endl;
    
    for (unsigned char c = 0; c < 255; c++) {
        cout << c << " " << (int)c << endl;
    }
    int kk; cin >> kk;
    return 0;
}
