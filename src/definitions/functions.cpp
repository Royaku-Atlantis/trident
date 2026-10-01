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
        std::cout << "Code size at LALALALAL initialisation of function:'" << code_size <<"'-----";
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
        std::cout<< RED "ABOUT TO GET SEGFAULT?" RESET;
        return code_size;
}

Command * Function::get_command(Index cmd_index) const
{
        //std::cout<<"\n(GetCommand(Index) code_size="<<get_code_size()<<", cmd_index="<<cmd_index<<", code.size()"<<code.size()<<")\n";
        std::cout<<"function about to show itself ";
        debug_display_command();

        if (code_size <= cmd_index) 
        {
                error("\nGetCommand(Index) = NULLPTR");
                return nullptr;
        }
        std::cout<<"\n(GetCommand(Index) != nullptr, supposedly)";
        if (code[cmd_index]==nullptr)
                std::cout<<"\n(WAIT, GetCommand(Index) is nullptr, WHAT??, code_size="<<code_size<<")";
        return code[cmd_index];
}

//methodes for the scope to navigate between brackets ?

//debug 
void Function::debug_display_command() const
{
        for (Command * codeline : code)
                codeline->debug_display_command();
}