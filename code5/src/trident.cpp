#include "basiclib.hpp"
#include "trident.hpp"
#include <iostream>
#include <vector>

void trident_libaction()
{
        std::cout << "Trident linking worked, I guess" << std::endl;
}

Executer::Executer (){ //constructor
        lastcodelineindex = 0;
        commandindexes[0] = 0;
        for (int i=1; i<maxCommandIndex; i++)
        {
                commandindexes[i]= EndOfCodeBuffer;
                variables[i] = -1;
        }
}

codelineindex Executer::execute_line(codelineindex index)
{
        codebufferindex buffer_codeline_start = commandindexes[index];
        codebufferindex buffer_codeline_end = EndOfCodeBuffer;
        if (index < maxCommandIndex) buffer_codeline_end = commandindexes[index+1];

        TokenType CommandId = (TokenType)codebuffer[buffer_codeline_start];

        debug("gonna do command : ", std::to_string(CommandId));

        switch (CommandId)
        {
                case PRINT: //EMPTY, PRINT, GOTO, CONSTVAL, TEXT, VARINDEX, SETVAL};
                        for (int i=buffer_codeline_start+1; i<buffer_codeline_end; i++)
                        {
                                std::cout << codebuffer[i];
                        }
                break;
                case GOTO:
                        return codebuffer[buffer_codeline_start+1]; //get next value, yet, just a char
                break;
                case SETVAL:
                        variables[buffer_codeline_start+1] = 0;
                break;
                case EMPTY:
                case NOCOMMAND:
                        return index;
                default:
                        std::cout << "Error, got command invalid index : " << (int)codebuffer[buffer_codeline_start] << std::endl;
                        std::cout << "is char : \'" << codebuffer[buffer_codeline_start] << "\' \n";
                        return maxCommandIndex;
                break;
        }

        return index;
}

void Executer::execute()
{
        for(    codelineindex PC=0;
                PC < lastcodelineindex;
                PC ++)
        {
                PC = execute_line(PC);
        }
}


void Executer::addcodeline(const char * charlist)
{
        //printcharpointer(charlist);

        int charlist_len = 0;
        for (int i=0; charlist[i]!='\0'; i++)
        {
                codebuffer.push_back(charlist[i]);
                charlist_len = i;
        }
        charlist_len ++;
        codebuffer.push_back('\0');

        codebufferindex codelinestart = commandindexes[lastcodelineindex];// + charlist_len;
        commandindexes[lastcodelineindex] = codelinestart;
        commandindexes[lastcodelineindex+1] = codelinestart + charlist_len+1;
        lastcodelineindex ++;
}