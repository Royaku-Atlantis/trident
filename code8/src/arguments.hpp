#pragma once
#include "trident.hpp"

class ArgumentExecuter
{
protected: 
        Array<Value> arguments;
        Value pop_last_arg();
        bool do_operation(OperatorType operation_type);

public:
        void add_val(const Value & newval);
        String string() const;
        Value get_val(Index index) const;
        Index get_valnumber() const;
};

void calculate_arguments(ExpressionElement * expr_element, ArgumentExecuter & argument_output);
/* procedure that takes an expression (a chained list, from the pointer of the first element)
 * the result will be outputted into the argument_output
 * the expr_element is not changed whatsoever
 *
 * exemple:
 * from the trident expressions : "1 + 5*3 "joe's age:" + round(var_age)"
 * expr_element = <5, 3, op_mul, 1, op_add, "joe's age:", var_age, op_round>
 *  | (let's say var_age store the number 24.3)
 *  V
 * argument_output <16, "joe's age:24">
 */

