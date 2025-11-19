#pragma once
//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <conio.h>
#include "basic_lib.hpp"
#include "classes.hpp"

//code ref
//will print arguments
#define COMMAND_PRINT "say"         // say ... args
//will jump the line index to a different line of code
#define COMMAND_GOTO "jump"         // jump ... args
//will jump n lines from the current line
#define SUBCOM_GOTO_RELATIVE "line" // jump <numb> line
//will jump directly at a given line, either a number, or a balise
#define SUBCOM_GOTO_ABSOLUTE "at"   // jump at <arg>
//define a line as the balise for a jump
#define COMMAND_BALISE "balise"      //  balise <name> 
//will start a comment
#define COMMAND_SETVAR "set"    //set <nomvar> || set <nomvar>
#define COMMENT_CHAR '#'

//////////////////////////////
#define NOLINE -1

extern std::ostream& say;
extern std::istream& input;
extern std::string nl;

typedef std::ifstream fileread;
typedef std::ofstream filewrite;


bool is_end_of_line(fileread & filer);

//parsing
std::string clean_command(std::string command);

void balise_add_from_command(std::string cleancommand, std::vector<Balise> & balises, int line_index);
int find_balise(std::string balisename, const std::vector<Balise> & balises);

// EXECUTIONS
void execution_say(std::stringstream & command, Scope & current_scope);

void execution_jump(std::stringstream & command, int & line_index, std::vector<Balise> baliseliste);

void execution_set(std::stringstream & command, Scope & current_scope);