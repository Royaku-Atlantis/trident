#include "../trident.hpp"
#include "../values.hpp"

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

Value::Value (String value_string)
{
        val_type = VALUE_STRING;
        val_string = new std::string(value_string);
        #ifdef DEBUGINFO
        say("create string:",value_string);
        #endif
}

Value::Value (int value_variable)
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

//Value affectation, fix memmory bs with strings
Value& Value::operator = (const Value & new_value)
{
        if (val_type == VALUE_STRING)
        {
                delete val_string;
        }
        
        val_type = new_value.val_type;
        switch (val_type)
        {
                case VALUE_BOOL:
                        val_bool = new_value.val_bool;
                        break;
                case VALUE_NUMB:
                        val_numb = new_value.val_numb;
                        break;
                case VALUE_OPERATOR:
                        val_operator = new_value.val_operator;
                        break;
                case VALUE_STRING:
                        val_string = new String( *(new_value.val_string)); 
                        break;
                case VALUE_VARIABLE:
                        val_variable = new_value.val_variable;
                        break;
                case VALUE_UNDEF:
                default:
                        //go endefine, or do nothing, depending of "Setmode undefined ..."
                        break;
        }       
        //thanks compiler for telling it off ;)
        return *this;
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
                        return global_variable_acessor_get_variable(val_variable).string();// "var:<" + std::to_string(val_variable) + '>';

                case VALUE_OPERATOR:
                        return get_OperatorString(val_operator);

                case VALUE_UNDEF:
                default:
                        return "Undefined";
        }
}

double Value::get_asnumber()
{
        if (val_type==VALUE_BOOL) return (double) val_bool;
        if (val_type==VALUE_NUMB) return val_numb;
        if (val_type==VALUE_STRING) return val_string->size();
        if (val_type==VALUE_VARIABLE) return get_var_data().get_asnumber();
        return 0;
}
bool Value::get_asbool()
{
        if (val_type==VALUE_BOOL) return val_bool;
        if (val_type==VALUE_NUMB) return val_numb <= 0;
        if (val_type==VALUE_STRING) return 0 < val_string->size();
        //get from Variable

        return false;
}

Value Value::get_var_data()
{
        //if its not a variable, lets not fucking care
        if (val_type!=VALUE_VARIABLE) return * this;

        Value vardata = global_variable_acessor_get_variable(val_variable);

        //loop in case its a link to a variable, or something
        //if (vardata.val_type == VALUE_VARIABLE) ...

        return vardata;
}//

void un_variable(Value & val)
{
        //if the value is a variable, get its non variable value
        //if its STILL a variable, continue
        while (val.val_type == VALUE_VARIABLE)
                val = global_variable_acessor_get_variable(val.val_variable);
}

//operation overloading
Value operator + (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch(AND(Val1.val_type, Val2.val_type))
        {
                //regular addition
                case AND(VALUE_NUMB,VALUE_NUMB):
                case AND(VALUE_NUMB,VALUE_BOOL):
                case AND(VALUE_BOOL,VALUE_NUMB):
                case AND(VALUE_BOOL,VALUE_BOOL):
                        return Value((double)(Val1.get_asnumber() + Val2.get_asnumber()));

                default:
                        //concatanate if any of them is a string
                        if (Val1.val_type == VALUE_STRING or Val2.val_type == VALUE_STRING)
                                return Val1.string() + Val2.string();
                        
                        //because variables are yet to be supported
                        if (Val1.val_type == VALUE_VARIABLE or Val2.val_type == VALUE_VARIABLE)
                                print_error("variable addition not yet supported");

                        //if all have failed, return undefined Value
                        return Value();
        }
}

Value operator - (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch(AND(Val1.val_type, Val2.val_type))
        {
                //regular substraction
                case AND(VALUE_NUMB,VALUE_NUMB):
                case AND(VALUE_NUMB,VALUE_BOOL):
                case AND(VALUE_BOOL,VALUE_NUMB):
                case AND(VALUE_BOOL,VALUE_BOOL):
                        return Value((double)(Val1.get_asnumber() - Val2.get_asnumber()));
                
                //like subtracting with a string, or something
                default:
                        //because variables are yet to be supported
                        if (Val1.val_type == VALUE_VARIABLE or Val2.val_type == VALUE_VARIABLE)
                                print_error("variable addition not yet supported");

                        //undefined
                        return Value();
        }
}

Value operator / (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular division
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        if (Val2.get_asnumber() == 0)
                                return Value(); //cant have division by 0, return Undefined Value if its the case
                        return Value((double)(Val1.get_asnumber() / Val2.get_asnumber()));

                default:
                        return Value();
        }
}

