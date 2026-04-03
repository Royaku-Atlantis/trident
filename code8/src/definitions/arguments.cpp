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
        #define OPERATOR(opvalue, operator) opvalue:add_val(pop_last_arg() operator pop_last_arg()); break;

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
                case OPb_NOT:
                        add_val(!pop_last_arg());
                        break;

                //comparators
                case OPERATOR(OPc_equalINF, <=);
                case OPERATOR(OPc_equalSUP, >=);
                case OPERATOR(OPc_strictINF, <);
                case OPERATOR(OPc_strictSUP, >);
                case OPERATOR(OPc_EQUAL, ==);
                case OPERATOR(OPc_UNEQUAL, !=);
                case OPc_roundEQUAL:
                        add_val(round_equal(pop_last_arg(), pop_last_arg())); 
                        break;

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
                        break;  
        
        }

        #undef OPERATOR

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
/* ----- Debug Display Functions ---- */

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