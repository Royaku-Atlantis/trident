#include <iostream>
#include <fstream>
using namespace std;
#define MAXINCORRECTPASSWORD 5
#define STR_SEPARATOR1   "\033[0m-----------------------------------------------"
#define STR_SEPARATOR2 "\n\033[0m===============================================\n"
/////////////////////////////////////////////////////////
///////////////// BASIC FUNCS

string input(const string & saytext="in"){
    cout << saytext << ":\033[34m" ;//underlined bold blue_text
    string smth;
    cin>>smth;
    return smth;
}
void say(const string & saytext){
    cout << saytext << endl ;
}

/////////////////////////////////////////////////////////
/////////////////// MICRO ELEMENT

#define NMIN 32
#define NMAX 126
#define NRANGE NMAX - NMIN +1
int periodichar(int source, int offset){
    source += offset;
    while(NMAX < source){
        source -= NRANGE;
    }
    while(source < NMIN){
        source += NRANGE;
    }
    return source;
}

#define NLCHAR '\0'
char encode(char data, char encode){
    if (data=='\n' or data=='\r') return NLCHAR;
    return periodichar(data,encode);
}
char decode(char data, char encode){
    if (data==NLCHAR) return '\n';
    return periodichar(data,-encode);
}

char key_get_offset(const string & key, int i){
    i %= key.length();
    return key[i];
}

/////////////////////////////////////////////////////////
/////////////////// MACRO ELEMENT

string encodeTxt(const string & text, const string & key){
    string encodedtext = "";
    for (int i=0; i<text.length(); i++){
        encodedtext += encode(text[i],key_get_offset(key,i));
    }
    return encodedtext;
}
string decodeTxt(const string & codedtext, const string & key){
    string decodedtext = "";
    for (int i=0; i<codedtext.length(); i++){
        decodedtext += decode(codedtext[i],key_get_offset(key,i));
    }
    return decodedtext;
}

void get_file_text(string & filedata, string filename){
    ifstream file(filename, fstream::binary);

    //read raw file and store in filedata
    filedata = "";
    string intxt = "";
    while (!file.eof()){
        getline(file,intxt);
        //if (!file.eof()) intxt += '\n';
        filedata += intxt;
    }
    file.close();
}

bool is_password_correct(const string & password,const string & filedata){
    int pslen = password.length();
    for(int i=0; i<pslen; i++){
        if (password[i] != decode(filedata[i],password[i]))
            return false;
    }
    return true;
}

/////////////////////////////////////////////////////////
/////////////////// MAIN ELEMENT

int main(){
    string filename = "";

    do{
        fstream file;
        do{
            //text to inform that the filename was invalid
                                /*underlined magenta_text*/       /* red_text*/
            if (filename!="")  cout<<"\033[31m\"\033[35m"<<filename<<"\033[31m\" not found. Enter a valid file name, or '\033[0mstop\033[31m' to close the program\n";
            filename = input("\033[0mfile to open");

            if (filename=="stop") break; //to stop the program from an infinit loop
            file.open(filename);

        }while (file.fail());

        if (filename=="stop") break; //to get the info about stopping the infinit loop
                /*Blue_text*/ /*underlined cyan_text*/ /*Blue_text*/
        cout <<"\033[0mFile \"\033[4;36m"<<filename<<"\033[0m\" found."<<endl;
        file.close(); //close for now, we will open it as ofstream or ifstream accordingly later

        string whatToDo="";
        do{
            if (whatToDo!="")
                    /*red_text*/      /*bold white*//*red_text*/   /*bold white*//*red_text*/
                say("\033[31mplease type \033[1;37mR\033[31m or \033[1;37mW\033[31m");
                            /*default*/  /*bold white*/ /*default*/    /*bold white*/ /*default*/
            whatToDo = input("\033[0mDo You want to Read? (\033[1;32mR\033[0m) or Encode? (\033[1;32mW\033[0m)");
        }while (whatToDo!="R" and whatToDo!="W");

        //get file data to read or encode
        
        if (whatToDo=="R")
        {

            string fullfile = "";
            ifstream file(filename);
            getline(file,fullfile);
            file.close();

            string password;
            for (int i=5; -1<=i ; i--)
            {
                if (i<0) throw "too many mistakes"; 

                password = input("\033[0menter the password");
                //if the password accurately decode itself
                if (is_password_correct(password,fullfile))
                {
                    fullfile = decodeTxt(fullfile,password);                    
                    //show without the password header
                    cout<<STR_SEPARATOR1<<endl<<"\033[33m"<< fullfile.erase(0,password.length())<<endl<<STR_SEPARATOR1;
                    break;
                }
                else cout<<"\033[31mIncorrect password, "<<i<<" attempts left\n";
            }            
        }
        else
        if (whatToDo=="W"){

            string fullfile = "";
            get_file_text(fullfile, filename);

            string password = input("create the password");
            string newfile = password + fullfile;
            newfile = encodeTxt(newfile,password);

            ofstream file (filename);
            file << newfile;
            file.close();

            cout<<"\033[4;36m"<<filename;
            say("\033[0m was encoded by the password.");
        }
        filename = "";
        cout<<endl<<STR_SEPARATOR2;
    
    }while(filename!="stop");
    cout<<endl<<STR_SEPARATOR2;
    cout<<"end of the program";
    cout<<endl<<STR_SEPARATOR1;
    return 0; //32 - 126 include
}