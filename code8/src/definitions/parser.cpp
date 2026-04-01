#include "../trident.hpp"
#include <sstream>

// for example, transform the text "print "caca" 3 *" into
// command : TYPE=CMD_PRINT - string "caca" - number 3 - operator OPn_MUL

// .ATL TO .TRD
//infix to postfix etc...


/* ----------------------- */
/* .TRD TO PURE TRIDENT	*/
/* ----------------------- */

// TODO : backslash support
Index get_word(const String & input_string, Index starthere, String & word)
{
	if (input_string.size()<=starthere) return starthere;

	word = ""; //empty the value before we modify it

	//remove the space if it start with spaces
	while (input_string[starthere] == ' ')starthere ++;

	//std::cout << "start at " << starthere << "in str '" << input_string << "' -> " ; //debug

	char endcase = ' ';
	//if the first char of the word is a " -> do until char is '"'
	bool there_just_was_an_antislash = false;
	if (input_string[starthere]=='"')
	{
		//std::cout << "str detected"; //debug
		endcase = '"';	
		word += '"';	// make it so that it returns the fact that it is a string value
		starthere ++;	//if we dont increment, the while loop will instantly stop at the first quotation mark, which is kinda dumb lmao
	}	

	Index endofword = starthere;
	
	//go through the part of the input string, to collect the word
	while (input_string[endofword] != endcase)
	{
		there_just_was_an_antislash = false;

		//if we're working on a string, check for '\'
		//if (endcase == '"') there_just_was_an_antislash = input_string[endofword]=='\\';
		//check for next character, do a switch or something
		
		word += input_string[endofword];
		endofword ++;

		//end in case the string is already finished
		if (input_string.size()<=(endofword)) break;
	}

	//std::cout << "word = '" << word << "'\n" ; //debug
	//we also get the actual word found with the "word" variable reference
	return endofword;
}

// string -> CommandType
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

	//if no other cmd is recognised
	return CMD_EMPTY;

	#undef GETCMD
}

//string -> Value 
Value string_to_value(String & input_string)
{
	say("Transforming '"+input_string+"' into a value");

	//case variables
	if (input_string.back() == 'v') return Value((int)stoi2(input_string, 0));

	//case strings
	if (input_string[0] == '"') return Value(input_string.erase(0,1));


	//case numbers
	double output;
	if (get_number_from_string(input_string, output)) return Value(output);

	//operators
	#define TEST_OPERATOR(txt, OP_ID) if (input_string==txt) return Value(OP_ID);

	TEST_OPERATOR("+",	OPn_ADD		)
	TEST_OPERATOR("-",	OPn_SUB		)
	TEST_OPERATOR("*",	OPn_MUL		)
	TEST_OPERATOR("/",	OPn_DIV		)
	TEST_OPERATOR("%",	OPn_MOD		)
	TEST_OPERATOR(".",	OPl_GET		)
	TEST_OPERATOR("and",	OPb_AND		)
	TEST_OPERATOR("or",	OPb_OR		)
	TEST_OPERATOR("!",	OPb_NOT		)
	TEST_OPERATOR("xor",	OPb_XOR		)
	TEST_OPERATOR("?",	OPb_COND	)
	TEST_OPERATOR("<",	OPc_strictINF	)
	TEST_OPERATOR(">",	OPc_strictSUP	)
	TEST_OPERATOR("<=",	OPc_equalINF	)
	TEST_OPERATOR(">=",	OPc_equalSUP	)
	TEST_OPERATOR("==",	OPc_EQUAL	)
	TEST_OPERATOR("~=",	OPc_roundEQUAL	)
	TEST_OPERATOR("!=",	OPc_UNEQUAL	)

	#undef TEST_OPERATOR
	//return undefined
	return Value();
}

// String code_line -> command object
Command * create_command(const String & code_line)
{
	say("start to create command");
	//get the command type
	String commandname;
	Index next_word = get_word(code_line, 0, commandname);
	CommandType command_type = cmdtext_get_cmdtype(commandname);

	say("command type gotten");

	//define the command
	Command * newcmd = new Command(command_type);

	say("command defined");

	//define the command arguments
	String str_value;
	do
	{
		next_word = get_word(code_line, next_word, str_value);
		newcmd->append_expression(string_to_value(str_value));

		say("apended value");
	}
	while (str_value != "");

	say("finished apendding values");

	//return the newly created command
	return newcmd;
}

