#include "../trident.hpp"
#include "../commands.hpp"

 //common procedure for constructor
void Function::set_from_codelines(const CodeLines & func_code)
{
        for (String codeline : func_code)
        {
                trim(codeline);

                //case of ignior code line
                if (codeline=="" or codeline[0]=='#') continue;
                
                code.push_back(create_command(codeline));
                say("addline:" + codeline);
        }
        code_size = code.size();
        std::cout << "\nfunction code size:'" << code_size <<", adress="<<this<<"-";
}

//construct from array of string, aka CodeLines
Function::Function(const CodeLines & func_code)
{
        set_from_codelines(func_code);
}

//construct directly from the filepath
Function::Function(String file_path)
{
        say("TEST Function");
        CodeLines code_lines;
        get_file(file_path, code_lines);
        set_from_codelines(code_lines);
        say("TEST Function done");
}

Function::~Function()
{
        say(BLUE "Function is being destroyed");
}

//functions to get informations of the function
Index Function::get_code_size() const
{
        std::cout<< RED "ABOUT TO GET SEGFAULT?" RESET;
        return code_size;
}

Command Function::get_command(Index cmd_index) const
{
        //std::cout<<"\n(GetCommand(Index) code_size="<<get_code_size()<<", cmd_index="<<cmd_index<<", code.size()"<<code.size()<<")\n";
        if (code_size <= cmd_index) 
        {
                return Command (CMD_EMPTY);
        }
        return code[cmd_index];
}

//methodes for the scope to navigate between brackets ?

//debug 
void Function::debug_display_command() const
{
        for (Command codeline : code)
                codeline.debug_display_command();
}