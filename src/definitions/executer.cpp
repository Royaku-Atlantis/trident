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
	for (Index i=0; i < funcnames.size() ; i++)
	{
		if (func_name == funcnames[i])
			return functions[i];
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

void Executer::run()
{
	//init base
	reset();
	say(BLUE "Start Of Execution");

	while (callstack_Func.size()>0)
	{
		//init execution of function
		StepData step_data = StepData(0);

		Function * current_func = callstack_Func.back();
		Index current_func_size = current_func->get_code_size();
		Index & PC = callstack_PC.back();
		bool Call_Function = false;

		if (PC==0){
			say("start new func");
			current_func->debug_display_command();
		}
		//start execution of function
		while (PC < current_func_size and !Call_Function)
		{
			step_data = current_func->get_command(PC).run(PC);
			PC = step_data.PC_next;

			print_var_status();

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
		return global_variables[var_idx];
	
	//return default value if out of bound
	else 
		return Value();
}
void Executer::set_var_abs(Index var_idx, Value var_value)
{
	//check for variable index higher than already initialized
	if (var_idx >= global_variables.size())
	{
		global_variables.resize(var_idx+1, Value());
	}

	//set variable
	global_variables[var_idx] = var_value;
}

Index Executer::get_var_offset()
{
	return callstack_var_start.back();
}


void Executer::print_var_status()
{
	std::cout << BLUE "\n- Var Status : -";
	int Varstart_index = -1;
	for (int i=0; i<global_variables.size(); i++)
	{
		//if at start of scope, increment scope index
		if (callstack_var_start.size() < Varstart_index) {
			bool is_next_scope = (callstack_var_start[Varstart_index+1] == i);
			if (is_next_scope)
			{
				Varstart_index ++;
				//separate scopes variable by color
				std::cout<< ((Varstart_index%2)? BLUE : CYAN); 
			}
		}
		//get variable index relative
		Index local_var_index = i - callstack_var_start[Varstart_index];
		std::cout << "\n[" << i << "] -> " << local_var_index <<"v =";
		//print variable value :
		global_variables[i].describe();
	}
	//flip color one last time
	std::cout<< ((Varstart_index%2)? CYAN : BLUE); 
	std::cout << "\n------------" RESET;
}

void Executer::load_var_incoming_scope(const ArgumentExecuter & arguments)
{
	Index last_start_of_variables = global_variables.size();

	say(YELLOW "new start of variable for this scope is:", std::to_string(callstack_var_start.back()));
	//add each Values To Variables
	//start at 1, because arg 1 = func name
	for (Index i=1; i<arguments.get_valnumber(); i++)
        {		
                Value appended_value = arguments.get_val(i);
		//to add variable as the value they hold
		//but maintain reference variable, for data/result arguments
		std::cout<<YELLOW "\nadd variable with data["<<i<<"]=" << appended_value<<RESET;
                un_variable_maintain_reference(appended_value);
		std::cout<<YELLOW "\nun variable -> data="<<appended_value<<RESET;
                global_variables.push_back(appended_value);
        }
	//set new start of Variable for the incoming scope
	callstack_var_start.push_back(last_start_of_variables);
}

Executer::~Executer()
{
	//delete the function list
	for (Function* one_function : functions) delete one_function;
	functions.clear();

	//empty others lists
	funcnames.clear();
	global_variables.clear();
}

