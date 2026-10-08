#pragma once
//external library that might be useful


  /* ------------------------------------------- */
 /* Precompile Global Definitions and Constants */
/* ------------------------------------------- */
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <map>

//Redefine some things
#define Array	std::vector //wish i could change push_back() to append(), idk if its possible
#define String	std::string 
#define Map	std::map

#define Index       unsigned int
#define IndexNval   ~(unsigned int)0 //max value of uint, 0b111...11

// global constants
#define DEBUG true
//extern bool GLOBAL_ErrorTellProgrammer;


  /* ----------------------------- */
 /* Functions Relating To Numbers */
/* ----------------------------- */
//modulo but with floats, very useful, actually
double modulo(double numb, double div);

double random_range(double mini, double maxi);

//Input=0 -> 0 ; Input<0 -> -1; Input>0 -> 1 
template<typename T>
int sign(T input)
{
	if (input>0) return 1;
	if (input<0) return -1; 
	return 0;
}  

  /* ------------------------------------- */
 /* Function Related To String Management */
/* ------------------------------------- */
// double print as 6.900000 by default, this fix it
String double_to_trimmed_string(double value); //TODO solve bug: 0 can be displayed as -0
// concat the same string 'value' times
String string_multip(const String & str, int value);
String get_last_word(const String & str);
bool ends_with(std::string const & value, std::string const & ending);

//code from https://codemia.io/knowledge-hub/path/how_to_trim_a_stdstring
// Trim from the left (in place)
void ltrim(String & s);
// Trim from the right (in place)
void rtrim(String & s);
// Trim both ends (in place)
void trim(String & s);

//string to int, but dont crash
unsigned int stoi2(std::string text_to_convert, int default_value);

//string input -> double output, bolean Is convertible
//if the text_to_convert is convertible to a double,
//then "result" is set to the value found in text_to_convert, and the function return True
//else, the result will not be set, and the function return false
bool get_number_from_string(String text_to_convert, double & result);
bool is_string_number(String text_to_test);

  /* ----------------------------- */
 /* Functions Relating To Numbers */
/* ----------------------------- */

template<typename T>
void flip(T & a, T & b)
{
	T c = a;
	a = b;
	b = c;
}

//concatanate chars in an int, useful for switch, and checking multiple enum:char at the same time
constexpr int AND(char c1, char c2, char c3=0, char c4=0) 
{
	//will transform (0xAA, 0xBB, 0xCC, 0xDD) into 0xDDCCBBAA
	return (int)c1 + ((int)c2<<8) + ((int)c2<<16) + ((int)c2<<24);
}

//get all the lines of a file into a list of string
void get_file(const String & filepath, Array<String> & file_text);

void wait_interaction();//#include <conio.h> getch();

//from a list of string, get all strings with a newline inbetween
String to_string(const Array<String> & file_text);


// - PRINT FUNCTIONS - //
//#define str(not_text) std::to_string(not_text)
#define error(text) std::cout << std::endl << RED << text << RESET ;
#define say(text) std::cout << std::endl << text << RESET;

//error handeling and detections
void assert(bool condition, String error_message = "Unspecified error message");

// CONSTANTS
enum textStatus {TXT_DEFAULT, TXT_BOLD, TXT_DARKER, TXT_ITALIC, TXT_UNDERLINED, TXT_BLINK, TXT_BLINK2, TXT_SETBACKGROUND, TXT_INVISIBLE, TXT_STRIKETHROUGH};
#define RED     "\033[31m"  //red     31   41
#define GREEN   "\033[32m"  //green   32   42
#define YELLOW  "\033[33m"  //yellow  33   43
#define BLUE    "\033[34m"  //blue    34   44
#define MAGENTA "\033[35m"  //magenta 35   45
#define CYAN    "\033[36m"  //cyan    36   46
#define WHITE   "\033[37m"  //white   37   47
#define BLACK   "\033[30m"  //black   30   40
#define RESET   "\033[0m"  

String textFormat(int fontcolor = 0);
String textFormat(int info1, int info2);
String textFormat(int info1, int info2, int info3);

#define repeat(n) for (int iterator = 0; iterator<n ; iterator++)
#define repeat_start(start, n) for (int iterator = start; iterator<n ; iterator++)