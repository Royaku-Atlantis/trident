#pragma once
#define REGION if (true)
//external library that might be useful
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

//Redefine some things
#define Array       std::vector
//wish i could change push_back() to append(), idk if its possible
#define String      std::string
#define Index       unsigned int
#define IndexNval   ~(unsigned int)0 //max value of uint, 0b111...11

// global "variable"
#define DEBUG true
//extern bool GLOBAL_ErrorTellProgrammer;

// double print as 6.900000 by default, this fix it
String double_to_trimmed_string(double value);
// concat the same string 'value' times
String string_multip(const String & str, int value);
//modulo but with floats, very useful, actually
double modulo(double numb, double div);

//concatanate chars in an int, useful for switch, and checking multiple enum:char at the same time
constexpr int AND(char c1, char c2, char c3=0, char c4=0) 
{
    //will transform (0xAA, 0xBB, 0xCC, 0xDD) into 0xDDCCBBAA
    return (int)c1 + ((int)c2<<8) + ((int)c2<<16) + ((int)c2<<24);
}

//get all the lines of a file into a list of string
void get_file(const String & filepath, Array<String> & file_text);
//from a list of string, get all strings with a newline inbetween
String to_string(const Array<String> & file_text);

// - PRINT FUNCTIONS - //
// { print functions

//print one single txt
void say(const String & text);
//say with any type after
template <class T>
void say(const String & text, const T & txt2)
{std::cout<<text<<txt2<<'\n';}

#define debug(txt,txt2) { if (DEBUG){say(textFormat(RED) + txt, txt2); std::cout << textFormat(0);}}

//{ color printing

// CONSTANTS
enum textStatus {TXT_DEFAULT, TXT_BOLD, TXT_DARKER, TXT_idk1, TXT_UNDERLINED, TXT_idk5, TXT_idk6, TXT_SETBACKGROUND, TXT_idk8, TXT_STRIKETHROUGH};
#define RED     "\033[31m"  //red     31   41
#define GREEN   "\033[32m"  //green   32   42
#define YELLOW  "\033[33m"  //yellow  33   43
#define BLUE    "\033[34m"  //blue    34   44
#define MAGENTA "\033[35m"  //magenta 35   45
#define CYAN    "\033[36m"  //cyan    36   46
#define WHITE   "\033[37m"  //white   37   47
#define BLACK   "\033[30m"  //black   30   40
#define DARK    "\033[30m"  
String textFormat(int fontcolor = 0);
String textFormat(int info1, int info2);
String textFormat(int info1, int info2, int info3);