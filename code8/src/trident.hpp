#pragma once

//generalist local library
#include "general.hpp"

//#define DEBUGINFO
//#define DEBUGINFO_DEEP


//enums :
enum ValueType : unsigned char {VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR, VALUE_VALTYPECOUNT};
enum OperatorType : unsigned char {OP_EMPTY, OPn_ADD, OPn_MUL, OPn_DIV, OPn_SUB, OPn_MOD, OPl_GET, OPb_AND, OPb_OR, OPb_NOT, OPb_XOR, OPb_COND};
enum CommandType : char {CMD_EMPTY, CMD_IF, CMD_ELIF, CMD_ELSE, CMD_PRINT, CMD_SET};

// declaration of everything
#include "values.hpp"
#include "expressions.hpp"
#include "arguments.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include "scopes.hpp"
#include "executer.hpp"