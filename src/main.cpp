#include "trident.hpp"
using namespace std;

/*
╦═╗ ╦═╗ ╔═╗ ╦═╗ ╦═╕ ╦═╕ ╔═╗ ╗ ╗ ╒╦╕ ║ ╔ ╦   ╦╦╗ ╗═╗ ╔═╗ ╦═╗ ╔═╗ ╦═╗ ╔═╗ ═╦═ ╗ ╗ ╗ ╗ ╗ ╗ ╗ ╔ ╗ ╗ ══╦
╠═╣ ╠═╣ ║   ║ ║ ╠═  ╠═  ║ ╥ ╠═╣  ║  ╠═╗ ║   ║╨║ ║ ║ ║ ║ ╠═╝ ║ ║ ╠═╝ ╚═╗  ║  ║ ║ ║ ║ ║╥║ ╚╪╗ ╚╦╝  /
╝ ╝ ╩═╝ ╚═╝ ╩═╝ ╩═╛ ╝   ╚═╝ ╝ ╝ ╘╩╛ ╝ ╚ ╩═╛ ╩ ╩ ╩ ╩ ╚═╝ ╝   ╚═╣ ╝ ╚ ╚═╝  ╩  ╚═╝  V  ╚╩╝ ╝ ╚  ╩  ╩══
╔═╗╔╗ ╔═╗╔═╗╓ ╓╔═╕╔═╗╔═╗╔═╗╔═╗
║ ║ ║  /  ═╣╚═╣╚═╗╠═╗  ║╠═╣╚═╣
╚═╝╘╩╛╩═╛╚═╝  ╩╚═╝╚═╝  ╜╚═╝╚═╝
*/

int main(int argc, char ** args)
{
        cout << "\033[0m";
        /*
        /*/
        //String trident_file_path = args[1];
        Functions mainfunc ("trident_folder/main.trd");
        Functions mainfunc ("trident_folder/test.trd");
        Scope scope (& mainfunc);
        scope.run();//*/

        return 0;
}