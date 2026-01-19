#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>
#include "base_lib.hpp"
using namespace std;

    /*-----------------------------------------------*/
   /* ╦═╗ ╦═╕ ╦═╕ ╒╦╕ ╗═╗ ╒╦╕ ═╦═ ╒╦╕ ╔═╗ ╗═╗ ╔═╗   */
  /*  ║ ║ ╠═  ╠═   ║  ║ ║  ║   ║   ║  ║ ║ ║ ║ ╚═╗  */
 /*   ╩═╝ ╩═╛ ╝   ╘╩╛ ╩ ╩ ╘╩╛  ╩  ╘╩╛ ╚═╝ ╩ ╩ ╚═╝ */
/*-----------------------------------------------*/
//variable types as an enum
enum VarType : char {VARIABLE_REF, OPERATOR, NUMBER, STRINGPTR, BOOL, COORD, LIST, UNDEFINED};

struct Variable{
        VarType type;
        union Union_Value
        {
                double number;            
                bool boolean;
                float coord[2];
                int index;
                unsigned int list_ptrs[2]; //start ptrs and lenght in global list variable pool
                unsigned int stringptr[2]; //start ptrs and lenght in global char pool
        } value;

        Variable (){
                type = UNDEFINED;
                value.boolean = false;
        }
        Variable (double inumber){
                type = NUMBER;
                value.number = inumber;
        }
        Variable (float inx, float iny){
                type = COORD;
                value.coord[0] = inx;
                value.coord[1] = iny;
        }
        Variable (bool inbool){
                type = BOOL;
                value.boolean = inbool;
        }
        Variable (const string & intext){
                type = STRINGPTR;
                setstring(intext);
        }

        Variable (VarType _type, double n_value){
                type = _type;
                switch (type){
                        case VARIABLE_REF:
                                value.index = (int)(n_value);
                }
                
        }

        void setstring(const string & intext);//global.string_pool.add_string(intext, value.stringptr[0], value.stringptr[1]);

        string display(){
                switch (type)
                {
                case VARIABLE_REF:
                        return "VAR_REF, TODO";
                case NUMBER:
                        return to_string(value.number);
                case STRINGPTR:
                        return "-STRING-";
                case BOOL:
                        return value.boolean ? "True" : "False";
                case COORD:
                        return "<" + to_string(value.coord[0]) + " " + to_string(value.coord[1]) + ">";
                case LIST:
                        return "[A,B,C...]";
                default:
                        return "-UNDEFINED-";
                }
        }
};

//varpool

enum CommandType : char {PRINT, STOP, INPUT, SETVAR, PROCEDURECALL, UNKNOWNCOMMAND};

CommandType getCommand(const string & commandstr){
        if (commandstr == "say") return PRINT;
        else if (commandstr == "stop") return STOP;
        else if (commandstr == "input") return INPUT;
        else if (commandstr == "let") return SETVAR;
        return UNKNOWNCOMMAND;
}

struct Command{
        CommandType type = UNKNOWNCOMMAND;
        vector<Variable> args;

        Command(CommandType intype){
                type = intype;
        }
        Command(CommandType intype, Variable && inarg){
                type = intype;
                args.push_back(inarg);
        }
        Command(CommandType intype, const vector<Variable> & inargs){
                type = intype;
                for (Variable v : inargs){
                        args.push_back(v);
                }                
        }

        void add_arg(Variable && inarg){
                args.push_back(inarg);
        }
        void execute();
};

struct Global{
        struct StringPool
        {
                unsigned int last_char_index = 0;
                vector<char> charpool;

                void add_string(string instring, unsigned int & start, unsigned int & end){
                        int char_start = last_char_index+10;
                        last_char_index += instring.length();
                        charpool.reserve(last_char_index + instring.length());

                        for (int i=0; i<instring.length(); i++){
                                charpool[char_start+i] = instring[i];
                        }
                }
                void get_string(unsigned int start, unsigned int end, string & outstring){
                        outstring.reserve(end - start);
                        for (unsigned int i=start; i<end; i++){
                                outstring += charpool[i];
                        }
                }
        } string_pool;

        vector<Command> program;

        vector<Variable> variable_pool; 

        void add_program_command(Command && cmd){
                cout<<"2- adding command to program: "<<cmd.args[0].display()<<"\n";
                program.push_back(cmd);
                cout<<"3- just added command to program\n";
        }

        void execute_program(){
                cout<<"--- executing program ---"<<endl;
                for (Command & cmd : program){
                        cmd.execute();
                        cout<<"executed_code line"<<endl;
                }
                cout<<"--- finished executing program ---"<<endl;
        }
}global;

