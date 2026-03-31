#pragma once
#include "trident.hpp"

class Command
{
        CommandType cmd_type = CMD_EMPTY;
        ExpressionElement * first_exprelement = nullptr;
        ExpressionElement * last_exprelement = nullptr;

public:
        Command (CommandType cmdtype, const Value & newval);
        void append_expression(const Value & newval);

        ExpressionElement * get_expressionstart() const;
};