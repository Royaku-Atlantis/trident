#pragma once
#include "trident.hpp"


class Executer
{
private:
	//functions array (static after initialisation)
	Array<Function*> functions;
	Array<String> funcnames;

	Function * get_function(String func_name) const;

  	//Scope array (dynamic)
	Array<Scope> scopes;
	Array<Value> global_variables;
public:
	//append functions and funcnames
	//will be switch to private, after the creation of constructor(folderpath)
	void add_function(const String & func_name, const String & new_func_file_path);

    	/*// interactions with scope*/
					//arg 0 is string = function call
        void _function_call_append_scope(ArgumentExecuter function_arguments); //called by command call
        void _scope_exit(); // called by command exit, procedures
        void _scope_return(Value); // called by command return <value>, functions  

	//quite self explenatory
	void run();

	~Executer();//destructor
};

extern Executer * global_executer_acessor;
void function_call_append_scope(ArgumentExecuter function_arguments);
void scope_exit();
void scope_return(Value);
