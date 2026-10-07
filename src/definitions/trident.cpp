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
		case CMD_EMPTY: return "CMD_EMPTY"; 
		case CMD_PRINT: return "CMD_PRINT"; 
		case CMD_SAY: return "CMD_SAY"; 
		case CMD_SET: return "CMD_SET"; 
		case CMD_INPUT: return "CMD_INPUT"; 
		case CMD_SETIFUNDEF: return "CMD_SETIFUNDEF"; 
		case CMD_UNREF: return "CMD_UNREF";
		case CMD_JUMP: return "CMD_JUMP"; 
		case CMD_JUMPIF: return "CMD_JUMPIF";
		case CMD_CALL: return "CMD_CALL"; 
		case CMD_EXIT: return "CMD_EXIT"; 
		case CMD_RETURN: return "CMD_RETURN";
		default:
			if (CmdType >= CMD_NUMBEROFCOMMANDS)
				return "INVALID_CMD_INDEX:"+std::to_string(CmdType);
			else 
				return "CMD forgotten in commandtype_string:"+std::to_string(CmdType);
	}
}