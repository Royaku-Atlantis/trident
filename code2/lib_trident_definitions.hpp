#ifndef LIB_TRIDENT_DEFINITIONS
#define LIB_TRIDENT_DEFINITIONS

#include <iostream>
#include <string.h>
#include <map>
#include "lib_basic.hpp"

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

        void printInfo(){
                std::cout<<"token type:"<<(short int)token_type<<" info:"<<token_info<<" valNumb="<<numeric_value<<" valText=\""<<string_value<<'\"';
        }

        std::string printValue()
        {
                switch(token_type){
                case VALUE:
                        if (token_info==VALUE_TEXT)
                                return string_value;
                        if (token_info==VALUE_NUMBER)
                                return std::to_string(numeric_value);
                        return "Undefined";

                case VARIABLE_ID:
                        return '['+string_value+']';

                default:
                        return "#TokenType" + std::to_string(token_type) + '#';        
                }
                return "ERROR WTF";
        }

        Token(){
                std::cout<<"Create1 token\n";
                setval();
        }
        Token(tokenType _token_type, INDEX _token_info, float numbval, std::string strval){
                std::cout<<"Create2 token\n";
                setval(token_type, token_info, numbval ,strval);
        }
        Token(tokenType _token_type, INDEX _token_info){
                std::cout<<"Create3 token\n";
                setval(_token_type, _token_info);
        }
        
        Token(float valnumb){
                std::cout<<"Create4 token\n";
                setval(VALUE, VALUE_NUMBER, valnumb);
        }
        Token(std::string valtext){
                std::cout<<"Create5 token\n";
                setval(VALUE, VALUE_TEXT,0, valtext);
        }

private:
        void setval(tokenType _token_type = NOTVALID, INDEX _token_info = INVALID_INFO, float numbval=0, std::string strval = ""){
                if (TOKEN_TYPE_MAX_INDEX<_token_type){
                        std::cout<<"Tried to create a token with invalid token index : "<<(short int)_token_type<<" which is higher then max : "<<TOKEN_TYPE_MAX_INDEX<<"\n";
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
                                        token_info = VALUE_TEXT;
                                        numeric_value = 0;
                                        string_value = strval;
                                break;
                                case VALUE_NUMBER:
                                        token_info = VALUE_NUMBER;
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

class Trident_Line{
        std::vector<Token> tokens;

};

class Scope{
public:
        INDEX reading_line = 0;
        INDEX number_of_line;
        void add_line(std::string code_line){
                INDEX reading_char = 0;

                for (INDEX c=0; c<code_line.size(); c++){
                        std::cout<<read_string_from(code_line,c)<<" - "<<std::endl;
                }
        }

        std::vector<Trident_Line> lines;
        std::vector<Token> variables;

private:

};

#endif