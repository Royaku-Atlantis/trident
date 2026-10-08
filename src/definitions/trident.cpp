#include "../trident.hpp"

String valuetype_string(ValueType ValType)
{
	switch (ValType)
	{
		case VALUE_UNDEF: return "Undef";
		case VALUE_OPERATOR: return "Op";
		case VALUE_NUMB: return "Numb";
		case VALUE_BOOL: return "Bool";
		case VALUE_VARIABLE: return "Var";
		case VALUE_VAREFERENCE: return "VarRef";
		case VALUE_STRING: return "Str";
		default : return "INVALID_TYPE";
		//case VALUE_VALTYPECOUNT:
	}
}


String commandtype_string(CommandType CmdType)
{
	switch (CmdType)
	{
		case CMD_EMPTY: return "EMPTY"; 
		case CMD_PRINT: return "PRINT"; 
		case CMD_SAY: return "SAY"; 
		case CMD_SET: return "SET"; 
		case CMD_INPUT: return "INPUT"; 
		case CMD_SETIFUNDEF: return "SETIFUNDEF"; 
		case CMD_UNREF: return "UNREF";
		case CMD_JUMP: return "JUMP"; 
		case CMD_JUMPIF: return "JUMPIF";
		case CMD_CALL: return "CALL"; 
		case CMD_EXIT: return "EXIT"; 
		case CMD_RETURN: return "RETURN";
		default:
			if (CmdType >= CMD_NUMBEROFCOMMANDS)
				return "CMD["+std::to_string(CmdType)+"]:INVALID_INDEX";
			else 
				return "CMD["+std::to_string(CmdType)+"]:Forgotten in commandtype_string()";
	}
}