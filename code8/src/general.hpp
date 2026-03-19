#pragma once
#include <iostream>

#define RED 31  //red     31   41
#define YELLOW 33  //yellow  33   43
#define GREEN 32   //green   32   42
#define CYAN 36  //cyan    36   46
#define BLUE 34  //blue    34   44
#define MAGENTA 35  //magenta 35   45
#define WHITE 37  //white   37   47
#define BLACK 30  //black   30   40
#define DARK 30

enum textStatus {TXT_DEFAULT, TXT_BOLD, TXT_DARKER, TXT_idk1, TXT_UNDERLINED, TXT_idk5, TXT_idk6, TXT_SETBACKGROUND, TXT_idk8, TXT_STRIKETHROUGH};
std::string textFormat(int fontcolor = 0);

template <class T>
void say(const std::string & text, const T & txt2)
{std::cout<<text<<txt2<<'\n';}

void say(const std::string & text);

//use to compare Multiple char at the same time
constexpr int AND(char c1, char c2, char c3=0, char c4=0) 
{
    //will transform (0xAA, 0xBB, 0xCC, 0xDD) into 0xDDCCBBAA
    return (int)c1 + ((int)c2<<8) + ((int)c2<<16) + ((int)c2<<24);
}

std::string double_to_trimmed_string(double value);


