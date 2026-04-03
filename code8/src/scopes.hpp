#pragma once
#include "trident.hpp"

class Scope
{
    private:
        Array<Value> Variables;
        //Index function_index
        Functions * function = nullptr;

    public:
        //create the scope from the function index/pointer
        Scope (Functions * func_ptr);

        void run();

        void set_variable(Index index, const Value & newval);
        Value get_variable(Index index);
};

extern Scope * global_variable_acessor_scope_link;
void global_variable_acessor_set_scope(Scope * new_scope_link);
Value global_variable_acessor_get_variable(Index index);
void global_variable_acessor_set_variable(Index index, const Value & newval);