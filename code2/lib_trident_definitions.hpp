#ifndef LIB_TRIDENT_DEFINITIONS
#define LIB_TRIDENT_DEFINITIONS

#include <iostream>
#include <string.h>
#include <map>
#include "lib_basic.hpp"
//typedefs for many states for many elements
typedef unsigned char BYTE;
typedef unsigned int INDEX;

//TOKEN INFOS
#define INVALID_INFO 0

std::string COMMAND_NAMES[] = {"","say", "set", "numb", "str", "object", "jump", "balise", "error", "if", "for", "function", ""};
#define COMMAND_PRINT 1 
#define COMMAND_SETVAR 2 
#define COMMAND_NUMBER 3 
#define COMMAND_STRING 4 
#define COMMAND_OBJECT 5 
#define COMMAND_JUMP 6 
#define COMMAND_BALISE 7 
#define COMMAND_SAYERROR 8 
#define COMMAND_IFLOOP 9 
#define COMMAND_FORLOOP 10
#define COMMAND_FUNCTION 11

#define COMMAND_maxindex 11

std::string OPERATOR_NAMES[] = {"", "!","+","*","/","."};
#define OPERATOR_NOT 1
#define OPERATOR_ADD 2
#define OPERATOR_MULTIP 3
#define OPERATOR_DIVIDE 4
#define OPERATOR_OBJ_GET 5

#define OPERATOR_maxindex 5

#define VALUE_UNDEFINED 0
#define VALUE_NUMBER 1
#define VALUE_TEXT 2

#define VALUE_maxindex 2

#define TOKEN_TYPE_MAX_INDEX 6


enum tokenType : BYTE {NOTVALID, COMMAND, OPERATOR, VALUE, VARIABLE_ID, BALISE_ID, OBJECT_ID};
class Token{
public:
        tokenType token_type;
        INDEX token_info;

        float numeric_value = 0;
        std::string string_value = "";

        std::string printValue()
        {
                if (token_type==VALUE){
                        if (token_info==VALUE_UNDEFINED)
                                return "undefined";
                        if (token_info==VALUE_TEXT);
                                return string_value;
                        if (token_info==VALUE_NUMBER)
                                return std::to_string(numeric_value);
                }
                return "#UnspecifiedToken#";
        }

        Token(){
                setval();
        }
        Token(tokenType _token_type){
                setval(_token_type);
        }
        Token(tokenType _token_type, INDEX _token_info){
                setval(_token_type, _token_info);
        }
        Token(float numbval){
                setval(VALUE, VALUE_NUMBER, numbval);
        } 
        Token(std::string strval){
                setval(VALUE, VALUE_TEXT,0,strval);
        }

private:
        void setval(tokenType _token_type = NOTVALID, INDEX _token_info = INVALID_INFO, float numbval=0, std::string strval = ""){
                if (TOKEN_TYPE_MAX_INDEX<token_type){
                        token_type = NOTVALID;
                        token_info = INVALID_INFO;
                        return;
                }
                token_type = _token_type;

                switch(_token_type){
                        case COMMAND:
                                if (COMMAND_maxindex <= _token_info){
                                        token_info = INVALID_INFO;
                                        return;
                                }
                                token_info = _token_info;
                        break;
                        case OPERATOR:
                                if (_token_info<=OPERATOR_maxindex){
                                        token_info = INVALID_INFO;
                                }
                                token_info = _token_info;
                        break;
                        case VALUE:
                                switch (_token_info){
                                case VALUE_TEXT:
                                        numeric_value = 0;
                                        string_value = strval;
                                break;
                                case VALUE_NUMBER:
                                        numeric_value = numbval;
                                        string_value = "";
                                break;
                                default:
                                        token_info = VALUE_UNDEFINED;
                                        numeric_value = 0;
                                        string_value = "";
                                break;
                                }
                        break;
                        case VARIABLE_ID:

                        break;
                        case BALISE_ID:

                        break;
                        case OBJECT_ID:
                        break;
                        default:
                                token_type = NOTVALID;
                                token_info = INVALID_INFO;
                                numeric_value = 0;
                                string_value = ""; 
                        break;
                }
                
        }
};

/*
class Token_Value : Token{
public:
        BYTE state;
        float numeric_value;
        std::string string_value;

        Token_Value(){
                state = VALUE_UNDEFINED;
                numeric_value = 0;
                string_value = "";        
        }
        Token_Value(float number){
                state = VALUE_NUMBER;
                numeric_value = number;
                string_value = "";        
        }
        Token_Value(std::string text){
                state = VALUE_TEXT;
                numeric_value = 0;
                string_value = text;        
        }

        std::string printValue(){
                switch (state){
                        case VALUE_TEXT:
                                return string_value;
                        case VALUE_NUMBER:
                                return std::to_string(numeric_value);
                        default:
                                return "-Undefined-";
                }
        }
private:
};

class Trident_Line{
        std::vector<Token> tokens;
};

class Scope{

        void add_line(std::string code_line){

        }

        std::vector<Trident_Line> lines;
        std::vector<> variables;
};*/

#endif