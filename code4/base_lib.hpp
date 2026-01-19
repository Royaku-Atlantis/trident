#pragma once
#include <iostream>
using namespace std;

bool string_found(int str_pos);

string trim(const string& line);

unsigned int stoi2(std::string text_to_convert, int default_value);

bool start_with(const string& strbase, const string& substr);
bool end_with(const string& strbase, const string& substr);

int get_operator_index(char op);