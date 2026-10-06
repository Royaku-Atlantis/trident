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
		case VALUE_STRING: return "Str";
		default : return "INVALID_TYPE";
		//case VALUE_VALTYPECOUNT:
	}
}