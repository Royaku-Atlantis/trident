#pragma once

//external library that might be useful
#include <iostream>
#include <string>
#include <vector>

// global "variable"
#define DEBUG true
extern bool GLOBAL_ErrorTellProgrammer;

// - PRINT FUNCTIONS - //
#pragma region "print functions"

//print one single txt
void say(const std::string & text);
//say with any type after
template <class T>
void say(const std::string & text, const T & txt2)
{std::cout<<text<<txt2<<'\n';}

#define debug(txt,txt2) { if (DEBUG){say(textFormat(RED) + txt, txt2); std::cout << textFormat(0);}}

void print_error(const std::string & errortext); //GLOBAL_ErrorTellProgrammer

#pragma endregion
#pragma region "color printing"

// CONSTANTS

enum textStatus {TXT_DEFAULT, TXT_BOLD, TXT_DARKER, TXT_idk1, TXT_UNDERLINED, TXT_idk5, TXT_idk6, TXT_SETBACKGROUND, TXT_idk8, TXT_STRIKETHROUGH};
#define RED 31  //red     31   41
#define YELLOW 33  //yellow  33   43
#define GREEN 32   //green   32   42
#define CYAN 36  //cyan    36   46
#define BLUE 34  //blue    34   44
#define MAGENTA 35  //magenta 35   45
#define WHITE 37  //white   37   47
#define BLACK 30  //black   30   40
#define DARK 30

std::string textFormat(int fontcolor = 0);
#pragma endregion

//concatanate chars in an int
constexpr int AND(char c1, char c2, char c3=0, char c4=0) 
{
    //will transform (0xAA, 0xBB, 0xCC, 0xDD) into 0xDDCCBBAA
    return (int)c1 + ((int)c2<<8) + ((int)c2<<16) + ((int)c2<<24);
}

// double print as 6.900000 by default, this fix it
std::string double_to_trimmed_string(double value);

std::string string_multip(const std::string & str, int value);