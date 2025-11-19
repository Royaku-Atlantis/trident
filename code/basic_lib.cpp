#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

bool is_char_writable(char value){
        return 33<value and value<126;
}

std::string trim(const std::string& line);

unsigned int stoi2(std::string text_to_convert, int default_value);

void throwing(std::string errortext){
        std::cout<<"ERROR-"<<errortext;
        int blbl; std::cin >> blbl;
        throw 2;
}