void Variable::setstring(const string & intext){
        global.string_pool.add_string(intext, value.stringptr[0], value.stringptr[1]);
}

    /*-------------------------------*/
   /* ╦═╗ ╦═╗ ╦═╗ ╔═╗ ╒╦╕ ╗═╗ ╔═╗   */
  /*  ╠═╝ ╠═╣ ╠═╝ ╚═╗  ║  ║ ║ ║ ╥  */
 /*   ╝   ╝ ╝ ╝ ╚ ╚═╝ ╘╩╛ ╩ ╩ ╚═╝ */
/*-------------------------------*/

//clean text from comments and blank lines
void get_file_text(vector<string> & filetext, string filename, string COMMENT, string BIGCOMMENT)
{
	ifstream file (filename);
	filetext.reserve(4);

	bool commentmode = false;
	string codeline;
	while (!file.eof()){
		getline(file, codeline);
		
		//do thing for big comment
		int commentstart = codeline.find(BIGCOMMENT);
		if (string_found(commentstart)){
			if (commentmode){ //end comment
                                commentmode = false;
                                codeline.erase(0, commentstart + BIGCOMMENT.length());
			}
			else{ //start comment
                                commentmode = true;
                                codeline.erase(commentstart, codeline.length()-commentstart);
                                filetext.push_back(codeline); //put line because it wont add it as its comment mode
                                continue;
                        }
		}
		else if (!commentmode){ //basic comment
			commentstart = codeline.find(COMMENT);
			if (string_found(commentstart))
                                codeline.erase(commentstart, codeline.length()-commentstart);
		}

                codeline = trim(codeline);

                if (!commentmode and codeline!="")
        		filetext.push_back(codeline);
	}
	file.close();
}

int get_var_index(const string & vartext){
        if (!start_with(vartext,"var[")) return -1;
        if (!end_with(vartext,"]")) return -2;
        string strnumber = "";
        //3 is the start of the number: v0 a1 r2 [3 --variable index-- ..]n
        for (int i=4; i<vartext.length()-1; i++){
                strnumber += vartext[i];
        }
        return stoi2(strnumber, -3);
}

//
void create_command(const string & commandline){
        string commandname = commandline.substr(0, commandline.find(" "));
        stringstream allargstr (commandline.substr(commandline.find(" ")+1, commandline.length()));
        string thisstr = "";
        vector<Variable> allargs;
        //Command cmd = ;//getCommand(commandname);
        //cmd.add_arg(Variable(allargs));
        //loop throug all arguments
        while (!allargstr.eof()){
                allargstr >> thisstr;
                int varindex = get_var_index(thisstr);
                if (0<=varindex){
                        allargs.push_back();
                }
        }

        global.add_program_command(Command(UNKNOWNCOMMAND,));
}

    /*-----------------------------------*/
   /* ╔═╗ ╔═╗ ╦╦╗ ╦╦╗ ╦═╗ ╗═╗ ╦═╗ ╔═╗   */
  /*  ║   ║ ║ ║╨║ ║╨║ ╠═╣ ║ ║ ║ ║ ╚═╗  */
 /*   ╚═╝ ╚═╝ ╩ ╩ ╩ ╩ ╝ ╝ ╩ ╩ ╩═╝ ╚═╝ */
/*-----------------------------------*/

void command_print(Command & cmd)
{
        for (Variable & var : cmd.args){
                cout << var.display() << " ";
        }
        cout << endl;
}

void command_error(Command & cmd)
{
       cout<<"\033[12m"<< cmd.args[0].display() <<"\033[0m"<<endl;
}

void command_setvar(Command & cmd)
{

}

void Command::execute()
{
        switch (type){
                case CommandType::PRINT:
                        command_print(*this);
                        break;
                default:
                        command_error(*this);
                        break;
        }    
}

    /*---------------------------------------------------------*/
   /* ╦╦╗ ╦═╗ ╒╦╕ ╗═╗   ╦═╕ ╗ ╗ ╦═╕ ╔═╗ ╗ ╗ ═╦═ ╒╦╕ ╔═╗ ╗═╗   */
  /*  ║╨║ ╠═╣  ║  ║ ║   ╠═  ╓\╜ ╠═  ║   ║ ║  ║   ║  ║ ║ ║ ║  */
 /*   ╩ ╩ ╝ ╝ ╘╩╛ ╩ ╩   ╩═╛ ╝ ╝ ╩═╛ ╚═╝ ╚═╝  ╩  ╘╩╛ ╚═╝ ╩ ╩ */
/*---------------------------------------------------------*/
int main(){
        /*
	vector<string> filetext;
	get_file_text(filetext, "main.atl", "#", "###");

        int i=0;
        //just display the cleaned text
        cout << "---- code ----" << endl;
        for (string line : filetext){
                cout << "line " << i << ":" << line << endl;
                i++;
	}
        cout << "---- tokenification ----" << endl;
	for (string line : filetext){
		create_command(line);
                cout << i << "created command from:" << line << endl;
                i++;
	}
        cout << "---- execution ----" << endl;
        global.execute_program();//*/

        return 0;
}