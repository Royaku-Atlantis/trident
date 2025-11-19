#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;

#define CHARA 0x00

int main() {
    char blbl = 0xF0;

    switch ((unsigned char)blbl){
        case CHARA:
            cout<<"just mt";
        break;
        case 0x01:
        break;
            cout<<"just 1";
        case 0xF0:
            cout<<"warning ig?";
        break;
        default:
            cout<<"None";
        break;
    }
    getch();
}
