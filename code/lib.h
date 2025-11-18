#pragma once
//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝
#include <fstream>
#include <iostream>
#include <sstream>
#include <conio.h>

//code ref
#define COMMAND_PRINT "say"         // say ... args
#define COMMAND_GOTO "jump"         // jump ... args
#define SUBCOM_GOTO_ABSOLUTE "at"   // jump at <arg>
#define SUBCOM_GOTO_RELATIVE "line" // jump <numb> line
#define COMMENT_CHAR '#'


extern std::ostream& say;
extern std::istream& input;
extern std::string nl;

typedef std::ifstream fileread;
typedef std::ofstream filewrite;


extern std::ostream& say;
extern std::istream& input;
extern std::string nl;

typedef std::ifstream fileread;
typedef std::ofstream filewrite;

bool is_char_writable(char value);
bool is_end_of_line(fileread & filer);

std::string trim(const std::string& line);

// CLASS
class CodeList{
public:
        unsigned int capacite;
        unsigned int str_numb;
        std::string * ad;

        CodeList ();
        ~CodeList ();
        void append(std::string e);
        std::string get_line(unsigned int indice) const;
};

//parsing
std::string clean_command(std::string command);

// EXECUTIONS
void execution_say(std::stringstream & command);

void execution_jump(std::stringstream & command, int & line_index);