#include <iostream>
#include <fstream>
#include <sstream>
#include "lib.h"
using namespace std;

#define filename "joemama.txt"


#define VAR_NUMBER 0xF0
#define VAR_TEXT 0xFF
#define VAR_UNDEF 0x00
class Variable{
public:
        Variable (){
                name = "";
        }
        Variable (std::string varname){
                name = varname;
                state = VAR_UNDEF;
        }
        bool is_name(std::string name_to_find){
                return name==name_to_find;
        }

        void set_string(std::string newtext){
                state = VAR_TEXT;
                text_value = newtext;
                numeric_value = 0;
        }
        void set_number(float newnumber){
                state = VAR_UNDEF;
                numeric_value = newnumber;
                text_value = "";
        }

        void number_to_string(){
                state = VAR_TEXT;
                text_value = std::to_string(numeric_value);
        }
        void string_to_number(){
                state = VAR_NUMBER;
        }

private:
        std::string name;
        char state = VAR_UNDEF;
        float numeric_value = 0;
        std::string text_value = "";
};

class VarList{
public:
        unsigned int capacite;
        unsigned int var_numb;
        Variable * ad;

        VarList (){
                ad = new Variable [1];
                capacite = 1;
                var_numb = 0;
        }
        ~VarList (){
                delete[] ad;    
        }
        void append(Variable e) {
        if (var_numb == capacite) { // tableau plein, on double la capacité
                Variable * temp = ad;
                ad = new Variable [2*capacite];
                capacite *= 2;
                for (unsigned int i = 0; i < var_numb; i++) ad[i] = temp[i];
                delete [] temp;
                }
                ad[var_numb] = e;
                var_numb++;
        }

        Variable get_var(unsigned int indice){
                if (var_numb <= indice)
                        throw "unsufficent check for VarList : get_var";
                return ad[indice];
        }
};








/* string command line to be executed | line index, to change with ifs and jumps*/
void execute(string command_line, int & line_index)
{
        if (command_line=="") return;
        
        stringstream code_line (command_line);
        string command_name;
        code_line >> command_name;

        if (command_name == COMMAND_PRINT)
        {
                execution_say(code_line);
                say << endl;
        }
        else if (command_name == COMMAND_GOTO)
        {
                // "lineindex +1" because its start at 0 in code, but 1 in ide
                say << "Jump Called, from line " << line_index+1;
                execution_jump(code_line, line_index);
                say << " to line " << line_index+2 << endl;
                //show +2 because it will increment next line execution
        }
        else{
                say << "\nError invalid command at line "<< line_index+1 <<": \"" << command_line << " \"\n";
        }
}

int main()
{
        //*
        fileread filer;
        filer.open(filename);
        
        string command = "";
        CodeList lines_of_codes;

        while (!filer.eof()){
                getline(filer, command);
                command = clean_command(command);
                lines_of_codes.append(command);
        }
        cout << "there are "<< lines_of_codes.str_numb << " lines of code \n";

        for (int line_index=0; line_index < lines_of_codes.str_numb ; line_index++){
                /*if (lines_of_codes.get_line(i).empty())
                        cout << "ENPTY LINE";
                cout << lines_of_codes.get_line(i) << endl;//*/
                execute(lines_of_codes.get_line(line_index), line_index);
                getch();
        }
        //stringstream ss(str);
        getch();
        return 0;
}