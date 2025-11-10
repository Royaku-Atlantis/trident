#include <iostream>
#include <fstream>
#include "lib.h"
using namespace std;

#define filename "joemama.txt"

void execute(string command, fileread& filer){
        if (command == "say"){
                bool stringmode = false;
                string text;
                
                while (!is_end_of_line(filer))
                {
                        filer >> text;
                        //check if lastchar is ", and not \", but check if only 1 char (no \" possible)
                        if (!stringmode and text[0]=='"')
                        {
                                stringmode = true;
                                text[0] = '\0';
                        } 
                        bool this_txt_is_end_of_string = (stringmode) and last_char(text)=='"' and
                                (text.length()==1 ? true : last_char(text,1)!='\\');

                        if (this_txt_is_end_of_string)
                        {
                                rm_last_char(text);
                        }                                                   

                        if (stringmode){
                                //simple write
                                say << text;
                                if (filer.peek()==' '){
                                        say << ' ';
                                }
                        }else{
                                say << " -[" << text << "]- ";
                        }
                               
                        if (this_txt_is_end_of_string)
                        {
                                stringmode = false;
                        }

                        getch();
                }
        }
        else
        {
                string uncommanded_text = command;
                say << "\n \"" << command << "is not a recognised command: \n";
                do
                {
                        say << uncommanded_text;
                        filer >> uncommanded_text;
                        getch();
                }
                while (!is_end_of_line(filer));
                say << "\n Continuation of the program :\n";
                
        }
}
//if (A[A.length()]==';')



int main()
{
        //*
        fileread filer;
        filer.open(filename);
        
        string command = "";
        
        while (!filer.eof()){
                filer >> command;
                execute(command, filer);
                
        }//*/

        getch();
        return 0;
}