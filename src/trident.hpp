#ifndef TRIDENT_HEADER
#define TRIDENT_HEADER

//generalist local library
#include "general.hpp"

//#define DEBUGINFO
//#define DEBUGINFO_DEEP

//define types
#define CodeLines Array<String>

//enums :
enum ValueType : unsigned int {
        VALUE_UNDEF, VALUE_OPERATOR, //fondamentals
        VALUE_NUMB, VALUE_BOOL, //primitives
        VALUE_VARIABLE, VALUE_VAREFERENCE, //primitives
        VALUE_STRING, //higher level (more then 8 byte, therfore, its with a pointer)

        VALUE_VALTYPECOUNT //get the max idx to dynamically create new object types in trident
};

String valuetype_string(ValueType);

enum OperatorType : unsigned char 
{OP_EMPTY, 
        //Basic Numbers operands
        OPn_ADD, OPn_SUB, OPn_MUL, OPn_DIV, OPn_MOD, 
        //trigonometry
        OPn_COS, 
        //Booleans
        OPb_AND, OPb_OR, OPb_NOT, OPb_XOR, 
        //Comparator
        OPc_strictINF, OPc_strictSUP, OPc_equalINF, OPc_equalSUP, 
        OPc_EQUAL, OPc_roundEQUAL, OPc_UNEQUAL, 
        //peculiar operator
        OPn_RAND, OPb_COND, OPn_ABS, 
        //object and variable management
        OPv_REF, OPl_GET, 
};

enum CommandType : char {
        CMD_EMPTY, 
        CMD_PRINT, CMD_SAY, 
        CMD_SET, CMD_INPUT, CMD_SETIFUNDEF, CMD_UNREF,
        CMD_JUMP, CMD_JUMPIF,
        CMD_CALL, CMD_EXIT, CMD_RETURN,
CMD_NUMBEROFCOMMANDS
};

// declaration of everything
#include "values.hpp"
#include "expressions.hpp"
#include "arguments.hpp"
#include "commands.hpp"
#include "parser.hpp"
#include "functions.hpp"
#include "executer.hpp"

#endif //TRIDENT_HEADER