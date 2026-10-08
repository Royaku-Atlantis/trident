#include "../trident.hpp"
#include "../commands.hpp"

//enum CommandType : char {CMD_EMPTY, CMD_IF, CMD_ELIF, CMD_ELSE, CMD_PRINT, CMD_SET};

StepData::StepData(Index PCnext)
{
	PC_next = PCnext;
	newfunc_name = "";
}

StepData::StepData(Index PCnext, String NewFuncName)
{
	PC_next = PCnext;
	newfunc_name = NewFuncName;
}

Command::Command (CommandType cmdtype)
{
        cmd_type = cmdtype;
        first_exprelement = nullptr;
        last_exprelement = nullptr;
}

Command::Command (CommandType cmdtype, const Value & newval)
{
        cmd_type = cmdtype;

        first_exprelement = new ExpressionElement (newval);
        last_exprelement = first_exprelement;
}

Command::Command (CommandType cmdtype, ExpressionElement * expression)
{
        cmd_type = cmdtype;
        first_exprelement = expression;
        last_exprelement = first_exprelement->get_tail();
}

void Command::append_expression(const Value & newval)
{
        //when the command have no expression initialised yet
        if (first_exprelement==nullptr)
        {
                first_exprelement = new ExpressionElement (newval);
                last_exprelement = first_exprelement; 
        }
        else //usual case, the command already have its expression initialised
        {
                last_exprelement = last_exprelement->append_expressionelement(newval);
        }
}

ExpressionElement * Command::get_expressionstart() const
{
        return first_exprelement;
}

void Command::debug_display_command() const
{
        //i hate doing that, tf you mean, double convertion??
        std::cout << "\n{cmdIndex:" << commandtype_string(cmd_type);

        ExpressionElement * expr = first_exprelement;

        while (expr!=nullptr)
        {
                std::cout << ", " << expr->value ;
                expr = expr->ptr_next;
        }
        std::cout << "}";
}

StepData Command::run(Index PC, Index CodeSize) const
{
        Index new_PC = PC + 1;
        //next command will simply be the next one

        ArgumentExecuter argexec;
        calculate_arguments(first_exprelement, argexec);

        #define COMMAND(CMD_INDEX, run_fonction) CMD_INDEX: run_fonction(argexec); break

        switch (cmd_type)
        {
                //Basic Commands 
                case COMMAND(CMD_PRINT, run_print);
                case COMMAND(CMD_SAY, run_say);
                case COMMAND(CMD_SET, run_set);
                case COMMAND(CMD_SETIFUNDEF, run_setifundef);
                case COMMAND(CMD_UNREF, run_unref);
                case COMMAND(CMD_INPUT, run_input);

                //special command
                case CMD_CALL:
                        return run_call(argexec, new_PC); break;

                //Commands that edit the Point Counter
                case CMD_JUMP:
                        new_PC = run_jump(argexec, PC); break;
                case CMD_JUMPIF:
                        new_PC = run_jumpif(argexec, PC); break;
                case CMD_RETURN:
                        run_return(argexec);
                        new_PC = CodeSize+1; break;
                case CMD_EXIT:
                        new_PC = CodeSize+1; break;


                case CMD_EMPTY:
                default:
                        if (CMD_NUMBEROFCOMMANDS <= cmd_type)
                                error("Command index[" << (int)cmd_type << "] Does not exist")
                        else
                                error("Command[" << (int)cmd_type << "] has no action defined in Command::run()");
                        break;
        }
        return new_PC;

        #undef COMMAND
}


//Run Commands

void run_print(const ArgumentExecuter & arguments)
{
        String toprint;
        repeat(arguments.get_valnumber())
        {
                toprint += arguments.get_val(iterator).string();
        }
        std::cout << toprint ;
}

void run_say(const ArgumentExecuter & arguments)
{
        String toprint;
        repeat(arguments.get_valnumber())
        {
                toprint += arguments.get_val(iterator).string() + " ";
        }
        std::cout << "\n" << toprint;
}

