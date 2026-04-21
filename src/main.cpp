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
        //*
        //String trident_file_path = args[1];
        Executer exe;
        exe.add_function("main", "trident_folder/main.trd");
        exe.add_function("test", "trident_folder/test.trd");

        exe.run();
        return 0;
}
