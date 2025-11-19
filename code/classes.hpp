#pragma once

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

///////////////////////////////////////////////////////////////////////////////////////////
/* TRIDENT DYNAMIC VARIABLE CLASS */
///////////////////////////////////
#define VAR_NUMBER 0xF0
#define VAR_TEXT 0xFF
#define VAR_UNDEF 0x00
class Variable{
public:
        Variable ();
        Variable (std::string varname);
        bool is_name(std::string name_to_find);

        void set_string(std::string newtext);
        void set_number(float newnumber);

        void number_to_string();
        void string_to_number();

private:
        std::string name;
        char state = VAR_UNDEF;
        float numeric_value = 0;
        std::string text_value = "";
};


////////////////////////////////////////////////////////////////////////////////////////////
/* Balise Liste */
/////////////////
struct Balise{
        std::string name;
        int line_index;
        Balise (std::string, int line_index);
};
