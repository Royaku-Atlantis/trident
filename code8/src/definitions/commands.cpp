#include "../trident.hpp"
#include "../commands.hpp"

//enum CommandType : char {CMD_EMPTY, CMD_IF, CMD_ELIF, CMD_ELSE, CMD_PRINT, CMD_SET};


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

void Command::debug_display_command()
{
                                     //i hate doing that, tf you mean, double convertion??
        std::cout << "{cmdIndex:" << std::to_string((int)cmd_type);

        ExpressionElement * expr = first_exprelement;

        while (expr!=nullptr)
        {
                std::cout << ", " << expr->value ;
                expr = expr->ptr_next;
        }
        std::cout << "}\n";
}

Index Command::run() const
{
        //next command will simply be the next one
        Index PC_offset = 1;

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
                case CMD_INPUT:
                        run_input(argexec);
                        break;
                case CMD_BRACE_OPEN:
                        run_openbrace(argexec, PC_offset);
                case CMD_BRACE_CLOSE:
                        run_closebrace(argexec, PC_offset);

                        //for jumps (ifs, while...), change PC
                case CMD_EMPTY:
                default:
                        if (CMD_NUMBEROFCOMMANDS <= cmd_type)
                                error("cmd_type have invalid index of command : [" + std::to_string(cmd_type) + ']');
                        break;
        }
        
        return PC_offset;
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
                toprint += arguments.get_val(i).string();
        }
        std::cout << toprint << "\n";
}

void run_set(const ArgumentExecuter & arguments)
{
        Value var = arguments.get_val(0);
        if (var.val_type != VALUE_VARIABLE)
        {
                error("tried to set something that wasn't a variable");
                return;
        }

        Value newval = arguments.get_val(1);
        global_variable_acessor_set_variable(var.val_variable, newval);
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
                        global_variable_acessor_set_variable(varindex, Value((double)output));
                }
                //then make it string
                else
                {
                        global_variable_acessor_set_variable(varindex, Value((String)input));
                }           
        }
}

void run_openbrace(const ArgumentExecuter & arguments, Index & PC)
{
        int closebrace_pc = arguments.get_val(0).get_asnumber();
}

void run_closebrace(const ArgumentExecuter & arguments, Index & PC)
{
        int openbrace_pc = arguments.get_val(0).get_asnumber();
}

void run_if(const ArgumentExecuter & arguments, Index & PC)
{

}