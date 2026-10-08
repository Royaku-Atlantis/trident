#pragma once
#include "trident.hpp"

class Executer
{
private:
	//functions array (static after initialisation)
	Array<Function*> functions; //constant after init
	Array<String> funcnames; //constant after init

	//callstack
	Array<Index> callstack_PC;
	Array<Function*> callstack_Func;

  	//Scope array (dynamic)
	Array<Value> global_variables;
	Array<Index> callstack_var_start;

	Value return_value;

	Function * get_function(String func_name) const;
	Function * get_function(Index func_idx) const;
public:
	Executer ();
	void reset();
	//append functions and funcnames
	//will be switch to private, after the creation of constructor(folderpath)
	void add_function(const String & func_name, const String & new_func_file_path);

    	/*// interactions with scope*/
	//arg 0 is string = function call

	//quite self explenatory
	void run(int argc, char ** args);

	Value get_var(int var_idx) const;
	void set_var(int var_idx, Value var_value);
	Value get_var_abs(Index var_idx) const;
	void set_var_abs(Index var_idx, Value var_value);
	Value get_return() const;
	void set_return(Value var_value);

	Index get_var_offset();
	Value get_local_varcount();

	void print_var_status();

	void load_var_incoming_scope(const ArgumentExecuter & arguments);

	~Executer();//destructor
};

extern Executer * global_executer_acessor;

    /*-----------------------------------------------*/
   /*     ╦═╗ ═╦═ ╦      ╦═╗ ╦═╕ ╦═╗ ╦═╗ ╦═╕ ╦═╗    */
  /*   ╔╗ ╠═╣  ║  ║      ╠═╝ ╠═  ╠═╣ ║ ║ ╠═  ╠═╝   */
 /*    ╚╝ ╝ ╝  ╩  ╩═╛    ╝ ╚ ╩═╛ ╝ ╝ ╩═╝ ╩═╛ ╝ ╚  */
/*-----------------------------------------------*/

int filepath_atl_function_name_get_size(String path);
String get_function_name(String path, int file_name_size);

//Executer -> Executer with functions from the folder <folder_name>
void executer_init_functions(Executer & exe, String folder_name);