#include "basiclib.hpp"
#include <iostream>

void print_argcv(int argc, char * argv[])
{
        std::cout << "\nmain.args :"; 
        for (int i=0 ; i < argc ; i++)
                std::cout << std::endl << argv[i];

        std::cout << "\n-------------\n" ;        
}

void basiclib_libaction()
{
        std::cout << "basiclib linking worked, I guess" << std::endl;
}


char writable_char(char c)
{
        if ((' '<=c) and (c<='~'))
                return c;
        else return '@';
}

void printcharpointer(const char * commandline)
{
        std::cout<<"charlist=\"";
        for (int i=0; commandline[i]!='\0' ;i++)
                std::cout << writable_char(commandline[i]);
        std::cout << "\"\n";
}

std::string removefirst(std::string str)
{
        str[0] = '_';
        return str;
}

void debug(std::string kk, std::string pipi){
        std::cout << kk << pipi << "\n";
}
