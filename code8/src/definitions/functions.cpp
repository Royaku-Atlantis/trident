#include "../trident.hpp"
#include "../commands.hpp"

 //common procedure for constructor
void Functions::set_from_codelines(const CodeLines & func_code)
{
        code_size = func_code.size();

        for (String codeline : func_code)
                code.push_back(create_command(codeline));
}

//construct from array of string, aka CodeLines
Functions::Functions(const CodeLines & func_code)
{
        set_from_codelines(func_code);
}

//construct directly from the filepath
Functions::Functions(String file_path)
{
        CodeLines code_lines;
        get_file(file_path, code_lines);
        set_from_codelines(code_lines);
}


//functions to get informations of the function
Index Functions::get_code_size() const
{
        return code_size;
}

Command * Functions::get_command(Index cmd_index)
{
        if (code_size <= cmd_index) return nullptr;
        return code[cmd_index];
}


//methodes for the scope to navigate between brackets ?