#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <tgmath.h> //only for modulo yet lmfao

using namespace std;


//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝

      /*--------------------------------------------------------------*/
     /* ╦═╗ ╔═╗ ╔═╗ ╒╦╕ ╔═╗   ╦═╕ ╗ ╗ ╗═╗ ╔═╗ ═╦═ ╒╦╕ ╔═╗ ╗═╗ ╔═╗    */
    /*  ╠═╣ ╠═╣ ╚═╗  ║  ║     ╠═  ║ ║ ║ ║ ║    ║   ║  ║ ║ ║ ║ ╚═╗   */
   /*   ╩═╝ ╝ ╝ ╚═╝ ╘╩╛ ╚═╝   ╝   ╚═╝ ╩ ╩ ╚═╝  ╩  ╘╩╛ ╚═╝ ╩ ╩ ╚═╝  */
  /*--------------------------------------------------------------*/

/* FROM MY CONSOLE GRAPHIC LIBRARY */
#define RED 31  //red     31   41
#define YELLOW 33  //yellow  33   43
#define GREEN 32   //green   32   42
#define CYAN 36  //cyan    36   46
#define BLUE 34  //blue    34   44
#define MAGENTA 35  //magenta 35   45
#define WHITE 37  //white   37   47
#define BLACK 30  //black   30   40
#define DARK 30
enum textStatus {TXT_DEFAULT, TXT_BOLD, TXT_DARKER, TXT_idk1, TXT_UNDERLINED, TXT_idk5, TXT_idk6, TXT_SETBACKGROUND, TXT_idk8, TXT_STRIKETHROUGH};
void setText(textStatus hexmode, int color=-1){
    if (color==-1)      cout<<"\033["<<hexmode<<'m';
    else                cout<<"\033["<<hexmode<<';'<<color<<'m';
}
/* ------------------------------ */

char getlastchar(string str){
        if (str.size()==0) return '\n';
        return str.back();
}

float randomf_mono(){
        return (float) rand() / (float) RAND_MAX; 
}
template <typename t>
void swap_direct(t & a, t & b){
        t c = a;
        a = b;
        b = c;
}

float randrange(float mini, float maxi){
        if (mini>maxi)
                swap_direct(maxi, mini);
        float randrange = (maxi - mini);
        randrange *= randomf_mono();
        randrange += mini;
        return randrange;
}

bool is_stof_valid(string toconvert){
        try {
                int res = std::stof(toconvert);
        }
        catch (...) {
                return false;
        }
        return true;
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



      /*----------------------------------------------------------------------*/
     /* ╔═╗ ╦   ╦═╗ ╔═╗ ╔═╗   ╦═╗ ╦═╕ ╦═╕ ╒╦╕ ╗═╗ ╒╦╕ ═╦═ ╒╦╕ ╔═╗ ╗═╗ ╔═╗    */
    /*  ║   ║   ╠═╣ ╚═╗ ╚═╗   ║ ║ ╠═  ╠═   ║  ║ ║  ║   ║   ║  ║ ║ ║ ║ ╚═╗   */
   /*   ╚═╝ ╩═╛ ╝ ╝ ╚═╝ ╚═╝   ╩═╝ ╩═╛ ╝   ╘╩╛ ╩ ╩ ╘╩╛  ╩  ╘╩╛ ╚═╝ ╩ ╩ ╚═╝  */
  /*----------------------------------------------------------------------*/

struct balise{
        string name;
        int linetogo;

        balise (string bname,int bline){
                name = bname; linetogo = bline;
        }
};

int search_balise_line(string varname, vector<balise> listofbalise){
        for (int i=0; i<listofbalise.size(); i++){
                if (listofbalise[i].name == varname)
                        return listofbalise[i].linetogo;
        }
        return -1;
}

typedef unsigned char Byte;

#define UNDEF 0x00
#define DEF 0xFF
#define DEFBOOL 0xF0 //tochange
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
                else if (status==DEFBOOL){
                        setText(TXT_BOLD,BLUE);
                        if (value)
                                cout<<"True";
                        else    cout<<"False";
                }
                else{
                        setText(TXT_BOLD,CYAN);
                        cout<<value;
                }
        }
};

