#pragma once
#include "basiclib.hpp"
#include <iostream>


void print_argcv(int argc, char * argv[]);

void basiclib_libaction();

char writable_char(char c);

void printcharpointer(const char *);

void debug(std::string kk, std::string pipi = "");

std::string removefirst(std::string str);

template <typename Type>
Type buffer_to_float(char buffer[sizeof(Type)]){

}