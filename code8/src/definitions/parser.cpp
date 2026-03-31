#include "../trident.hpp"
#include <sstream>

// for example, transform the text "print "caca" 3 *" into
// command : TYPE=CMD_PRINT - string "caca" - number 3 - operator OPn_MUL


CommandType cmdtext_get_cmdtype(String cmd_firsttoken)
{
	#define GETCMD(text, cmdtype) if (cmd_firsttoken==text) return cmdtype;
	GETCMD("if",    CMD_IF);
	GETCMD("elif",  CMD_ELIF);
	GETCMD("else",  CMD_ELSE);
	GETCMD("print", CMD_PRINT);
	GETCMD("set",   CMD_SET);
	//GETCMD("error",CMD_) 
	//GETCMD("continue",CMD_) 
	//GETCMD("break",CMD_) 
	//GETCMD("for",CMD_) 
	//GETCMD("while",CMD_)
	return CMD_EMPTY;

	#undef GETCMD
}

// TODO get string as one word
// "word1 blabla "text with quotes are one whole word"
//        ^-6   ^-12
// -> return 12, str = "blabla"
Index get_word(const String & input_string, Index starthere, String & word)
{
	if (input_string.size()<=starthere) return starthere;

	word = ""; //empty the value before we modify it

	//remove the space if it start with spaces
	while (input_string[starthere] == ' ')starthere ++;

	//std::cout << "start at " << starthere << "in str '" << input_string << "' -> " ; //debug

	char endcase = ' ';
	//if the first char of the word is a " -> do until char is '"'
	if (input_string[starthere]=='"')
	{
		std::cout << "str detected";
		endcase = '"';
		starthere ++;
		//TODO make it so that it returns the fact that it is a string value
	}	

	Index endofword = starthere;
	
	//go through the part of the input string, to collect the word
	while (input_string[endofword] != endcase) //if its 
	{
		word += input_string[endofword];
		endofword ++;
		
		//end in case the string is already finished
		if (input_string.size()<=(endofword)) return endofword;
	}

	//std::cout << "word = '" << word << "'\n" ; //debug
	//we also get the actual word found with the "word" variable reference
	return endofword;
}

/*
Command cmdtext_to_command(String cmd_txt)
{
        String cmdname
}*/

/*
"if"
"elif"
"else"
"print"
"set"
"error"
"continue"
"break"
"for"
"while"
"+"
"-"
"*"
"/"
"%"
"."
"and"
"or"
"!"
"xor"
"?"
"<"
">"
"<="
">="
"=="
"~="
"!="
*/