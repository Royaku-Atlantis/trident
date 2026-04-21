#pragma once
#include "trident.hpp"

class Command
{
        CommandType cmd_type = CMD_EMPTY;
        ExpressionElement * first_exprelement = nullptr;
        ExpressionElement * last_exprelement = nullptr;

public:
        Command (CommandType cmdtype);
        Command (CommandType cmdtype, const Value & newval);
        Command (CommandType cmdtype, ExpressionElement * expression);
        void append_expression(const Value & newval);

        ExpressionElement * get_expressionstart() const;
        
        void debug_display_command();

        //return PCoffset (1 = basic increment, go to the next command) 
        Index run(Index PC) const;
};

//print arguments
void run_print(const ArgumentExecuter & arguments);

//print arguments + \n
void run_say(const ArgumentExecuter & arguments);

//set var argument
void run_set(const ArgumentExecuter & arguments);

//initialise a variable, if its not undefined, do nothing. usefule for the beggening of functions
void run_setifundef(const ArgumentExecuter & arguments);

//input
void run_input(const ArgumentExecuter & arguments);

//braces
Index run_jump(const ArgumentExecuter & arguments, Index PC);
Index run_jumpif(const ArgumentExecuter & arguments, Index PC);

//functions 
void run_call(const ArgumentExecuter & arguments);
void run_exit();
void run_return(const ArgumentExecuter & arguments);