void run_set(const ArgumentExecuter & arguments)
{
        //should only have 2 arguments, put a warning if (arguments!=2) ?

        Value var = arguments.get_val(0);

        if (var.val_type == VALUE_VARIABLE)
        {
                Value newval = arguments.get_val(1);
                un_variable_maintain_reference(newval);//to be sure to get the actual value

                //case var reference
                Value original_value = global_executer_acessor->get_var(var.val_variable);
                if (original_value.val_type==VALUE_VAREFERENCE)
                {
                        global_executer_acessor->set_var_abs(original_value.val_variable, newval);
                }
                //classic variables
                else
                        global_executer_acessor->set_var(var.val_variable, newval);
        }
        else
        {
                error("tried to set something that wasn't a variable");
                return;
        }
}

void run_unref(const ArgumentExecuter & arguments)
{
        Value var = arguments.get_val(0);
        Value optional_newval = arguments.get_val(1);

        if (var.val_type == VALUE_VAREFERENCE)
        {
                Value newval = arguments.get_val(1);
                un_variable(newval);//to be sure to get the actual value
                global_executer_acessor->set_var(var.val_variable, newval);
        }
}

void run_setifundef(const ArgumentExecuter & arguments)
{
        Value var = arguments.get_val(0);
        if (var.val_type != VALUE_VARIABLE)
        {
                error("tried to set something that wasn't a variable");
                return;
        }

        //check if its not undefined
        if (VALUE_UNDEF != global_executer_acessor->get_var(var.val_variable).val_type) return;

        Value newval = arguments.get_val(1);
        global_executer_acessor->set_var(var.val_variable, newval);
}

void run_input(const ArgumentExecuter & arguments)
{
        repeat(arguments.get_valnumber())
        {
                Value this_val = arguments.get_val(iterator);
         
                //check if its indeed a variable
                if (this_val.val_type != VALUE_VARIABLE)
                        continue;

                //get the var index;
                Index varindex = this_val.val_variable;
                
                //adapt to var references
                bool is_var_ref = false;
                Value stored_value = global_executer_acessor->get_var(varindex);
                if (stored_value.val_type == VALUE_VAREFERENCE)
                {
                        say("set var ref");
                        varindex = stored_value.val_variable;
                        is_var_ref = true;
                }

                //input value
                String input;
                getline(std::cin, input);
                
                //string cmd input -> Value
                stored_value = cmd_input_to_value(input);

                //set variable to inputed vakue
                if (is_var_ref)
                {
                        say("set var abs v[" << varindex << "] <- " << stored_value.string());
                        global_executer_acessor->set_var_abs(varindex, stored_value);
                }else{
                        say("set var abs v[" << varindex << "] <- " << stored_value.string());
                        global_executer_acessor->set_var(varindex, stored_value);
                }
        }
}

//return the new PC
Index run_jump(const ArgumentExecuter & arguments, Index PC)
{        
        int jump_value = arguments.get_val(0).get_asnumber();

        if (jump_value==0)
        {
                error("Jump 0 is forbidden");
                return PC + 1;
        }

        if (jump_value>0) jump_value++; //correction

        int new_PC = PC + jump_value;   

        new_PC = std::max(0, new_PC); //cut minimum at 0
        return new_PC;
}

//return the new PC
Index run_jumpif(const ArgumentExecuter & arguments, Index PC)
{         
        bool do_jump = !arguments.get_val(0).get_asbool();
        int jump_value = arguments.get_val(1).get_asnumber();

        if (jump_value==0)
        {
                error("Jump 0 is forbidden");
                return PC + 1;
        }

        if (jump_value>0) jump_value++; //correction

        int new_PC;
        if (do_jump)
                new_PC = PC + jump_value;
        else
                new_PC = PC + 1; //simply continue the code

        //cut minimum at 0
        new_PC = std::max(0, new_PC);
        return new_PC;
}

//functions 
StepData run_call(const ArgumentExecuter & arguments, Index PC)
{	
        global_executer_acessor->load_var_incoming_scope(arguments);
        return StepData(PC, arguments.get_val(0).string());
}
void run_return(const ArgumentExecuter & arguments)
{
        global_executer_acessor->set_return(arguments.get_val(0));
}
