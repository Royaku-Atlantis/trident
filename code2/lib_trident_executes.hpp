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
        return 0;//COMMAND_NAMES[];
}

void execute_say(std::vector<Token> saytokens){
        for (Token token : saytokens){
                std::cout<<token.printValue()<<" "; //then include var list and scope
        }
        std::cout<<std::endl;
}

#endif