#include "../trident.hpp"
#include "../executer.hpp"

Executer * global_executer_acessor = nullptr;

/*  Array<Function> functions;
    Array<String> funcnames;
    Array<Scope> scopes;
    Array<Value> global_variables;*/

Function * Executer::get_function(String func_name) const
{
	Index function_index = IndexNval;

	//chercher l'index
	for (Index i=0; i < funcnames.size() ; i++)
	{
		if (func_name == funcnames[i])
			return functions[i];
	}
	error("function not found");
	return nullptr;
}

void Executer::add_function(const String & func_name, const String & new_func_file_path)
{
	Function newfunc (new_func_file_path);

	Function * new_function = new Function("trident_folder/main.trd");
	
	funcnames.push_back(func_name);
	functions.push_back(new_function);
}


//interactions for scopes

void Executer::_function_call_append_scope(ArgumentExecuter function_arguments) //called by command call
{
	//init
	assert(function_arguments.get_valnumber() >= 1, "Command 'call' with no function_name argument");
	assert(function_arguments.get_val(0).val_type == VALUE_STRING, "Command 'call', first arg is not a string");

	//create the new scope
	String function_name = *(function_arguments.get_val(0).val_string);
	scopes.push_back( Scope(
		get_function(function_name),	//initialise 
		function_arguments		//initialise arguments in scope
	) );

	scopes.back().run();
}

void Executer::_scope_exit() // called by command exit, procedures
{
	scopes.pop_back();

	//case main scope
	if (scopes.size() == 0)
	{
		//end of program
	}
	else //case called function scope
	{
	        global_variable_acessor_set_scope(& scopes.back());
	}
}
void Executer::_scope_return(Value)
{

}

void Executer::run()
{
	//init
	scopes.clear();
	if (funcnames.size() != functions.size()){error("incoherent size function-executer, func name != func size");throw -1;}

	//create the scope[0]
	global_executer_acessor = this;

	scopes.push_back( get_function("main") );
	scopes[0].run();
}


Executer::~Executer()
{
	//delete the function list
	for (Function* one_function : functions) delete one_function;
	functions.clear();

	//empty others lists
	funcnames.clear();
	scopes.clear();
	global_variables.clear();
}

void function_call_append_scope(ArgumentExecuter function_arguments)
{
	global_executer_acessor->_function_call_append_scope(function_arguments);
}

void scope_exit()
{
	global_executer_acessor->_scope_exit();
}
void scope_return(Value)
{}