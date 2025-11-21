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
        return is_between(char_to_test, (char)65, (char)90);
}
bool is_char_lowercase(char char_to_test){
        return is_between(char_to_test, (char)97, (char)122);
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

std::string trim(const std::string& line);

unsigned int stoi2(std::string text_to_convert, int default_value);



///// system things

void throwing(std::string errortext){
        std::cout<<"ERROR-"<<errortext;
        int blbl; std::cin >> blbl;
        throw 2;
}

#endif