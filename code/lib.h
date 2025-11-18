#pragma once
//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝
#include <fstream>
#include <iostream>
#include <sstream>
#include <conio.h>

//code ref
//will print arguments
#define COMMAND_PRINT "say"         // say ... args
//will jump the line index to a different line of code
#define COMMAND_GOTO "jump"         // jump ... args
//will jump n lines from the current line
#define SUBCOM_GOTO_RELATIVE "line" // jump <numb> line
//will jump directly at a given line, either a number, or a label
#define SUBCOM_GOTO_ABSOLUTE "at"   // jump at <arg>
//define a line as the label for a jump
#define COMMAND_LABEL "label"      //  label <name> 
//will start a comment
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
class ListString{
public:
        unsigned int capacite;
        unsigned int str_numb;
        std::string * ad;

        ListString ();
        ~ListString ();
        void append(std::string e);
        std::string get_line(unsigned int indice) const;
};

//parsing
std::string clean_command(std::string command);

// EXECUTIONS
void execution_say(std::stringstream & command);

void execution_jump(std::stringstream & command, int & line_index);