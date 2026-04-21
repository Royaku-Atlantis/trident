#include "../trident.hpp"
#include "../arguments.hpp"


/* CLASS ARGUMENT EXECUTER*/

Value ArgumentExecuter::pop_last_arg()
{
        //if there is nothing do pop, return the Undefined Value
        if (arguments.size()==0) return Value();

        Value back_value = arguments.back();

        arguments.pop_back();

        // VARIABLE --- change back_value into a pure Value if variable
        return back_value;
}

void ArgumentExecuter::add_val(const Value & newval) 
{
        bool is_an_operation = newval.val_type == VALUE_OPERATOR;//check_operation(newval);
        
        if (is_an_operation)
                do_operation(newval.val_operator);
        else
                arguments.push_back(newval);
}

bool ArgumentExecuter::do_operation(OperatorType operation_type)
{
        //case operator between values
        #define OPERATOR(opvalue, operator) opvalue:add_val(pop_last_arg() operator pop_last_arg()); break;

        //case function with two input
        #define FUNCTION(opvalue, function) opvalue:add_val(function(pop_last_arg(), pop_last_arg())); break;

        //case function (or prefix operator) with one input
        #define FUNCMONO(opvalue, funcmono) opvalue:add_val(funcmono(pop_last_arg())); break;

        //postfix action with operator switch
        switch (operation_type)
        {
                //classic number operations
                case OPERATOR(OPn_ADD, +);
                case OPERATOR(OPn_SUB, -);
                case OPERATOR(OPn_MUL, *);
                case OPERATOR(OPn_DIV, /);
                case OPERATOR(OPn_MOD, %);

                //bolean operations
                case OPERATOR(OPb_AND, and);
                case OPERATOR(OPb_OR, or);
                case OPERATOR(OPb_XOR, xor);
                case FUNCMONO(OPb_NOT, !);

                //comparators
                case OPERATOR(OPc_equalINF, <=);
                case OPERATOR(OPc_equalSUP, >=);
                case OPERATOR(OPc_strictINF, <);
                case OPERATOR(OPc_strictSUP, >);
                case OPERATOR(OPc_EQUAL, ==);
                case OPERATOR(OPc_UNEQUAL, !=);
                case FUNCTION(OPc_roundEQUAL, round_equal);
                
                //trigo function
                case FUNCMONO(OPn_COS, value_cos);

                //functions-operators
                case FUNCTION(OPn_RAND,value_random_range);
                
                //special
                case OPb_COND :
                        add_val(
                                pop_last_arg().get_asbool() ?
                                pop_last_arg() : 
                                pop_last_arg()
                        );
                        break;
                case OPl_GET :
                        //for lists, does nothing yet
                case OP_EMPTY :
                default:
                        //return false;//i guess ?, 
                        //like, there was only one return in the whole func lmao 
                        break;  
        
        }

        #undef OPERATOR
        #undef FUNCTION
        #undef FUNCMONO

        //return the fact that it was an operation
        return true;
}

void calculate_arguments(ExpressionElement * expr_element, ArgumentExecuter & argument_output)
{
        // loop trhough all the expression, 
        // the expression is a chained list of expr_elements 
        while (expr_element != nullptr)
        {
                argument_output.add_val(expr_element->value);

                expr_element = expr_element->ptr_next;
        }
}

 /* ---------------------------------- */
/* ----- Debug Display Function ---- */

String ArgumentExecuter::string() const
{
        String res = "{ ";
        bool firstelem = true;
        for (Value arg : arguments)
        {
                if (!firstelem) res += ", "; 
                else            firstelem=false; //to have only "," in between parenthesis

                String color_change = get_value_color(arg.val_type);
                res += color_change + arg.string() + textFormat();
        }            
        return res + "}\n";
}


Value ArgumentExecuter::get_val(Index index) const
{
        if (arguments.size() <= index) return Value();
        else return arguments[index];
}
Index ArgumentExecuter::get_valnumber() const
{
        return arguments.size();
}