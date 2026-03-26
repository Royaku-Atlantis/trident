#include "../general.hpp"
#include "../values.hpp"
#include "../executer.hpp"
#include "stdarg.h"

//enum CommandType : char {CMD_EMPTY, CMD_IF, CMD_ELIF, CMD_ELSE, CMD_PRINT, CMD_SET};

Command::Command (CommandType cmdtype, const Value & newval)
{
        cmd_type = cmdtype;

        first_exprelement = new ExpressionElement (newval);
        last_exprelement = first_exprelement;
}

void Command::append_expression(const Value & newval)
{
        last_exprelement = last_exprelement->append_expressionelement(newval);
}
ExpressionElement * Command::get_expressionstart() const
{
        return first_exprelement;
}

/*
class function {
        Octet * code; //dont change once created
        unsigned int codesize;

        Octet * calculstack;
        //Octet * 
};*/