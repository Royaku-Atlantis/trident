#include "../trident.hpp"
#include "../executer.hpp"

Executer * global_executer_acessor = nullptr;

/*  Array<Function> functions;
    Array<String> funcnames;
    Array<Scope> scopes;
    Array<Value> global_variables;*/

Executer::Executer()
{	
	reset();
}
void Executer::reset()
{
	//reset variables to []
	this->global_variables.clear();
	//set variable readstack start to [variable index 0]
	this->callstack_var_start.clear();
	this->callstack_var_start.push_back(0);
	//reset PointCounter stack to [code line index 0]
	this->callstack_PC.clear();
	this->callstack_PC.push_back(0);
	//reset Scope Function stack to [* "main"]
	this->callstack_Func.clear();
	this->callstack_Func.push_back(get_function("main"));

	global_executer_acessor = this;
}

Function * Executer::get_function(String func_name) const
{
	if (func_name=="")
		return nullptr;
	
	Index function_index = IndexNval;

	//chercher l'index
	repeat (funcnames.size())
	{
		if (func_name == funcnames[iterator])
			return functions[iterator];
	}

	error("function not found");
	return nullptr;
}

Function * Executer::get_function(Index func_idx) const
{
	if (func_idx > functions.size()) return nullptr;
	return functions[func_idx];
}

void Executer::add_function(const String & func_name, const String & new_func_file_path)
{
	//Function newfunc (new_func_file_path);
	Function * new_function = new Function(new_func_file_path);
	
	funcnames.push_back(func_name);
	functions.push_back(new_function);
	//functions.back()->debug_display_command();
}

void Executer::run(int argc, char ** args)
{
	//init base
	reset();

        repeat_start(2, argc)
        {       
                Value varappend = cmd_input_to_value(args[iterator]);
                std::cout << "\nvar[" << iterator-2 << "] = " << varappend << " (from : '"<<args[iterator]<<"')";
                set_var(iterator-2, varappend);
        }

	say(BLUE "Start Of Execution");

	while (callstack_Func.size()>0)
	{
		//init execution of function
		StepData step_data = StepData(0);

		Function * current_func = callstack_Func.back();
		Index current_func_size = current_func->get_code_size();
		Index & PC = callstack_PC.back();
		bool Call_Function = false;

		//if (PC==0) current_func->debug_display_command();
		
		//start execution of function
		while (PC < current_func_size and !Call_Function)
		{
			step_data = current_func->get_command(PC).run(PC, current_func_size);
			PC = step_data.PC_next;

			//print_var_status();

			//New Scope with "Call" command
			Function * newfunc = get_function(step_data.newfunc_name);
			if (newfunc != nullptr)
			{
				callstack_PC[callstack_PC.size()-1] = PC; //PC = Index & so idk wy i need to do this??
				callstack_PC.push_back(0);
				callstack_Func.push_back(newfunc);
				Call_Function = true;
				//callstack_var_start is managed by load_var_incoming_scope()
				//load_var_incoming_scope is run by the call command
				break;
			}
		}

		//if reached end of the function
		if (!Call_Function)
		{
			callstack_PC.pop_back();
			callstack_Func.pop_back();
			global_variables.erase(
				global_variables.begin() + callstack_var_start.back(),
				global_variables.begin() + global_variables.size()
			);
			callstack_var_start.pop_back();
		}
	}
	say(BLUE "End Of Execution");
}

Value Executer::get_var(int var_idx) const
{
	var_idx = var_idx + callstack_var_start.back();

	//return the value at idx
	if (var_idx < global_variables.size())
		return global_variables[var_idx];
	
	//return default value if out of bound
	else 
		return Value();
}
void Executer::set_var(int var_idx, Value var_value)
{
	var_idx = var_idx + callstack_var_start.back();
	
	//check for variable index higher than already initialized
	if (var_idx >= global_variables.size())
	{
		global_variables.resize(var_idx+1, Value());
	}

	//set variable
	global_variables[var_idx] = var_value;
}

Value Executer::get_var_abs(Index var_idx) const
{
	//return the value at idx
	if (var_idx < global_variables.size())
	{
		return global_variables[var_idx];
	}
	//return default value if out of bound
	else 
	{	
		return Value();
	}
}
void Executer::set_var_abs(Index var_idx, Value var_value)
{
	//check for variable index higher than already initialized
	if (var_idx >= global_variables.size())
	{
		global_variables.resize(var_idx+1, Value());
	}
	
	global_variables[var_idx] = var_value;
	//set variable
}

