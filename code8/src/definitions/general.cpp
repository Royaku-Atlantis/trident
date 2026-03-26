#include "../trident.hpp"
#include "../general.hpp"

bool GLOBAL_ErrorTellProgrammer = false;

std::string textFormat(int fontcolor)
{
	return "\033[" + std::to_string(fontcolor) + "m";
}

void print_error(const std::string & errortext)
{
        if (GLOBAL_ErrorTellProgrammer)
                std::cout << "\n\033[31m" << errortext << "\n\033[0m\n";
}

void say(const std::string & text)
{std::cout<<text<<std::endl;}

std::string double_to_trimmed_string(double value)
{
	std::string str = std::to_string(value);

	//trim the useless 0
	str.erase(str.find_last_not_of('0') + 1, std::string::npos );

	//remove the . if its a whole nuber
	if (str.back()=='.') str.pop_back();

	return str;
}

