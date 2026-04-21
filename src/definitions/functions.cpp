#include "../trident.hpp"
#include "../commands.hpp"

 //common procedure for constructor
void Function::set_from_codelines(const CodeLines & func_code)
{
        code_size = func_code.size();

        for (String codeline : func_code)
        {
                code.push_back(create_command(codeline));
        }
}

//construct from array of string, aka CodeLines
Function::Function(const CodeLines & func_code)
{
        set_from_codelines(func_code);
}

//construct directly from the filepath
Function::Function(String file_path)
{
        CodeLines code_lines;
        get_file(file_path, code_lines);
        set_from_codelines(code_lines);
}


//functions to get informations of the function
Index Function::get_code_size() const
{
        return code_size;
}

Command * Function::get_command(Index cmd_index)
{
        if (code_size <= cmd_index) return nullptr;
        return code[cmd_index];
}

//methodes for the scope to navigate between brackets ?

//debug 
void Function::debug_display_command()
{
        for (Command * codeline : code)
                codeline->debug_display_command();
}