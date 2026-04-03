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
                case CMD_SET:
                        run_set(argexec);
                        break;
                        //for jumps (ifs, while...), change PC
                case CMD_EMPTY:
                default:
                        break;
        }
        
        return PC_offset;
}

void run_print(const ArgumentExecuter & arguments)
{
        for (Index i=0; i<arguments.get_valnumber(); i++)
        {
                Value val_to_print = arguments.get_val(i);
                std::cout<< (val_to_print.string());
        }
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