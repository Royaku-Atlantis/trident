#pragma once
#include "trident.hpp"

class Scope
{
    private:
        Array<Value> Variables;
        int function_index; 

    public:
        void set_variable(Index index, const Value & newval);
        Value get_variable(Index index);
};

class Global_Variable_Acessor
{
    private:
        Scope * scope_link = nullptr;
    public:
        void set_scope(Scope * scope_adress);

        Value get_variable(Index index);

};
//global variable
extern Global_Variable_Acessor global_variable_acessor;