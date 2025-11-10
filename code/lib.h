#pragma once
//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝
#include <fstream>
#include <iostream>
#include <conio.h>

//code ref
extern std::ostream& say;
extern std::istream& input;
extern std::string nl;

typedef std::ifstream fileread;
typedef std::ofstream filewrite;

bool is_char_writable(char value);
bool is_end_of_line(fileread & filer);

char last_char(std::string text, int offset = 0);
void rm_last_char(std::string & text, int offset = 0);
