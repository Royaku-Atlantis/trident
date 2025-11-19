#pragma once

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

bool is_char_writable(char value);

template <typename T>
bool is_between(T value, T mini,T maxi){
        return value<maxi and mini<=value;
}

std::string trim(const std::string& line);

unsigned int stoi2(std::string text_to_convert, int default_value);

void throwing(std::string errortext);