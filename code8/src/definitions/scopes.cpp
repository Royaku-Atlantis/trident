#include "../trident.hpp"
#include "../scopes.hpp"

//global defintion 
//Global_Variable_Acessor global_variable_acessor;

Scope * global_variable_acessor_scope_link = nullptr;
void global_variable_acessor_set_scope(Scope * new_scope_link)
{
        global_variable_acessor_scope_link = new_scope_link;
}
Value global_variable_acessor_get_variable(Index index)
{
        if (global_variable_acessor_scope_link==nullptr)
        {
                error("Tried to GET a variable, but the global_variable_acessor_scope_link is set to nullptr");
                return Value();//undefined
        }
        return global_variable_acessor_scope_link->get_variable(index);
}
void global_variable_acessor_set_variable(Index index, const Value & newval)
{
        if (global_variable_acessor_scope_link==nullptr)
        {
                error("Tried to SET a variable, but the global_variable_acessor_scope_link is set to nullptr");
                return;
        }
        global_variable_acessor_scope_link->set_variable(index, newval);
}


void Scope::set_variable(Index index, const Value & newval)
{
        //resize the size if it ask for a bigger variable
        if (Variables.size() <= index)
                Variables.resize(index +1);
        //intentional use of resize and not reserve
        
        //affect variable
        Variables[index] = newval;
}

Value Scope::get_variable(Index index)
{
        //resize the size if it ask for a bigger variable
        if (Variables.size() <= index)
                Variables.resize(index +1);
        //intentional use of resize and not reserve
        
        //affect variable
        return Variables[index];
}