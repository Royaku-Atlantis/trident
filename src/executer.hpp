#pragma once
#include "trident.hpp"


class Executer
{
private:
    //functions array (static after initialisation)
    Array<Functions> functions;
    Array<String> funcnames;

    Functions * get_function(String func_string) const;
    Functions * get_function(Index func_index) const;

    //Scope array (dynamic)
    Array<Scope> scopes;
    Array<Value> global_variables;
public:
    //append functions and funcnames
    void add_function(const String & func_name, const Functions & new_func);

    //run the functions, starting from the "main" function
    void run(const String & function_name = "main");
};
