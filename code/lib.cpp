#include "lib.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <conio.h>

//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝

std::ostream& say = std::cout;
std::istream& input = std::cin;
std::string nl = "\n";

typedef std::ifstream fileread;
typedef std::ofstream filewrite;

bool is_char_writable(char value){
        return 33<value and value<126;
}
bool is_end_of_line(fileread & filer) //detect end of file
{
        char C, D;
        do {
                filer.get(C);
                D = filer.peek();
        }
        while (!filer.eof() and C!='\n' and !is_char_writable(D));

        if (C=='\n'){
                say << "\n -- Endl -- \n";
                return true;
        }
        return false;
}

char last_char(std::string text, int offset){
        return text[text.length()-1 + offset];
}
void rm_last_char(std::string & text, int offset){
        text[text.length()-1 + offset] = '\0';
}
