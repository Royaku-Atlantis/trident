#pragma once
#include "trident.cpp"



class Functions
{
private:        
        Array<Command> code; //dont change once created
        int code_size;
        int number_of_variables;

public:
        int get_number_of_variable();
        int get_code_size();
        //methodes for the scope to navigate between brackets
};