#pragma once
#include <string>
#include <vector>

//trident settings

extern bool GLOBAL_ErrorTellProgrammer;

//#define DEBUGINFO
//#define DEBUGINFO_DEEP

void print_error(const std::string & errortext); //GLOBAL_ErrorTellProgrammer

//constants & enums
enum ValueType : unsigned char {VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT};
enum OperatorType : unsigned char {OP_EMPTY, OPn_ADD, OPn_MUL, OPn_DIV, OPn_SUB, OPn_MOD, OPl_GET, OPb_AND, OPb_OR, OPb_NOT, OPb_XOR, OPb_COND};
#define Index int 


// enum OperatorType : unsigned char {OP_EMPTY, OPn_ADD, OPn_MUL, OPn_DIV, OPn_SUB, OPn_MOD, OPl_GET, OPb_AND, OPb_OR, OPb_NOT, OPb_XOR, OPb_COND};
std::string get_OperatorString(OperatorType c_operator);

int get_value_color(ValueType vtype); //VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT

struct Value{
        union {
                double val_numb;
                bool val_bool;
                std::string * val_string;
                Index val_variable;
                OperatorType val_operator;
        };

        ValueType val_type;

        Value (); //VALUE_UNDEF
        Value (Value const& val);
        ~Value ();
        
        Value (double value_numb);
        Value (bool value_bool);
        Value (std::string value_string);
        Value (Index value_variable);
        Value (OperatorType value_operator);

        //void setTo (double value_numb);
        //void setTo (bool value_bool);
        //void setTo (std::string value_string);
        //void setTo (Index value_variable);
        //void setTo (OperatorType value_operator);

        //Value as (Value type) -> switch
        //use it in operator overloads, with a new function AnyValueHaveValueType(VALUETYPECONSTANTE, VAL1, VAL2)

        std::string string();
};

//Value operators overloading
Value operator + (Value Val1, Value Val2);
Value operator - (Value Val1, Value Val2);

class ArgumentList{
protected: 
        std::vector<Value> arguments;

        Value pop_last_arg();
        Value get_arg_from_tail(int location);
        bool do_operation(OperatorType operation_type);
public:

        void add_val(const Value & newval);

        std::string string();
};

enum CommandType : char {CMD_EMPTY, CMD_PRINT, CMD_SET};

class Command{};
