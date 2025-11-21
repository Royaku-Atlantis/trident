#include "lib_basic.hpp"
#include "lib_trident_definitions.hpp"
#include "lib_trident_executes.hpp"
using namespace std;

int main(){
        //ifstream codefile;
        //codefile.open();
        vector<Token> saylist = {Token(), Token(69.420), Token("kakou")};

        cout<<"HELLO WORLD :";
        cout<<(int)saylist[1].token_type;

        execute_say(saylist);
}