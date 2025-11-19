#pragma once

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

typedef unsigned char varState;
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
        Variable (std::string varname, std::string strValue);
        Variable (std::string varname, float numValue);
        Variable (std::string varname, varState type);

        std::string get_value_to_print();

        bool is_name(std::string name_to_find);
        bool is_state(varState state_to_check);

        void set_string(std::string newtext);
        void set_number(float newnumber);

        void convert_to_state(varState state_to_convert);

private:
        std::string name;
        varState state = VAR_UNDEF;
        float numeric_value = 0;
        std::string text_value = "";

        void number_to_string();
        void string_to_number();
};


////////////////////////////////////////////////////////////////////////////////////////////
struct Balise{
        std::string name;
        int line_index;
        Balise (std::string, int line_index);
};

class Scope{
public:
        void set_var(const std::string & varName, const Variable & VarValue);
        Variable get_var(const std::string & varName, varState typeAsked = VAR_UNDEF);
        Variable add_default_var(std::string varName, varState type = VAR_UNDEF);
        std::string displayVar(std::string varname);
private:
        std::vector<Variable> varlist;

        int find_var(const std::string); //return the index of the var, -1 if dont exist
        void add_var(const std::string & varName, const Variable & varToCopy);
        Variable get_var_from_index(int index);
};
