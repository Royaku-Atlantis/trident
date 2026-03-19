#pragma once
#include <string>
#include <vector>

//trident settings
#define TRIDENT_DEBUGINFO
//#define TRIDENT_DEBUGINFO_DEEP

//constants & enums
enum ValueType : char {VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT};
enum OperatorType : char {OP_EMPTY, OPn_ADD='+', OPn_MUL='*', OPn_DIV='/', OPn_SUB='-', OPn_MOD='%', OPl_GET='.', OPb_AND='&',OPb_OR='|',OPb_NOT='!',OPb_XOR='^', OPb_COND = '?'};
#define Index int 

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

        std::string string();
};

class ArgumentList{
protected: 
        Value pop();
        Value get();
        std::vector<Value> arguments;
public:
        template <class T>
        void add_val(T t_val) {arguments.push_back(Value(t_val));}

        std::string string();
        void calculate();
};

enum CommandType : char {CMD_EMPTY, CMD_PRINT, CMD_SET};

class Command{};
