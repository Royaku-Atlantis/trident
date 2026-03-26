#include "../values.hpp"
#include "../general.hpp"
#include <iostream>

bool GLOBAL_ErrorTellProgrammer = true;

void print_error(const std::string & errortext)
{
        if (GLOBAL_ErrorTellProgrammer)
                std::cout << "\n\033[31m" << errortext << "\n\033[0m\n";
}

Value::Value() : val_bool(false)
{
        val_type = VALUE_UNDEF;
        #ifdef DEBUGINFO
                say("create Undef");
        #endif
}

Value::Value(const Value & val)
{
        val_type = val.val_type;
         
        #ifdef DEBUGINFO_DEEP
        say("create with copy value:'",std::to_string(val_variable) + '\'');
        #endif

        switch(val_type){
                case VALUE_NUMB:
                        val_numb = val.val_numb;
                        return;
                case VALUE_BOOL:
                        val_bool = val.val_bool;
                        return;
                case VALUE_STRING:
                        val_string = new std::string(*val.val_string);
                        return;
                case VALUE_VARIABLE:
                        val_variable = val.val_variable;
                        return;
                case VALUE_OPERATOR:
                        val_operator = val.val_operator;
                        return;
                case VALUE_UNDEF:
                default:
                        val_type = VALUE_UNDEF;
                        val_bool = false;
                        return;
        }
}

Value::~Value()
{       

        #ifdef DEBUGINFO_DEEP
        if (val_type==VALUE_STRING)
                say("destroy string with value:",*val_string);
        else
                say("destroy value");
        #endif

        if (val_type==VALUE_STRING)
                val_string->~basic_string();
}

//Constructors of each type
Value::Value (double value_numb)
{
        val_type = VALUE_NUMB;
        val_numb = value_numb;
        #ifdef DEBUGINFO
                say("create numb:",std::to_string(value_numb));
        #endif
}

Value::Value (bool value_bool)
{
        val_type = VALUE_BOOL;
        val_bool = value_bool;
        #ifdef DEBUGINFO
                say("create bool:",std::to_string(value_bool));
        #endif
}

Value::Value (std::string value_string)
{
        val_type = VALUE_STRING;
        val_string = new std::string(value_string);
        #ifdef DEBUGINFO
        say("create string:",value_string);
        #endif
}

Value::Value (Index value_variable)
{
        val_type = VALUE_VARIABLE;
        val_variable = value_variable;
        #ifdef DEBUGINFO 
        say("create varid:",std::to_string(value_variable));
        #endif
}

Value::Value (OperatorType value_operator)
{
        val_type = VALUE_OPERATOR;
        val_operator = value_operator;
        #ifdef DEBUGINFO
        say("create operator:",get_OperatorString(value_operator));
        #endif
}

//to display the Value

std::string Value::string() const
{
        //if (val_type==VALUE_OPERATOR) return "OPERATOR";
        switch(val_type)
        {
                case VALUE_NUMB:
                        return double_to_trimmed_string(val_numb);

                case VALUE_BOOL:
                        if (val_bool) 
                                return "True";
                        else    return "False";

                case VALUE_STRING:
                        return (* val_string);

                case VALUE_VARIABLE:
                        return "var:<" + std::to_string(val_variable) + '>';

                case VALUE_OPERATOR:
                        return get_OperatorString(val_operator);

                case VALUE_UNDEF:
                default:
                        return "Undefined";
        }
}

