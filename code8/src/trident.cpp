#include "trident.hpp"
#include "general.hpp"
#include <iostream>
#include <memory>

Value::Value() : val_bool(false)
{
        val_type = VALUE_UNDEF;
        #ifdef TRIDENT_DEBUGINFO
                say("create Undef");
        #endif
}

Value::Value(Value const& val)
{
        val_type = val.val_type;
         
        #ifdef TRIDENT_DEBUGINFO_DEEP
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
                        val_string = val.val_string;
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
        if (val_type==VALUE_STRING) 
                val_string->~basic_string();

        #ifdef TRIDENT_DEBUGINFO_DEEP
                say("destroy value");
        #endif
}

//Constructors of each type
Value::Value (double value_numb)
{
        val_type = VALUE_NUMB;
        val_numb = value_numb;
        #ifdef TRIDENT_DEBUGINFO_DEEP
                say("create numb:",std::to_string(value_numb));
        #endif
}

Value::Value (bool value_bool)
{
        val_type = VALUE_BOOL;
        val_bool = value_bool;
        #ifdef TRIDENT_DEBUGINFO
                say("create bool:",std::to_string(value_bool));
        #endif
}

Value::Value (std::string value_string)
{
        val_type = VALUE_STRING;
        val_string = new std::string(value_string);
        #ifdef TRIDENT_DEBUGINFO
        say("create string:",value_string);
        #endif
}

Value::Value (Index value_variable)
{
        val_type = VALUE_VARIABLE;
        val_variable = value_variable;
        #ifdef TRIDENT_DEBUGINFO 
        say("create varid:",std::to_string(value_variable));
        #endif
}

Value::Value (OperatorType value_operator)
{
        val_type = VALUE_OPERATOR;
        val_operator = value_operator;
        #ifdef TRIDENT_DEBUGINFO
        say("create operator:",std::to_string(value_operator));
        #endif
}

//to display the Value
std::string Value::string()
{
        switch(val_type)
        {
                case VALUE_NUMB:
                        return std::to_string(val_numb);

                case VALUE_BOOL:
                        if (val_bool) 
                                return "True";
                        else    return "False";

                case VALUE_STRING:
                        return * val_string;

                case VALUE_VARIABLE:
                        return "var:<" + std::to_string(val_variable) + '>';

                case VALUE_OPERATOR:
                        return "op:'" + val_operator + '\'';

                case VALUE_UNDEF:
                default:
                        return "Undefined";
        }
}

std::string ArgumentList::string()
{
        std::string res = "{ ";

        for (Value arg : arguments)
        {
                res += arg.string() + ", ";                
        }

        res += (char)8 + (char)8 + "}----";

        return res;
}


