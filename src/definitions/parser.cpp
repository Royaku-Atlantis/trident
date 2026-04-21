#include "../trident.hpp"


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
	word = "";//empty the value before we modify it

	//if the index is already too far, then its finished
	if (input_string.size()<=(starthere))
		return starthere;

	//remove the space if it start with spaces
	while (input_string[starthere] == ' '
		or input_string[starthere] == '|') //to make more lisible .trd code
	starthere ++;

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
	return endofword
	
	+ (endcase == '"');
	//if its in string mode, increment the end of the word to skip the quote
}

// string -> CommandType
CommandType cmdtext_get_cmdtype(String cmd_firsttoken)
{
	#define GETCMD(text, cmdtype) if (cmd_firsttoken==text) return cmdtype;

	GETCMD("print", CMD_PRINT);
	GETCMD("say", 	CMD_SAY);
	GETCMD("set",   CMD_SET);
	GETCMD("input", CMD_INPUT);
	GETCMD("jump",	CMD_JUMP);
	GETCMD("jumpif",CMD_JUMPIF);
	GETCMD("init",	CMD_SETIFUNDEF);
	GETCMD("call",	CMD_CALL);
	GETCMD("exit",	CMD_EXIT);
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
Value string_to_value(const String & input_string)
{
	//case strings
	if (input_string[0] == '"')
	{
		String output_string = input_string;
		output_string.erase(0,1);
		return Value((String)output_string);
	}

	//case variables
	if (input_string.back() == 'v') return Value((int)stoi2(input_string, 0));

	//case numbers
	double output;
	if (get_number_from_string(input_string, output)) return Value(output);

	//test specific str -> value (const)
	#define TEST_STR(txt, val) if (input_string==txt) return Value(val);
	#define TXT_FORMAT(val) "\033[" + val + 'm'

	//constants
	TEST_STR("true", true);
	TEST_STR("false", false);
	TEST_STR("Undefined", Value());


	TEST_STR("endl", (String)"\n");
	TEST_STR("pi", (double)3.14159265359);

	//colors
	TEST_STR("RED", 	(String)RED	);
	TEST_STR("GREEN", 	(String)GREEN	);
	TEST_STR("YELLOW", 	(String)YELLOW	);
	TEST_STR("BLUE", 	(String)BLUE	);
	TEST_STR("MAGENTA", 	(String)MAGENTA	);
	TEST_STR("CYAN", 	(String)CYAN	);
	TEST_STR("WHITE", 	(String)WHITE	);
	TEST_STR("BLACK", 	(String)BLACK	);
	TEST_STR("RESET", 	(String)RESET	); //not a color, reset to default shell
	TEST_STR("DEFAULT",		(String)(TXT_FORMAT(TXT_DEFAULT))	);
	TEST_STR("BOLD",		(String)(TXT_FORMAT(TXT_BOLD))		);
	TEST_STR("DARKER",		(String)(TXT_FORMAT(TXT_DARKER))	);
	TEST_STR("UNDERLINED",		(String)(TXT_FORMAT(TXT_UNDERLINED))	);
	TEST_STR("SETBACKGROUND",	(String)(TXT_FORMAT(TXT_SETBACKGROUND))	);
	TEST_STR("STRIKETHROUGH",	(String)(TXT_FORMAT(TXT_STRIKETHROUGH))	);

	//operators
	TEST_STR("+",	OPn_ADD		);
	TEST_STR("-",	OPn_SUB		);
	TEST_STR("*",	OPn_MUL		);
	TEST_STR("/",	OPn_DIV		);
	TEST_STR("%",	OPn_MOD		);
	TEST_STR(".",	OPl_GET		);
	TEST_STR("and",	OPb_AND		);
	TEST_STR("or",	OPb_OR		);
	TEST_STR("!",	OPb_NOT		);
	TEST_STR("xor",	OPb_XOR		);
	TEST_STR("?",	OPb_COND	);
	TEST_STR("<",	OPc_strictINF	);
	TEST_STR(">",	OPc_strictSUP	);
	TEST_STR("<=",	OPc_equalINF	);
	TEST_STR(">=",	OPc_equalSUP	);
	TEST_STR("==",	OPc_EQUAL	);
	TEST_STR("~=",	OPc_roundEQUAL	);
	TEST_STR("!=",	OPc_UNEQUAL	);
	TEST_STR("cos",	OPn_COS		);
	TEST_STR("rand",OPn_RAND	);
	
	#undef TEST_STR
	#undef TXT_FORMAT

	//return undefined
	return Value();
}

// String code_line -> command object
Command * create_command(const String & code_line)
{
	//get the command type
	String commandname;
	Index next_word = get_word(code_line, 0, commandname);
	CommandType command_type = cmdtext_get_cmdtype(commandname);

	//define the command
	Command * newcmd = new Command(command_type);

	//define the command arguments
	String str_value;
	next_word = get_word(code_line, next_word, str_value);

	//loop through the "words" of the code line 
	while (str_value != "")
	{
		Value newval = string_to_value(str_value);
		newcmd->append_expression(newval);
		next_word = get_word(code_line, next_word, str_value);
	}

	//return the newly created command
	return newcmd;
}

