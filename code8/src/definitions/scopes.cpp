#include "../trident.hpp"
#include "../scopes.hpp"

//global defintion 
//Global_Variable_Acessor global_variable_acessor;

void Global_Variable_Acessor::set_scope(Scope * scope_adress)
{scope_link = scope_adress;}

Value Global_Variable_Acessor::get_variable(Index index)
{
        return scope_link->get_variable(index);
}

void Scope::set_variable(Index index, const Value & newval)
{
        //resize the size if it ask for a bigger variable
        if (Variables.size() <= index)
                Variables.resize(index);
        //intentional use of resize and not reserve
        
        //affect variable
        Variables[index] = newval;
}

Value Scope::get_variable(Index index)
{
        //resize the size if it ask for a bigger variable
        if (Variables.size() <= index)
                Variables.resize(index);
        //intentional use of resize and not reserve
        
        //affect variable
        return Variables[index];
}