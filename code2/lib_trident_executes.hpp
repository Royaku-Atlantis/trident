#ifndef LIB_TRIDENT_EXECUTES
#define LIB_TRIDENT_EXECUTES

#include <iostream>
#include <string.h>
#include <map>
#include "lib_basic.hpp"
#include "lib_trident_definitions.hpp"

//typedefs for many states for many elements
typedef unsigned char BYTE;

//command list
BYTE get_command_id(std::string potential_command){
        return 0;
}

void say_single_token(Token thisToken)
{
        switch (thisToken.token_type)
        {
                case VALUE:
                        thisToken.printValue();
                break;
                default:
                        std::cout << "#unspecified token#";
                break;                
        }
}
void execute_say(std::vector<Token> saytokens){
        for (Token token : saytokens){
                say_single_token(token); //then include var list and scope
        }
}

void execute_error(){

}



void execute(){
        switch(5){
        }
}

#endif