Value Executer::get_return() const
{
	return return_value;
}
void Executer::set_return(Value var_value)
{
	return_value = var_value;
}

Index Executer::get_var_offset()
{
	return callstack_var_start.back();
}

Value Executer::get_local_varcount()
{
	return (double)(global_variables.size() - callstack_var_start.back());
}
void Executer::print_var_status()
{
	std::cout << BLUE "\n- Var Status : - [";

	for (auto i : callstack_var_start)
	{
		std::cout << "," << i;
	}
	std::cout << "] - retval=" << return_value;

	int Varstart_index = -1;
	repeat(global_variables.size())
	{
		//if at start of scope, increment scope index
		if (callstack_var_start.size() > (Varstart_index+1)){
			if (callstack_var_start[Varstart_index+1] == iterator)
			{
				Varstart_index ++;
				//separate scopes variable by color
				std::cout<< ((Varstart_index%2)? BLUE : CYAN); 
			}
		}
		//get variable index relative
		Index local_var_index = iterator - callstack_var_start[Varstart_index];
		std::cout << "\n[" << iterator << "] -> " << local_var_index <<"v =";
		//print variable value :
		global_variables[iterator].describe();
	}
	//flip color one last time
	std::cout<< ((Varstart_index%2)? CYAN : BLUE); 
	std::cout << "\n------------" RESET;
}

void Executer::load_var_incoming_scope(const ArgumentExecuter & arguments)
{

	//init var references
	//otherwise, using reference to unset variables crash
	repeat_start(1, arguments.get_valnumber())
        {		
                Value value = arguments.get_val(iterator);
		if (value.val_type==VALUE_VAREFERENCE)
		{
			Index difference = value.val_variable - global_variables.size() + 1;

			if (difference > 0)
			{
                		global_variables.resize(value.val_variable+1);
				say("added new variable in precedent scope, diff = " << difference);
			}
		}
        }

	//init variable start to prepare the incoming scope
	Index last_start_of_variables = global_variables.size();
	//say(YELLOW "new start of variable for this scope is:", std::to_string(callstack_var_start.back()));

	//add each Values To Variables
	//start at 1, because arg 1 = func name
	repeat_start(1, arguments.get_valnumber())
        {		
                Value appended_value = arguments.get_val(iterator);
		//to add variable as the value they hold
		//but maintain reference variable, for data/result arguments
                un_variable_maintain_reference(appended_value);
                global_variables.push_back(appended_value);
        }

	//set new start of Variable for the incoming scope
	callstack_var_start.push_back(last_start_of_variables);
}

Executer::~Executer()
{
	//delete the function list
	for (Function* single_function : functions) delete single_function;
	functions.clear();

	//empty others lists
	funcnames.clear();
	global_variables.clear();
}

    /*-----------------------------------------------*/
   /*     ╦═╗ ═╦═ ╦      ╦═╗ ╦═╕ ╦═╗ ╦═╗ ╦═╕ ╦═╗    */
  /*   ╔╗ ╠═╣  ║  ║      ╠═╝ ╠═  ╠═╣ ║ ║ ╠═  ╠═╝   */
 /*    ╚╝ ╝ ╝  ╩  ╩═╛    ╝ ╚ ╩═╛ ╝ ╝ ╩═╝ ╩═╛ ╝ ╚  */
/*-----------------------------------------------*/

#include <filesystem>
#define FILE_EXT_LEN 4
#define FILE_EXT ".atl"
int filepath_atl_function_name_get_size(String path)
{
        //check if it end in .atl
        if (!ends_with(path, FILE_EXT)) return -1;

        int size = 0;
        for (int i=path.size()-FILE_EXT_LEN-1; i>=0; i--)
        {
                if (path[i] == '/' or path[i] == '\\') break;
                size ++;
        }
        return size;
}
String get_function_name(String path, int file_name_size)
{
        return path.substr(
                path.size()-file_name_size-FILE_EXT_LEN,
                file_name_size);
}
#undef FILE_EXT_LEN
#undef FILE_EXT

void executer_init_functions(Executer & exe, String folder_name){
	exe.add_function("main", folder_name+"/main.atl");

        //add all functions
        //*
        for (const auto & entry : std::filesystem::directory_iterator(folder_name+"/functions")) 
        {
                String function_file_path = entry.path().string();

                int filesize = filepath_atl_function_name_get_size(function_file_path);

                if (filesize==-1)
                {
                        //cout << " -> not a func file";
                }
                else
                {
                        String funcfile_name = get_function_name(function_file_path, filesize);
                        //add this function
                        exe.add_function(funcfile_name, function_file_path);
                }
        }//
}