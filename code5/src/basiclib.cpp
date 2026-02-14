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