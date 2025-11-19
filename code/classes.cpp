#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

#include "classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////
/* TRIDENT DYNAMIC VARIABLE CLASS */
///////////////////////////////////

Variable::Variable (){
        name = "";
}
Variable::Variable (std::string varname){
        name = varname;
        state = VAR_UNDEF;
}
bool Variable::is_name(std::string name_to_find){
        return name==name_to_find;
}

void Variable::set_string(std::string newtext){
        state = VAR_TEXT;
        text_value = newtext;
        numeric_value = 0;
}
void Variable::set_number(float newnumber){
        state = VAR_UNDEF;
        numeric_value = newnumber;
        text_value = "";
}
void Variable::number_to_string(){
        state = VAR_TEXT;
        text_value = std::to_string(numeric_value);
}
void Variable::string_to_number(){
        state = VAR_NUMBER;
}


///////////////////////////////////////////////////////////////////////////////////////////
/* Balises */
////////////

Balise::Balise (std::string createname, int put_line_index){
        name = createname;
        line_index = put_line_index;
}

