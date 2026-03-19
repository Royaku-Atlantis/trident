#pragma once

#include <iostream>

template <class T>
void say(const std::string & text, const T & txt2)
{std::cout<<text<<txt2<<'\n';}

void say(const std::string & text);