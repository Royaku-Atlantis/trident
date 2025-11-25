#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "console_graphic.hpp"

using namespace std;

typedef unsigned char Byte;

#define UNDEF 0x00
#define DEF 0xFF

char getlastchar(string str){
        if (str.size()==0) return '\n';
        return str.back();
}

bool is_number(char firstchar){
        return firstchar <= '9' and firstchar >= '0';
}

bool stringcontain(const string & bigstring,const string & substring){
       return bigstring.find(substring)!=string::npos ;
}
string remove_comment(string codeline){
        if (codeline.size()==0) return "";
        int commentStartIndex = codeline.find("#");
        if (commentStartIndex != string::npos)
                return codeline.erase(commentStartIndex, codeline.size()-commentStartIndex);
        return codeline;
}


struct vardata{
        string varname;
        float value;
        Byte status=UNDEF;  
        
        vardata(string varn){
                varname = varn;
                value = 0;
                status = UNDEF;
        }
        vardata (string varn, float val, Byte etat){
                varname = varn; value = val; status = etat;
        }

        void printval(){
                if (status==UNDEF){
                        setText(TXT_STRIKETHROUGH,RED);
                        cout<<' '<<varname<<' ';
                }
                else{
                        setText(TXT_BOLD,CYAN);
                        cout<<value;
                }
        }
};

struct map{
        vector<vardata> varlist;

        vardata getvar(string varname,bool create_if_dont_exist=true){
                int index = search_index(varname);
                if (index==-1 and create_if_dont_exist)
                {
                        createvar(varname, 0, UNDEF);
                        return varlist.back();
                }
                else if (var_index_is_valid(index))
                        return varlist[index];
                return vardata (varname, 0, UNDEF);
        }
        void setvar(bool create_if_dont_exist, string varname, float value, Byte status=DEF)
        {
                int index = search_index(varname);
                if (index==-1 and create_if_dont_exist)
                        createvar(varname, value, status);
                else if (var_index_is_valid(index))
                {
                        varlist[index].status = status;
                        varlist[index].value = value;
                }          
        }
        
        void printval(string varname, bool create_if_dont_exist=true){
                vardata vartoget = getvar(varname,create_if_dont_exist);
                vartoget.printval();
        }
        bool var_exist(string varname){
                return search_index(varname)!=-1;
        }
        bool var_index_is_valid(int varindex){
                return varindex!=-1 and varindex < varlist.size();
        }
private:
        void createvar(string varname, float value, Byte status){
                varlist.push_back(vardata (varname, value, status));
        }

        int search_index(string varname){
                for (int i=0; i<varlist.size(); i++){
                        if (varlist[i].varname == varname)
                                return i;
                }
                return -1;
        }
};

int main(){

        setText(TXT_DEFAULT);
        ifstream file;
        vector<string> codelines;
        bool debug_enable = false;

        file.open("main.atl");
        int numb_of_lines = 0;
        bool isBigCommentMode = false;

        while (!file.eof())
        {
                string thisline;
                getline(file,thisline);

                if (isBigCommentMode)   codelines.push_back("");
                else                    codelines.push_back(remove_comment(thisline));

                if (stringcontain(thisline,"###"))
                        isBigCommentMode = !isBigCommentMode;

                numb_of_lines ++;
        }
        file.close();
        cout<<endl;

        //cout<<" boutasse "<<numb_of_lines<<endl;

        map variables;
        vector<float> calculator;

        for (int i=0; i<numb_of_lines; i++)
        {
                stringstream thisline (codelines[i]);
                string str;
                thisline >> str;

                if (str[0]=='#' or str[0]==' ' or str=="") continue;

                else if (str=="say")
                {
                        bool stringmode = false;

                        while (!thisline.eof()){
                                thisline>>str;
                                
                                bool startstringmode = str[0]=='"';
                                bool endstringmode = getlastchar(str)=='"';

                                //for lone quotes
                                if (startstringmode and endstringmode and str.size()==1){
                                        stringmode = !stringmode;
                                        cout<<' ';
                                        continue;
                                }
                                else if (endstringmode)
                                        str.erase(str.size()-1,1);
                                if (startstringmode){
                                        stringmode = true;
                                        str.erase(0,1);
                                }

                                if (stringmode){
                                        setText(TXT_DEFAULT,YELLOW);
                                        cout<<str;
                                        if (!endstringmode) 
                                                cout<<' ';
                                }        
                                else{
                                        variables.printval(str);
                                }
                                if (endstringmode) 
                                        stringmode = false;//*/
                        }
                        cout<<"\n";
                }
                else if (str=="set")
                {
                        //(string varn, float val, Byte etat)
                        string varname;
                        thisline >> varname >> str;

                        Byte status;
                        float varvalue;

                        if (str=="UNDEF"){
                                variables.setvar(false, varname, 0, UNDEF);
                        }
                        else if (is_number(str[0])){
                                variables.setvar(true, varname, stoi(str), DEF);
                        }
                        else{
                                vardata varsource = variables.getvar(str, false);
                                variables.setvar(true, varname, varsource.value, varsource.status);
                        }
                }
                else if (str=="debug"){
                        thisline >> str;
                        if (str=="disable"){
                                debug_enable = false;
                        }else{
                                debug_enable = true;
                                setText(TXT_DEFAULT);
                                cout<<"-- Enabeled Debug lines\n";   
                        }
                        
                }
                else if (str=="if")
                {
                        string str;
                        thisline >> str;
                        bool skipLoop;
                        if (str=="UNDEF"){
                                skipLoop = true;
                        }
                        else if (is_number(str[0])){
                                skipLoop = stoi(str) == 0;
                        }
                        else{
                                skipLoop = 0 == variables.getvar(str, false).value;
                        }

                        if (skipLoop){

                                bool thisIsFinalLine = stringcontain(codelines[i],"}") or stringcontain(codelines[i],"endif") or (numb_of_lines<=i);
                                
                                while (!thisIsFinalLine){
                                        i++;
                                        thisIsFinalLine = stringcontain(codelines[i],"}") or stringcontain(codelines[i],"endif") or (numb_of_lines<=i);
                                }
                        }
                }
                else{
                        setText(TXT_DEFAULT,RED);
                        cout<<"Error, command: \"";
                        setText(TXT_STRIKETHROUGH);
                        cout<<codelines[i];
                        setText(TXT_DEFAULT,RED);
                        cout<<"\" at line "<<i<<endl;
                }
        }
        setText(TXT_DEFAULT);
        cout<<"\n end of exectuion";
        return 0;
}
