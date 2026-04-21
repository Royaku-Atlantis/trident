#pragma once
#include "trident.hpp"



class Function
{
private:        
        Array<Command *> code; //dont change once created
        Index code_size;
        
        //common procedure for constructor
        void set_from_codelines(const CodeLines & func_code);
public:
        //construct from array of string
        Function (const CodeLines & func_code);

        //construct directly from the filepath
        Function (String filepath);

        //functions to get informations of the function
        Index get_code_size() const;
        Command * get_command(Index cmd_index);
        //methodes for the scope to navigate between brackets

        //display all commands info
        void debug_display_command();//codeline.debug_display_command()
};