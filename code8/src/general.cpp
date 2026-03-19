#include "general.hpp"
#include <iostream>

std::string textFormat(int fontcolor)
{
    return "\033[" + std::to_string(fontcolor) + "m";
}

void say(const std::string & text)
{std::cout<<text<<std::endl;}

std::string double_to_trimmed_string(double value)
{
        std::string str = std::to_string(value);
        str.erase(str.find_last_not_of('0') + 1, std::string::npos );
        if (str.back()=='.') str.pop_back();

        return str;
}
