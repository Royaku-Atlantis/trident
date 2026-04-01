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

int main()
{
        String input;
        do 
        {
                cout << "Entrez une commande trident : \n";
                getline(cin,input);
                Command * usercmd = create_command(input);//joe mamajoe mama
                usercmd->run();
                cout << endl;
        }
        while (input!="exit");

        return 0;
}