Value operator * (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular multiplications
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value((double)(Val1.get_asnumber() * Val2.get_asnumber()));
                
                // multiply string : "ca" * 2 = "caca"
                case AND(VALUE_NUMB, VALUE_STRING):
                case AND(VALUE_BOOL, VALUE_STRING):
                        return string_multip(*Val2.val_string, Val1.get_asnumber());
                case AND(VALUE_STRING, VALUE_NUMB):
                case AND(VALUE_STRING, VALUE_BOOL):
                        return string_multip(*Val1.val_string, Val2.get_asnumber());

                default:
                        //undefined
                        return Value();
        }
}

Value operator % (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular multiplications
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value((double)(modulo(Val1.get_asnumber(), Val2.get_asnumber())) );

                default:
                        //undefined
                        return Value();
        }
}

Value operator or (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value((bool)(Val1.get_asbool() || Val2.get_asbool()));

                default:
                        //undefined
                        return Value();
        }
}

Value operator and (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value((bool)(Val1.get_asbool() and Val2.get_asbool()));

                default:
                        //undefined
                        return Value();
        }
}

Value operator xor (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value((bool)(Val1.get_asbool() xor Val2.get_asbool()));

                default:
                        //undefined
                        return Value();
        }
}

Value operator ! (Value Val1)
{
        un_variable(Val1);
        if (Val1.val_type == VALUE_NUMB or Val1.val_type == VALUE_BOOL)
                return Value((bool)(!Val1.get_asbool()));
        return Value();
}

Value operator == (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);

        if (Val1.val_type != Val2.val_type) return Value(false);

        switch (Val1.val_type)
        {
                case VALUE_UNDEF:
                        return true; //they both 
                case VALUE_NUMB:
                        return Val1.val_numb == Val2.val_numb ; 
                case VALUE_BOOL:
                        return Val1.val_bool == Val2.val_bool ; 
                case VALUE_STRING:
                        return (* Val1.val_string) == (* Val2.val_string); 
                case VALUE_VARIABLE:
                        //VARIABLE not yet Implemented
                case VALUE_OPERATOR:
                default :
                        return Value ();
        }
}

Value operator != (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        un_variable(Val1); un_variable(Val2);

        if (Val1.val_type != Val2.val_type) return Value(true);

        return Value( !(Val1 == Val2));
}

Value operator >= (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value(Val1.get_asbool() >= Val2.get_asbool());

                default:
                        //undefined
                        return Value();
        }
}

Value operator <= (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value(Val1.get_asbool() <= Val2.get_asbool());

                default:
                        //undefined
                        return Value();
        }
}

Value operator > (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value(Val1.get_asbool() > Val2.get_asbool());

                default:
                        //undefined
                        return Value();
        }
}

Value operator < (Value Val1, Value Val2)
{
        un_variable(Val1); un_variable(Val2);
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value(Val1.get_asbool() < Val2.get_asbool());

                default:
                        //undefined
                        return Value();
        }
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

String get_value_color(ValueType vtype)
{
        switch (vtype)
        {
                case VALUE_UNDEF: return RED;
                case VALUE_NUMB: return CYAN;
                case VALUE_BOOL: return BLUE;
                case VALUE_STRING: return YELLOW;
                case VALUE_VARIABLE: return GREEN;
                case VALUE_OPERATOR: return "\033[31mOPERATOR_";
                default: return "\033[31mERROR_INVALIDVALUETYPE_";
        }
}; //VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT

//overload to be display with cout
std::ostream& operator<<(std::ostream& out, const Value & thisval)
{
        out << get_value_color(thisval.val_type) << thisval.string() << "\033[0m" ;
        return out;
}

Value round_equal(Value Val1, Value Val2)
{
        switch (AND(Val1.val_type, Val2.val_type))
        {
                //regular logic "or"
                case AND(VALUE_NUMB, VALUE_NUMB):
                case AND(VALUE_NUMB, VALUE_BOOL):
                case AND(VALUE_BOOL, VALUE_NUMB):
                case AND(VALUE_BOOL, VALUE_BOOL):
                        return Value( (bool)( std::abs(Val1.get_asnumber()-Val2.get_asnumber()) < 1 ));

                case AND(VALUE_STRING, VALUE_STRING):
                        //test, but count maj and min as the same thing
                        //maybe a more advenced algorithm to make shit easier
                default:
                        //undefined
                        return Value();
        }
}

