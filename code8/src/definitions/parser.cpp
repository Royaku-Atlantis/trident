#include "trident.hpp"
#include "parser.hpp"
#include <sstream>

// for example, transform the text "print "caca" 3 *" into
// command : TYPE=CMD_PRINT - string "caca" - number 3 - operator OPn_MUL
Command cmdtext_to_command(std::string cmd_txt)
{
    
}