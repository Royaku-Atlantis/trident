#pragma once

#include "trident.hpp"
#include <sstream>

Command cmdtext_to_command(String cmd_txt);
// for example, transform the text "print "caca" 3 *" into
// command : TYPE=CMD_PRINT - string "caca" - number 3 - operator OPn_MUL