string clean_varname(string varname){
        if (varname.back()=='{'){
                return varname.erase(varname.size()-1, 1);
        }
        return varname;
}

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
                varname = clean_varname(varname);
                varlist.push_back(vardata (varname, value, status));
        }

        int search_index(string varname){
                varname = clean_varname(varname);
                for (int i=0; i<varlist.size(); i++){
                        if (varlist[i].varname == varname)
                                return i;
                }
                return -1;
        }
};



float getvalue(string strdata, map & variables, bool create_ifnotexist = false, float default_value=0){
        if (is_stof_valid(strdata)){
                return (float) stof(strdata);
        }
        else{
                vardata variable = variables.getvar(strdata, create_ifnotexist);
                if (variable.status == UNDEF){
                        return default_value;
                }
                        return variable.value;
        }
}


        //gotonext_endof_loop(i, codelines, numb_of_lines);
void gotonext_endof_loop(int & i,const vector<string> & codelines, int numb_of_lines){
        unsigned int withinloop = 1;
        while (!withinloop and i<numb_of_lines){
                i++;
                if (stringcontain(codelines[i],"{"))
                        withinloop ++;
                if (stringcontain(codelines[i],"}"))
                        withinloop --;
        }
}
/*
        //gotonext_endof_loop(i, codelines, numb_of_lines);
void gotonext_endof_loop(int & i,const vector<string> & codelines, int numb_of_lines){
        bool thisIsFinalLine = stringcontain(codelines[i],"}") or stringcontain(codelines[i],"endif") 
                        or stringcontain(codelines[i],"else") or (numb_of_lines<=i);

        while (!thisIsFinalLine){
                i++;
                thisIsFinalLine = stringcontain(codelines[i],"}") or stringcontain(codelines[i],"endif") 
                                        or stringcontain(codelines[i],"else") or (numb_of_lines<=i);
        }
}
*/


    /*---------------------------------------------------------*/
   /* ╦╦╗ ╦═╗ ╒╦╕ ╗═╗   ╦═╕ ╗ ╔ ╦═╕ ╔═╗ ╗ ╗ ═╦═ ╒╦╕ ╔═╗ ╗═╗   */
  /*  ║╨║ ╠═╣  ║  ║ ║   ╠═  ╚╪╗ ╠═  ║   ║ ║  ║   ║  ║ ║ ║ ║  */
 /*   ╩ ╩ ╝ ╝ ╘╩╛ ╩ ╩   ╩═╛ ╝ ╚ ╩═╛ ╚═╝ ╚═╝  ╩  ╘╩╛ ╚═╝ ╩ ╩ */
/*---------------------------------------------------------*/

