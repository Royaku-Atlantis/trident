#ifndef TRIDENT_LIB_BASIC
#define TRIDENT_LIB_BASIC

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝
/*-----------Basic number handling-------------*/
/* ╦═╗ ╦═╗ ╔═╗ ╦═╗ ╦═╗ ╦═╗  */
/* ╠═╣ ╠═╣ ║   ║ ║ ╠═  ╠═   */
/* ╝ ╝ ╩═╝ ╚═╝ ╩═╝ ╩═╝ ╝    */

//typedefs for many states for many elements
typedef unsigned char BYTE;
typedef unsigned int INDEX;


template <typename T>
bool is_between(T value, T mini,T maxi){
        return mini<=value and value<=maxi;
}

///////// char and string handeling
bool is_char_writable(char value){
        return is_between(value, (char)33, (char)126);
}

//lowercase + 32 = highercase
bool is_char_uppercase(char char_to_test){
        return is_between(char_to_test, 'A', 'Z');
}
bool is_char_lowercase(char char_to_test){
        return is_between(char_to_test, 'a', 'z');
}
bool same_char(char charA, char charB, bool upperlowercase){
        bool samechar = charA == charB; 

        if (!samechar and upperlowercase){
                if (is_char_lowercase(charA)){
                        return (charA+32) == charB;
                }else{
                        return charA == (charB+32);
                }
        }
        return charA == charB;
}

bool same_string(std::string strA, std::string strB, bool upperlowercase)
{
        int sizeA = strA.size(); 
        if (sizeA != strB.size())
                return false;

        if (!upperlowercase)
                return strA == strB;
        for (int i=0; i<sizeA ;i++){
                if (!same_char(strA[i], strB[i], upperlowercase)){
                        return false;
                }
        }
        return true;
}

bool is_char_acceptable_in_variable_names(char letter){
        return letter=='-' or letter=='_' or is_between(letter,'0','9') or is_char_uppercase(letter) or is_char_lowercase(letter);
}

std::string trim(const std::string& line);

unsigned int stoi2(std::string text_to_convert, int default_value);

std::string read_string_from(std::string source, INDEX & reader)
{        
        if (source.size()<=reader) return "";

        std::string returnstring;
        char readingchar = source[reader];

        if (!is_char_acceptable_in_variable_names(readingchar)){
                reader++;
                returnstring = " -[" + readingchar ;
                return returnstring + "]- ";
        }

        do{
                returnstring += readingchar;
                reader++;
                readingchar = source[reader];
        }while (is_char_acceptable_in_variable_names(readingchar));

        return " -[" + returnstring + "]- ";
}

///// system things

void throwing(std::string errortext){
        std::cout<<"ERROR-"<<errortext;
        int blbl; std::cin >> blbl;
        throw 2;
}

#endif