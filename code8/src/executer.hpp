#pragma once
#define Octet unsigned char

#include "general.hpp"
#include "values.hpp"

enum CommandType : char {CMD_EMPTY, CMD_IF, CMD_ELIF, CMD_ELSE, CMD_PRINT, CMD_SET};

class Command
{
        CommandType cmd_type = CMD_EMPTY;
        ExpressionElement * first_exprelement = nullptr;
        ExpressionElement * last_exprelement = nullptr;

public:
        Command (CommandType cmdtype, const Value & newval);
        void append_expression(const Value & newval);

        ExpressionElement * get_expressionstart() const;

        //Run ( core_or_whatever_the_name_is & );
};


/*
class function {
        Octet * code; //dont change once created
        unsigned int codesize;

        Octet * calculstack;
        //Octet * 
};*/