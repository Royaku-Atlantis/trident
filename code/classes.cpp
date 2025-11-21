#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

#include "basic_lib.hpp"
#include "classes.hpp"


///////////////////////////////////////////////////////////////////////////////////////////
/* TRIDENT DYNAMIC VARIABLE CLASS */
///////////////////////////////////
typedef unsigned char varState;

Variable::Variable (){
        name = "";
        state = VAR_UNDEF;
        text_value = "";
        numeric_value = 0;
}
Variable::Variable (std::string varname){
        std::cout << "YEP ITS HERE THE ERROR";

        name = varname;
        state = VAR_UNDEF;
        text_value = "";
        numeric_value = 0;
}
Variable::Variable (std::string varname, std::string strValue){
        name = varname;
        state = VAR_TEXT;
        text_value = strValue;
        numeric_value = 0;
}
Variable::Variable (std::string varname, float numValue){
        name = varname;
        state = VAR_NUMBER;
        numeric_value = numValue;
        text_value = "";
}

std::string Variable::get_value_to_print(){
        switch (state){
        case VAR_NUMBER:
                return std::to_string(numeric_value);
        case VAR_TEXT:
                return text_value;
        case VAR_UNDEF:
                return "Undefined";
        default:
                throwing("Variable display found an invalid State");
                return "wArninG tHeRE iSn t rEtUrn hErE";
        }
}

bool Variable::is_name(std::string name_to_find){
        return name==name_to_find;
}
bool Variable::is_state(varState state_to_check){
        return state == state_to_check;
}
void Variable::convert_to_state(varState state_to_convert){
        if (is_state(state_to_convert))
                return;
        state = state_to_convert;
        switch (state_to_convert){
                case VAR_UNDEF:
                        text_value = "";
                        numeric_value = 0;
                case VAR_NUMBER:
                        numeric_value = stoi2(text_value,0);
                        text_value = "";
                case VAR_TEXT:
                        text_value = std::to_string(numeric_value);
                        return;
                default:
                        throwing("error convert_to_state() has state that dont exist");
                        return;
        }
}

void Variable::set_string(std::string newtext){
        state = VAR_TEXT;
        text_value = newtext;
        numeric_value = 0;
}
void Variable::set_number(float newnumber){
        state = VAR_NUMBER;
        numeric_value = newnumber;
        text_value = "";
}

////////////// /////////////////////////////////////////////////////////////////////////////
/* Balises */
////////////

Balise::Balise (std::string createname, int put_line_index){
        name = createname;
        line_index = put_line_index;
}

////////////////// /////////////////////////////////////////////////////////////////////////
/* Class SCOPE */
////////////////
//class Scope{
//public:
void Scope::set_var(const std::string & varName, const Variable & VarValue)
{
        int existing_var_index = find_var(varName);
        if (existing_var_index!=-1)
        {
                varlist[existing_var_index] = VarValue;
        }
        else{
                add_var(varName, VarValue);
        }
}
Variable Scope::get_var(const std::string & varName, varState typeAsked)
{
        int existing_var_index = find_var(varName);
        if (existing_var_index!=-1)
        {
                Variable found_var = varlist[existing_var_index];
                if (typeAsked==VAR_UNDEF)
                        return found_var;

                found_var.convert_to_state(typeAsked);
                return found_var;
        }
        else{
                return add_default_var(varName, typeAsked);
        }
}
Variable Scope::add_default_var(std::string varName, varState type){
        std::cout << "Debug push back of add_default_var ";
        switch(type){
        case VAR_UNDEF:
                std::cout << "undef ";
                varlist.push_back(Variable (varName)); //ERROR HERE
        break;
        case VAR_NUMBER:
                std::cout << "number ";
                varlist.push_back(Variable (varName, (float)0));  
        break;
        case VAR_TEXT:
                std::cout << "text ";
                varlist.push_back(Variable (varName, ""));
        break;
        default:
                throwing("Tried to create a variable, invalide typeState");
        }

        return get_var_from_index(varlist.size());
}
std::string Scope::displayVar(std::string varname)
{
        int var_index = find_var(varname);
        if (var_index==-1)
                return "Undefined";

        return get_var_from_index(var_index).get_value_to_print();
}
//private:
//std::vector<Variable> varlist;
int Scope::find_var(const std::string){
        return 0;
}
void Scope::add_var(const std::string & varName, const Variable & varToCopy){}

Variable Scope::get_var_from_index(int index){
        if (is_between(index, 0, (int)varlist.size()))
                throwing("Tried to access var outside of scope");
        return varlist[index];
}
