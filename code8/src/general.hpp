#pragma once
#include <iostream>
#include "values.hpp"

// global "variable"
#define DEBUG true

// - PRINT FUNCTIONS - //
#pragma region "print functions"

//print one single txt
void say(const std::string & text);
//print text + value
void say(const std::string & text, const Value & val);
//say with any type after
template <class T>
void say(const std::string & text, const T & txt2)
{std::cout<<text<<txt2<<'\n';}

/*very simple print, no external weird libraryvoid print(){std::cout<<std::endl;} //to properly end the variadic
template <typename Type1, typename... Types2>
void print(Type1 arg1, Types2... args2){
	std::cout << arg1 ;
	print(args2...);
}*/
// To handle base case of below recursive
// Variadic function Template
//define print function
/*void myprint());
template <typename T, typename... Types>
void myprint(T var1, Types... var2) //variadic core
{
        std::cout << var1;
        myprint(var2...);
}
void myprint() //variadic terminator
{
        std::cout << std::endl;
}*/


#define debug(txt,txt2) { if (DEBUG){say(textFormat(RED) + txt, txt2); std::cout << textFormat(0);}}

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