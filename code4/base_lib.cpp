#include "base_lib.hpp"
#include <iostream>
using namespace std;

bool string_found(int str_pos)
{
    return str_pos != string::npos;
}

string trim(const string& line)
{
    const char* WhiteSpace = " \t\v\r\n";
    size_t start = line.find_first_not_of(WhiteSpace);
    size_t end = line.find_last_not_of(WhiteSpace);
    return (start == end) ? string() : line.substr(start, end - start + 1);
}