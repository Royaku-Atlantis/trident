#pragma once

#include "trident.hpp"
#include <sstream>

/*
 * @brief In the input_string, 
 *  -get the word starting in Index starthere,
 *  -returning the end of the word.
 *  -saving the found word in word &.
 *  The "words" are considered separated by spaces
 *  Or, if it reads a quote first, then it will read as a string,
 *  and will wait a for second quote to consider the word to be finished
 * //Command cmdtext_to_command(String cmd_txt);
 * // for example, transform the text "print "caca" 3 *" into
 * // command : TYPE=CMD_PRINT - string "caca" - number 3 - operator OPn_MUL
 * @param input_string
 * @param starthere
 * @param word, outputed word found at indext start here
 * @return Index of the end of the word (the space just after)
 */

Index get_word(const String & input_string, Index starthere, String & word);

Value string_to_value(const String & input_string);

//string cmd_firsttoken -> get command type
CommandType cmdtext_get_cmdtype(String cmd_firsttoken);

//String code_line, (variable map, not yet though) -> Command
Command * create_command(const String & code_line);
