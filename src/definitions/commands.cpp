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
	PC_next = PC_next;
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
        std::cout << "\n{cmdIndex:" << std::to_string((int)cmd_type);

        ExpressionElement * expr = first_exprelement;

        while (expr!=nullptr)
        {
                std::cout << ", " << expr->value ;
                expr = expr->ptr_next;
        }
        std::cout << "}";
}

StepData Command::run(Index PC) const
{
        Index new_PC = PC + 1;
        //next command will simply be the next one

        ArgumentExecuter argexec;
        calculate_arguments(first_exprelement, argexec);

        switch (cmd_type)
        {
                case CMD_PRINT:
                        run_print(argexec);
                        break;
                case CMD_SAY:
                        run_say(argexec);
                        break;
                case CMD_SET:
                        run_set(argexec);
                        break;
                case CMD_SETIFUNDEF:
                        run_setifundef(argexec);
                        break;
                case CMD_INPUT:
                        run_input(argexec);
                        break;
                case CMD_JUMP:
                        new_PC = run_jump(argexec, PC);
                        break;
                case CMD_JUMPIF:
                        new_PC = run_jumpif(argexec, PC);
                        break;
                case CMD_CALL:
                        return run_call(argexec, PC);
                        break;
                case CMD_EXIT:
                        run_exit();
                        break;
                case CMD_EMPTY:
                default:
                        if (CMD_NUMBEROFCOMMANDS <= cmd_type)
                                error("cmd_type have invalid index of command : [" + std::to_string(cmd_type) + ']');
                        break;
        }
        return new_PC;
}


//Run Commands

void run_print(const ArgumentExecuter & arguments)
{
        String toprint;
        for (Index i=0; i<arguments.get_valnumber(); i++)
        {
                toprint += arguments.get_val(i).string();
        }
        std::cout << toprint ;
}

void run_say(const ArgumentExecuter & arguments)
{
        String toprint;
        for (Index i=0; i<arguments.get_valnumber(); i++)
        {
                toprint += arguments.get_val(i).string() + " ";
        }
        std::cout << "\n" << toprint;
}

void run_set(const ArgumentExecuter & arguments)
{
        //should only have 2 arguments, put a warning if (arguments!=2) ?

        Value var = arguments.get_val(0);
        if (var.val_type != VALUE_VARIABLE)
        {
                error("tried to set something that wasn't a variable");
                return;
        }

        Value newval = arguments.get_val(1);
        un_variable(newval);//to be sure to get the actual value
        global_executer_acessor->set_var(var.val_variable, newval);
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
        for (Index i=0; i<arguments.get_valnumber(); i++)
        {
                Value this_val = arguments.get_val(i);
         
                //check if its indeed a variable
                if (this_val.val_type != VALUE_VARIABLE)
                        continue;

                //get the var index;
                Index varindex = this_val.val_variable;
                
                //input value
                String input;
                getline(std::cin, input);
                
                //can it be a number?
                double output;
	        if (get_number_from_string(input, output))
                {
                        global_executer_acessor->set_var(varindex, Value((double)output));
                }
                //can it be a bool?
                else if (input=="True" or input=="true" or input=="TRUE")
                {
                        global_executer_acessor->set_var(varindex, Value(true));
                }
                else if (input=="False" or input=="false" or input=="FALSE")
                {
                        global_executer_acessor->set_var(varindex, Value(false));
                }
                //then make it string
                else
                {       
                        global_executer_acessor->set_var(varindex, Value((String)input));
                }      
        }
}

//return the new PC
Index run_jump(const ArgumentExecuter & arguments, Index PC)
{       
        int new_PC = PC + arguments.get_val(0).get_asnumber() + 1;
        new_PC = std::max(0, new_PC); //cut minimum at 0
        return new_PC;
}

//return the new PC
Index run_jumpif(const ArgumentExecuter & arguments, Index PC)
{         
        bool do_jump = !arguments.get_val(0).get_asbool();
        
        int new_PC;
        if (do_jump)
                new_PC = PC + arguments.get_val(1).get_asnumber() + 1;
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
void run_exit()
{
        //scope_exit();
	//std::cout<<"\n(in run_exit())";
}
void run_return(const ArgumentExecuter & arguments)
{}
