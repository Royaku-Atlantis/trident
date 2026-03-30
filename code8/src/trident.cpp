#ifndef TRIDENT_HEADER
#define TRIDENT_HEADER

//generalist local library
#include "general.hpp"

//#define DEBUGINFO
//#define DEBUGINFO_DEEP

//define types
#define CodeLines Array<String>

//enums :
enum ValueType : unsigned char {VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT};
enum OperatorType : unsigned char {OP_EMPTY, OPn_ADD, OPn_MUL, OPn_DIV, OPn_SUB, OPn_MOD, OPl_GET, OPb_AND, OPb_OR, OPb_NOT, OPb_XOR, OPb_COND, OPc_strictINF, OPc_strictSUP, OPc_equalINF, OPc_equalSUP, OPc_EQUAL, OPc_roundEQUAL, OPc_UNEQUAL};
enum CommandType : char {CMD_EMPTY, CMD_IF, CMD_ELIF, CMD_ELSE, CMD_PRINT, CMD_SET, CMD_NUMBEROFCOMMANDS};

//commands trdident string
#define COMMAND_TOKEN_if "if"
#define COMMAND_TOKEN_elif "elif"
#define COMMAND_TOKEN_else "else"
#define COMMAND_TOKEN_print "print"
#define COMMAND_TOKEN_set "set"
#define COMMAND_TOKEN_error "error" 


// declaration of everything
#include "values.hpp"
#include "expressions.hpp"
#include "arguments.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include "scopes.hpp"
#include "executer.hpp"

#endif //TRIDENT_HEADER