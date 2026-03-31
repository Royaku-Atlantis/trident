#pragma once
#include "trident.hpp"

//trident settings



void print_error(const String & errortext); //GLOBAL_ErrorTellProgrammer

// enum OperatorType : unsigned char {OP_EMPTY, OPn_ADD, OPn_MUL, OPn_DIV, OPn_SUB, OPn_MOD, OPl_GET, OPb_AND, OPb_OR, OPb_NOT, OPb_XOR, OPb_COND};
String get_OperatorString(OperatorType c_operator);

String get_value_color(ValueType vtype); //VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT

struct Value{
        union {
                double val_numb;
                bool val_bool;
                String * val_string;
                int val_variable;
                OperatorType val_operator;
        };

        ValueType val_type;

        Value (); //VALUE_UNDEF
        Value (Value const& val);
        ~Value ();
        
        Value (double value_numb);
        Value (bool value_bool);
        Value (String value_string);
        Value (int value_variable);
        Value (OperatorType value_operator);

        //void setTo (double value_numb);
        //void setTo (bool value_bool);
        //void setTo (String value_string);
        //void setTo (int value_variable);
        //void setTo (OperatorType value_operator);

        //Value as (Value type) -> switch
        //use it in operator overloads, with a new function AnyValueHaveValueType(VALUETYPECONSTANTE, VAL1, VAL2)

        String string() const;
        double get_asnumber();
        bool get_asbool();
};

std::ostream& operator<<(std::ostream& out, Value thisval);

//Value operators overloading
Value operator +        (Value Val1, Value Val2);
Value operator -        (Value Val1, Value Val2);
Value operator /        (Value Val1, Value Val2);
Value operator *        (Value Val1, Value Val2);
Value operator %        (Value Val1, Value Val2);
Value operator or       (Value Val1, Value Val2);
Value operator and      (Value Val1, Value Val2);
Value operator xor      (Value Val1, Value Val2);
Value operator !        (Value Val1);
Value operator ==       (Value Val1, Value Val2);
Value operator !=       (Value Val1, Value Val2);
Value operator >=       (Value Val1, Value Val2);
Value operator <=       (Value Val1, Value Val2);
Value operator >        (Value Val1, Value Val2);
Value operator <        (Value Val1, Value Val2);

Value round_equal(Value Val1, Value Val2);