//operation overloading
Value operator + (Value Val1, Value Val2)
{
        switch(AND(Val1.val_type, Val2.val_type))
        {
                //regular addition
                case AND(VALUE_NUMB,VALUE_NUMB):
                        return Value(Val1.val_numb + Val2.val_numb);
                
                //bool and number additioning
                case AND(VALUE_NUMB,VALUE_BOOL):
                        return Value( (double)Val1.val_numb + Val2.val_bool );
                case AND(VALUE_BOOL,VALUE_NUMB):
                        return Value( Val1.val_bool + (double)Val2.val_numb );
                case AND(VALUE_BOOL,VALUE_BOOL):
                        return Value( (double)Val1.val_bool + (double)Val2.val_bool );

                //easy string case
                case AND(VALUE_STRING,VALUE_STRING):
                        return Val1.string() + Val2.string();

                default:
                        //concatanate if any of them is a string
                        if (Val2.val_type == VALUE_STRING)
                                return Val1.string() + (* Val2.val_string);
                        else if (Val1.val_type == VALUE_STRING)
                                return Val1.string() + (* Val2.val_string);
                        
                        //because variables are yet to be supported
                        if (Val1.val_type == VALUE_VARIABLE or Val2.val_type == VALUE_VARIABLE)
                                print_error("variable addition not yet supported");

                        //if all have failed, return undefined Value
                        return Value();
        }
}

Value operator - (Value Val1, Value Val2){
        switch(AND(Val1.val_type, Val2.val_type))
        {
                //regular substraction
                case AND(VALUE_NUMB,VALUE_NUMB):
                        return Value(Val1.val_numb - Val2.val_numb);
                
                //bool and number substraction
                case AND(VALUE_BOOL,VALUE_NUMB):
                        return Value( (double)Val1.val_bool - Val2.val_numb );
                case AND(VALUE_NUMB,VALUE_BOOL):
                        return Value( Val1.val_numb - (double)Val2.val_bool);
                case AND(VALUE_BOOL,VALUE_BOOL):
                        return Value( (double)Val1.val_bool - (double)Val2.val_bool );
                
                //like subtracting with a string, or something
                default:
                        //because variables are yet to be supported
                        if (Val1.val_type == VALUE_VARIABLE or Val2.val_type == VALUE_VARIABLE)
                                print_error("variable addition not yet supported");
                        return Value();
        }
}


/* CLASS ARG/EXPRESSION ELEMENT LIST */
ExpressionElement::ExpressionElement(const Value & val)
{
        value = val;
        ptr_next = nullptr;
}
ExpressionElement::~ExpressionElement()
{
        if (ptr_next!=nullptr)
        {
                delete ptr_next;
        }
}

ExpressionElement * ExpressionElement::append_expressionelement(const Value & new_value)
{
        //create the new expression element
        ExpressionElement * new_expression_element_ptr = new ExpressionElement(new_value);

        //add it to the current expression element
        if (ptr_next != nullptr)
        {
                say("ho no! this element is not the tail:", value.string());
                delete ptr_next;
        }
        ptr_next = new_expression_element_ptr;

        //return the pointer of the new tail element we just created
        return new_expression_element_ptr;
}

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

std::string ArgumentExecuter::string()
{
        std::string res = "{ ";
        for (Value arg : arguments)
        {
                std::string color_change = textFormat(get_value_color(arg.val_type));
                res += color_change + arg.string() + textFormat() + ", ";
        }            
        return res + '}';
}

std::string get_OperatorString(OperatorType c_operator)
{
        switch (c_operator)
        {
                case OP_EMPTY : return "(0)EMPTY";
                case OPn_ADD :  return "(2)ADD";
                case OPn_MUL :  return "(2)MUL";
                case OPn_DIV :  return "(2)DIV";
                case OPn_SUB :  return "(2)SUB";
                case OPn_MOD :  return "(2)MOD";
                case OPl_GET :  return "(2)GET";
                case OPb_AND :  return "(2)AND";
                case OPb_OR :   return "(2)OR";
                case OPb_NOT :  return "(1)NOT";
                case OPb_XOR :  return "(2)XOR";
                case OPb_COND : return "(3)IF_ELSE";
                default :       return "(0)INVALID";
        }
} 

int get_value_color(ValueType vtype)
{
        switch (vtype)
        {
                case VALUE_UNDEF: return RED;
                case VALUE_NUMB: return CYAN;
                case VALUE_BOOL: return BLUE;
                case VALUE_STRING: return YELLOW;
                case VALUE_VARIABLE: return GREEN;
                case VALUE_OPERATOR: return 0;
                default: return 0;
        }
}; //VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT