#pragma once

#include "basiclib.hpp"
#include "trident.hpp"
#include <iostream>
#include <vector>

void trident_libaction();

enum TokenType : char {EMPTY, NOCOMMAND, PRINT, GOTO, SETVAL, CONSTVAL, TEXT, VARINDEX};

typedef unsigned int codelineindex;
typedef unsigned int codebufferindex;

#define EndOfCodeBuffer ~(codebufferindex)0 // = 0b1111...111
#define maxCommandIndex 256

class Executer{
        std::vector<char> codebuffer;
        codebufferindex commandindexes [maxCommandIndex];

        codelineindex lastcodelineindex;


        float variables [256];

        codelineindex execute_line(codelineindex index);

public:
        Executer ();

        void execute();
        void addcodeline(const char * charlist);
};