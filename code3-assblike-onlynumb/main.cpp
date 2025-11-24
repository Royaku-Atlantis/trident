#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
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

        string printval(){
                if (status==UNDEF)
                        return "<"+varname+" is Undefined>";
                else
                        return to_string(value);
        }
};

struct map{
        vector<vardata> varlist;

        vardata getvar(string varname){
                int index = search_index(varname);
                if (index==-1)
                {
                        createvar(varname, 0, UNDEF);
                        return varlist.back();
                }
                else
                        return varlist[index];
        }
        void setvar(string varname, vardata var)
        {
                int index = search_index(varname);
                if (index==-1)
                        createvar(var.varname, var.value, var.status);
                else
                        varlist[index] = var; 
        }
        string getvarstr(string varname){
                vardata vartoget = getvar(varname);
                return vartoget.printval();
        }
        bool var_exist(string varname){
                return search_index(varname)!=-1;
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
        ifstream file;
        vector<string> codelines;

        file.open("blabla.txt");
        int numb_of_lines = 0;
        while (!file.eof())
        {
                string thisline;
                getline(file,thisline);
                codelines.push_back(thisline);
                numb_of_lines ++;
        }
        file.close();

        //cout<<" boutasse "<<numb_of_lines<<endl;

        map variables;
        vector<float> calculator;

        for (int i=0; i<numb_of_lines; i++)
        {
                stringstream thisline (codelines[i]);
                string str;
                thisline >> str;

                if (str[0]=='#' or str[0]==' ') continue;

                else if (str=="say")
                {
                        bool stringmode = false;

                        while (!thisline.eof()){
                                thisline>>str;
                                
                                bool startstringmode = str[0]=='"';
                                bool endstringmode = getlastchar(str)=='"';

                                if (endstringmode)
                                                str.erase(str.size()-1,1);
                                if (startstringmode){
                                        stringmode = true;
                                        str.erase(0,1);
                                }

                                if (stringmode){
                                        cout<<str;
                                        if (!endstringmode) 
                                                cout<<' ';
                                }        
                                else cout<<variables.getvarstr(str);

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
                                variables.setvar(varname, vardata (varname, 0, UNDEF));
                        }
                        else if (is_number(str[0])){
                                variables.setvar(varname, vardata (varname, stoi(str), DEF));
                        }
                        else if (variables.var_exist(str)){
                                variables.setvar(varname, variables.getvar(str));
                        }
                        else{
                                //variables.setvar(varname, vardata (varname, stoi(str), DEF));
                        }

                        
                }
        }

        cout<<"\n end of exectuion";
        return 0;
}