int main(){

        setText(TXT_DEFAULT);
        ifstream file;
        vector<string> codelines;
        bool debug_enable = false;

        file.open("main.atl");
        int numb_of_lines = 0;
        bool isBigCommentMode = false;

        vector<balise> list_of_balises;

          /*---------------*/
         /*   FILE LOOP   */
        /*---------------*/
        while (!file.eof())
        {
                string thisline;
                getline(file,thisline);

                if (isBigCommentMode)   codelines.push_back("");
                else                    codelines.push_back(remove_comment(thisline));

                stringstream thislinestream (thisline);
                string checkbalise;
                thislinestream >> checkbalise;
                if (checkbalise=="balise" and !thislinestream.eof()){
                        thislinestream >> checkbalise;
                        if (search_balise_line(checkbalise, list_of_balises) == -1)
                                list_of_balises.push_back( balise (checkbalise, numb_of_lines) );
                }

                if (stringcontain(thisline,"###"))
                        isBigCommentMode = !isBigCommentMode;

                numb_of_lines ++;
        }
        file.close();
        cout<<endl;

        //cout<<" boutasse "<<numb_of_lines<<endl;

        map variables;
        vector<float> calculator;


          /*----------------*/
         /*   EXECUTIONS   */
        /*----------------*/

        bool in_if_loop = false;
        unsigned int iterator = 0;
        int repeatline = -1;

        for (int i=0; i<numb_of_lines; i++)
        {
                stringstream thisline (codelines[i]);
                string str;
                thisline >> str;

                if (str[0]=='#' or str[0]==' ' or str=="") continue;
                //input add subtract multip divise modulo and or not max min inferior superior equal
                else if (str=="say")
                {
                        bool stringmode = false;

                        while (!thisline.eof()){
                                thisline>>str;
                                
                                if (str=="endl"){
                                        cout<<endl;
                                        continue;
                                }
                                bool startstringmode = str[0]=='"';
                                bool endstringmode = getlastchar(str)=='"';

                                //for lone quotes
                                if (startstringmode and endstringmode and str.size()==1){
                                        stringmode = !stringmode;
                                        if (stringmode) cout<<' ';
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
                        else if (str=="true"){
                                variables.setvar(false, varname, 1, DEFBOOL);
                        }
                        else if (str=="false"){
                                variables.setvar(false, varname, 0, DEFBOOL);
                        }
                        else if (is_stof_valid(str)){
                                variables.setvar(true, varname, stof(str), DEF);
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
                        setText(TXT_DEFAULT);
                        bool skipLoop;
                        string str, arg2;
                        thisline >> str;
                        if (!thisline.eof()){
                                thisline >> arg2;
                                if (arg2 != "{")
                                        skipLoop = getvalue(str, variables) != getvalue(arg2, variables);
                                else
                                        skipLoop = getvalue(str, variables) == 0;
                        }
                        else
                                skipLoop = getvalue(str, variables) == 0;

                        if (skipLoop){
                                gotonext_endof_loop(i, codelines, numb_of_lines);
                        }else{
                                in_if_loop = true;
                        }
                }
                else if (str=="repeat"){
                        string numberofiteration;
                        thisline >> numberofiteration;

                        float temp = getvalue(numberofiteration, variables);
                        unsigned int itnumb;
                        if (temp<=0) itnumb=-1;
                        else itnumb = temp;

                        if (itnumb!=-1){
                                iterator = itnumb;
                                repeatline =  i;
                        }else{
                                setText(TXT_DEFAULT,RED);
                                cout << "error:  repat loop have invalid value (at line "<<i<<")\n";
                                gotonext_endof_loop(i, codelines, numb_of_lines);
                        }
                }
                else if (str=="continue"){
                        thisline >> str;
                        if (getvalue(str,variables) and iterator>0 and repeatline>0)
                                i=repeatline;
                }
                else if (str=="break"){
                        thisline >> str;
                        if (getvalue(str,variables) and iterator>0 and repeatline>0){
                                repeatline = -1;        
                                gotonext_endof_loop(i, codelines, numb_of_lines);
                        }
                }
                else if (str=="input"){
                        setText(TXT_BOLD,GREEN);
                        while (!thisline.eof()){
                                cout<<"LASTREAD:"<<str<<"_eof:"<<thisline.eof();
                                thisline >> str;
                                cout<<"_NOWREAD:"<<str<<"_eof:"<<thisline.eof()<<endl;
                                string newval;
                                cin >> newval;
                                if (is_stof_valid(newval))
                                        variables.setvar(true, str, stof(newval),DEF);
                                else
                                        variables.setvar(false, str, -1,DEF);
                        }
                }
                else if (str=="jump"){
                        if (!thisline.eof()){
                                thisline >> str;
                                int linetogo = search_balise_line(str,list_of_balises);
                                if (linetogo != -1)
                                        i = linetogo;
                        }
                }
                else if (str=="add"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) + getvalue(arg2, variables);
                        variables.setvar(true, varname, res, DEF);
                }
                else if (str=="subtract"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) - getvalue(arg2, variables);
                        variables.setvar(true, varname, res);
                }
                else if (str=="multip"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) * getvalue(arg2, variables);
                        variables.setvar(true, varname, res);
                }
                else if (str=="divide"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float arg2val = getvalue(arg2, variables);

                        if (getvalue(arg2, variables)==0){
                                variables.setvar(true, varname, 0, UNDEF);
                        }else{
                                float res = getvalue(arg1, variables) / arg2val;
                                variables.setvar(true, varname, res);
                        }
                }else if (str=="modulo"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float arg2val = getvalue(arg2, variables);

                        if (getvalue(arg2, variables)==0){
                                variables.setvar(true, varname, 0, UNDEF);
                        }else{
                                float res = fmod(getvalue(arg1, variables), arg2val);
                                variables.setvar(true, varname, res);
                        }
                }else if (str=="and"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) and getvalue(arg2, variables);
                        variables.setvar(true, varname, res, DEFBOOL);
                }else if (str=="or"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) or getvalue(arg2, variables);
                        variables.setvar(true, varname, res, DEFBOOL);
                }
                else if (str=="not"){
                        string varname, arg1;
                        thisline >> varname >> arg1;
                        float res = getvalue(arg1, variables);
                        if (res==0)
                                variables.setvar(true, varname, 1, DEFBOOL);
                        else
                                variables.setvar(true, varname, 0, DEFBOOL); 
                }else if (str=="max"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = max(getvalue(arg1, variables), getvalue(arg2, variables));
                        variables.setvar(true, varname, res);
                }else if (str=="min"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = min(getvalue(arg1, variables), getvalue(arg2, variables));
                        variables.setvar(true, varname, res);
                }
                else if (str=="inferior"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) < getvalue(arg2, variables);
                        variables.setvar(true, varname, res, DEFBOOL);
                }
                else if (str=="superior"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) > getvalue(arg2, variables);
                        variables.setvar(true, varname, res, DEFBOOL);
                }
                else if (str=="equal"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1 >> arg2;
                        float res = getvalue(arg1, variables) == getvalue(arg2, variables);
                        variables.setvar(true, varname, res, DEFBOOL);
                }
                else if (str=="inequal"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1;
                        float res = getvalue(arg1, variables) != getvalue(arg2, variables);
                        variables.setvar(true, varname, res, DEFBOOL);
                }
                else if (str=="else"){
                        if (in_if_loop){
                                in_if_loop = false;
                                gotonext_endof_loop(i, codelines, numb_of_lines);
                        }
                        else{
                                setText(TXT_DEFAULT,RED);
                                cout<<"error: else not connected to 'if' at line "<<i<<endl;
                        }
                        
                }
                else if (str=="round"){
                        string varname, arg1;
                        thisline >> varname >> arg1;
                        thisline >> arg1;
                        float res = getvalue(arg1, variables);
                        variables.setvar(true, varname, round(res), DEF);
                }
                else if (str=="random"){
                        string varname, arg1, arg2;
                        thisline >> varname >> arg1;
                        if (thisline.eof()){
                                float res = getvalue(arg1, variables);
                                res = randrange(0, res);
                                variables.setvar(true, varname, res, DEF);
                        }else{
                                thisline >> arg2;
                                float mini = getvalue(arg1, variables);
                                float maxi = getvalue(arg2, variables);
                                maxi = randrange(mini, maxi);
                                variables.setvar(true, varname, maxi, DEF);  
                        }
                }
                else if (str=="endl"){
                        cout<<endl;
                }
                else if (str=="endif" or str=="}"){
                        
                        if (iterator>1){
                                iterator --;
                                i = repeatline;
                        }else{
                                iterator = 0;
                                repeatline = -1;
                        }
                }
                else if (str!="{" and str!="balise"){
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
        getch();
        return 0;
}