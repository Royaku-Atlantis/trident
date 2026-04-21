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
        VALUE_NUMB, VALUE_BOOL, VALUE_VARIABLE, //primitives
        VALUE_STRING, //higher level (more then 8 byte, therfore, its with a pointer)

        VALUE_VALTYPECOUNT //to dynamically create new object types in trident
};
enum OperatorType : unsigned char 
{OP_EMPTY, 
        OPn_ADD, OPn_SUB, OPn_MUL, OPn_DIV, OPn_MOD, 
        
        OPb_AND, OPb_OR, OPb_NOT, OPb_XOR,

        OPc_strictINF, OPc_strictSUP, OPc_equalINF, OPc_equalSUP, 
        OPc_EQUAL, OPc_roundEQUAL, OPc_UNEQUAL,

        OPn_COS, 

        OPn_RAND, OPl_GET, OPb_COND
};
enum CommandType : char {
        CMD_EMPTY, 
        CMD_PRINT, CMD_SAY, 
        CMD_SET, CMD_INPUT, CMD_SETIFUNDEF,
        CMD_JUMP, CMD_JUMPIF, CMD_CALL,
CMD_NUMBEROFCOMMANDS
};

// declaration of everything
#include "values.hpp"
#include "expressions.hpp"
#include "arguments.hpp"
#include "commands.hpp"
#include "parser.hpp"
#include "functions.hpp"
#include "scopes.hpp"
#include "executer.hpp"

#endif //TRIDENT_HEADER