#pragma once
#include "trident.hpp"

/* CLASS ARG ELEMENT LIST */
struct ExpressionElement
{
        Value value;
        ExpressionElement * ptr_next = nullptr;

        ExpressionElement(const Value & val);
        //delete recurcively the rest of the expression, from this
        ~ ExpressionElement();

        ExpressionElement * append_expressionelement(const Value & new_value);
        ExpressionElement * get_tail();
};