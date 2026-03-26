#include "../general.hpp"
#include <iostream>
#include "../values.hpp"

std::string textFormat(int fontcolor)
{
	return "\033[" + std::to_string(fontcolor) + "m";
}


void say(const std::string & text)
{std::cout<<text<<std::endl;}
void say(const std::string & text, const Value & val)
{std::cout<<text<<val.string()<<std::endl;}

std::string double_to_trimmed_string(double value)
{
	std::string str = std::to_string(value);

	//trim the useless 0
	str.erase(str.find_last_not_of('0') + 1, std::string::npos );

	//remove the . if its a whole nuber
	if (str.back()=='.') str.pop_back();

	return str;
}

