#include "../trident.hpp"
#include "../executer.hpp"


/*  Array<Functions> functions;
    Array<String> funcnames;
    Array<Scope> scopes;
    Array<Value> global_variables;*/

Functions * Executer::get_function(Index func_index) const
{
	return (Functions *) &(functions[func_index]);
}

Functions * Executer::get_function(String func_string) const
{
	Index function_index = IndexNval;

	//chercher l'index
	for (Index i=0; i < funcnames.size() ; i++)
	{
		if (func_string == funcnames[i])
			return (Functions *) & functions[i];
	}
}

void Executer::add_function(const String & func_name, const Functions & new_func)
{
	if (func_name.size() != functions.size())
	{
		error("adding function to executer, func name != func size");
		throw -1;
	}
	
	funcnames.push_back(func_name);
	functions.push_back(new_func);
}

void Executer::run(const String & function_name = "main")
{

}