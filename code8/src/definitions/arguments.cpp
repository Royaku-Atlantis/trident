#include "../trident.hpp"
#include "../arguments.hpp"


/* CLASS ARGUMENT EXECUTER*/

Value ArgumentExecuter::pop_last_arg()
{
        //if there is nothing do pop, return the Undefined Value
        if (arguments.size()==0) return Value();

        Value back_value = arguments.back();

        arguments.pop_back();
        #ifdef DEBUGINFO
        say("Popped tail value = ",back_value.string());
        #endif
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
        switch (operation_type)
        {
                //classic number operations
                case OPn_ADD :
                        add_val(pop_last_arg() + pop_last_arg());
                        break;

                case OPn_SUB :
                        add_val(pop_last_arg() - pop_last_arg());
                        break;

                case OPn_MUL :  
                case OPn_DIV :

                case OPn_MOD : 

                //bolean operations
                case OPb_AND :    
                case OPb_OR :     
                case OPb_NOT :    
                case OPb_XOR : 

                //comparaters

                //special
                case OPb_COND :

                case OPl_GET :  
                case OP_EMPTY :
                default:
                        break;  
        }
        //return the fact that it was an operation
        return true;
}

void calculate_arguments(ExpressionElement * expr_element, ArgumentExecuter & argument_output)
{
        // loop trhough all the expression, 
        // the expression is a chained list of expr_elements 
        while (expr_element != nullptr)
        {
                say(" add val with element ",expr_element->value);
                argument_output.add_val(expr_element->value);

                expr_element = expr_element->ptr_next;
        }
}


 /* ---------------------------------- */
/* ----- Debug Display Functions ---- */

std::string ArgumentExecuter::string() const
{
        std::string res = "{ ";
        bool firstelem = true;
        for (Value arg : arguments)
        {
                if (!firstelem) res += ", "; else firstelem=false; //to have only "," in between parenthesis

                std::string color_change = textFormat(get_value_color(arg.val_type));
                res += color_change + arg.string() + textFormat();
        }            
        return res + "}\n";
}