#include "../trident.hpp"
#include "../scopes.hpp"

Scope::Scope (Function * func_ptr)
{
        function = func_ptr;
}

Scope::Scope (Function * func_ptr, const ArgumentExecuter & arguments)
{
        function = func_ptr;
        for (size_t i=1; i < arguments.get_valnumber() ; i++)
        {
                set_variable(i-1, arguments.get_val(i));
        }
}

void Scope::run()
{
        say(GREEN "start of run() of this func");
        //set vriable acessors to the current scope
        global_variable_acessor_set_scope(this);

        Index func_size = function->get_code_size();
        std::cout<<"\n(funcize = "<<func_size<<")\n";
        
        //loop through the whole function
        Index PC=0;
        while (PC<func_size)
        {
                String funcidx = std::to_string(func_size);
                say(" - now at command ["+std::to_string(PC)+"]");
                PC = PC+1;//function->get_command(PC).run(PC);
                say(" - end of command, next index is ->"+std::to_string(PC));
        }
        say(GREEN "End of run() of this func");
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
                Variables.resize(index + 1);
        //intentional use of resize and not reserve
        
        //affect variable
        return Variables[index];
}

//global interaction with the current scope
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