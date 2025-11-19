#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include "classes.hpp"
#include "lib.hpp"
using namespace std;

#define filename "joemama.txt"

/* string command line to be executed | line index, to change with ifs and jumps*/
void execute(string command_line, int & line_index, vector<Balise> balise_list, Scope current_scope)
{
        if (command_line=="") return;
        
        stringstream code_line (command_line);
        string command_name;
        code_line >> command_name;

        if (command_name == COMMAND_PRINT)
        {
                execution_say(code_line, current_scope); //add current scope LEFT HERE
                say << endl;
        }
        else if (command_name == COMMAND_GOTO)
        {
                // "lineindex +1" because its start at 0 in code, but 1 in ide
                say << "Jump Called, from line " << line_index+1;
                execution_jump(code_line, line_index, balise_list);
                say << " to line " << line_index+2 << endl;
                //show +2 because it will increment next line execution
        }
        //other commands
        else if (command_name == COMMAND_SETVAR)
        {
                say << command_name << " a var";
                execution_set(code_line, current_scope);
                say << " sucessfully set \n";
        }
        else if (command_name != COMMAND_BALISE)
        {
                say << "\nError invalid command at line "<< line_index+1 <<": \"" << command_line << " \"\n";
                return;
        }
        getch();
}

int main()
{
        fileread filer;
        filer.open(filename);
        
        string command = "";
        vector<string> lines_of_codes;
        vector<Balise> balise_list;
        Scope global;

        while (!filer.eof()){
                getline(filer, command);
                command = clean_command(command);
                balise_add_from_command(command, balise_list, lines_of_codes.size());
                lines_of_codes.push_back(command);
        }
        cout << "there are "<< lines_of_codes.size() << " lines of code \n";

        for (int line_index=0; line_index < lines_of_codes.size() ; line_index++){
                /*if (lines_of_codes.get_line(i).empty())
                        cout << "ENPTY LINE";
                cout << lines_of_codes.get_line(i) << endl;//*/
                execute(lines_of_codes[line_index], line_index, balise_list, global);
        }
        //stringstream ss(str);
        getch();
        return 0;
}