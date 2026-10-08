#include "../trident.hpp"
#include "../commands.hpp"

 //common procedure for constructor
void Function::set_from_codelines(CodeLines func_code)
{
        Map<String, Index> balises;

        //init code
        repeat (func_code.size())
        {
                String & code_line = func_code[iterator];

                trim(code_line);
                //case of ignore code line
                if (code_line=="" or code_line[0]=='#')
                {
                        func_code.erase(func_code.begin() + iterator);
                        iterator --;
                        continue;
                }

                //is valid command, check for Balise
                String command_name;
                String balise_name;
	        Index next_word_idx = get_word(code_line, 0, command_name);

                //if its not a balise line, check next
                if (command_name != "balise") continue;

                //get balise name
                get_word(code_line, next_word_idx, balise_name);
                if (balise_name != "")
                {
                        if (balises.count(balise_name) == 0)
                                balises.insert({balise_name, iterator});
                }
                //erase this code line, as it's a balise (cmdmacro)  
                func_code.erase(func_code.begin() + iterator);
                iterator --;
        }

        //set fonction
        repeat (func_code.size())
        {
                String & code_line = func_code[iterator];   
                code.push_back(create_command(code_line, iterator, balises));
        }
        code_size = func_code.size();
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

Function::~Function()
{
        say("Function is being destroyed");
}

//functions to get informations of the function
Index Function::get_code_size() const
{
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