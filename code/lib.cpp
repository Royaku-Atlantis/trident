#include "basic_lib.hpp"
#include "classes.hpp"
#include "lib.hpp"

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>

//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝
//commands and parameters definitions

std::ostream& say = std::cout;
std::istream& input = std::cin;
std::string nl = "\n";

typedef std::ifstream fileread;
typedef std::ofstream filewrite;

bool is_end_of_line(fileread & filer) //detect end of file
{
        char C, D;
        do {
                filer.get(C);
                D = filer.peek();
        }
        while (!filer.eof() and C!='\n' and !is_char_writable(D));

        if (C=='\n'){
                say << "\n -- Endl -- \n";
                return true;
        }
        return false;
}

std::string trim(const std::string& line)
{
    const char* WhiteSpace = " \t\v\r\n";
    std::size_t start = line.find_first_not_of(WhiteSpace);
    std::size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? std::string() : line.substr(start, end - start + 1);
}

unsigned int stoi2(std::string text_to_convert, int default_value){
        try{
                return stoi(text_to_convert);
        }
        catch(...){
                return default_value;
        }
}


std::string clean_command(std::string command){

        //if the line has no command
        if (command.empty() or command[0]==COMMENT_CHAR)
                return "";
        
        //TODO : check if the command is valid (say, for...)
        int start_of_comment = command.find(COMMENT_CHAR);

        //for command that has a comment
        if (start_of_comment!=-1){//string::npos) 
                int length_to_erase = command.length() - start_of_comment;
                command.erase(start_of_comment,length_to_erase);   
        }

        //clean start and end whitespace
        return trim(command);       
}

void balise_add_from_command(std::string clean_command, std::vector<Balise> & balises, int line_index){
        std::stringstream command (clean_command);
        std::string commandtest;
        command >> commandtest;

        if (!command.eof() and commandtest == COMMAND_BALISE){
                std::string balisename;
                command >> balisename;
                std::cout << "Debug push back of add balise";
                balises.push_back(Balise (balisename, line_index+1));
        }
}

int find_balise(std::string balisename,const std::vector<Balise> & balises){
    for (int i=0; i<balises.size() ; i++){
        if (balises[i].name == balisename)
            return balises[i].line_index;
    }
    return NOLINE;
}


///////////////////////////////////

void execution_say(std::stringstream & command,Scope & current_scope)
{
        bool stringmode = false;
        std::string text;
        
        do
        {
                command >> text;
                //check if lastchar is ", and not \", but check if only 1 char (no \" possible)
                if (!stringmode and text[0]=='"')
                {
                        stringmode = true;
                        text[0] = '\0';
                } 
                bool this_txt_is_end_of_string = (stringmode) and text.back()=='"' and
                        (text.length()==1 ? true : text.back()!='\\');

                if (this_txt_is_end_of_string)
                {
                        text.pop_back();
                }                                                   

                //simple write
                if (stringmode){
                        say << text;
                        if (command.peek()==' ' and !this_txt_is_end_of_string){
                                say << ' ';
                        }
                }else
                {       //write value of variable
                        say << " [" << current_scope.displayVar(text) << "] ";
                }
                
                if (this_txt_is_end_of_string)
                        stringmode = false;
        }
        while (!command.eof());
}

void execution_jump(std::stringstream & command, int & line_index, std::vector<Balise> baliseliste)
{
        int new_pos = line_index;

        std::string jump_arg1, jump_arg2;
        command >> jump_arg1 >> jump_arg2;

        if (jump_arg1==SUBCOM_GOTO_ABSOLUTE)
        {
                int testnewline = stoi2(jump_arg2, NOLINE);
                if (testnewline==NOLINE)
                {
                        new_pos = find_balise(jump_arg2, baliseliste);
                }
                else //arg 2 is a number
                {
                        new_pos = testnewline -1 ;
                }
        }
        else if (jump_arg2==SUBCOM_GOTO_RELATIVE)
        {
                new_pos = line_index + stoi2(jump_arg1,-1);
        }

        //a new pos that go too far already end the code ✧ദ്ദി
        if (0<=new_pos)
                line_index = new_pos-1;
        
}

void execution_set(std::stringstream & command, Scope & current_scope){
        std::string new_var_name;
        command >> new_var_name;
        current_scope.add_default_var(new_var_name);
}









