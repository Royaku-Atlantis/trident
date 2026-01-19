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

unsigned int stoi2(std::string text_to_convert, int default_value){
        try{
                return stoi(text_to_convert);
        }
        catch(...){
                return default_value;
        }
}

bool start_with(const string& strbase, const string& substr){
        return strbase.find(substr) == 0;
}
bool end_with(const string& strbase, const string& substr){
        return strbase.find(substr) == (strbase.length()-substr.length());
}

int get_operator_index(char op,int context){
        switch (op){

                default:
        }
}