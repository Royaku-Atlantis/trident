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

int main(){
        /*
        Command * testprint = create_command("print 5 3 - \"joe mama\" * ");//joe mamajoe mama
        testprint->run();
        /*/
        Command test_cmd (CMD_PRINT);
        test_cmd.append_expression(Value(true));
        test_cmd.append_expression(Value(false));
        test_cmd.append_expression(Value(OPb_OR));
        test_cmd.append_expression(Value(OPb_NOT));
        test_cmd.append_expression(Value((String)"Bla"));
        test_cmd.append_expression(Value(4.0));
        test_cmd.append_expression(Value(OPn_MUL));
        test_cmd.append_expression(Value(3.0));
        test_cmd.append_expression(Value(0.0));
        test_cmd.append_expression(Value(5.0));
        test_cmd.append_expression(Value(OPn_MUL));
        test_cmd.append_expression(Value(OPn_DIV));

        ArgumentExecuter exe;
        calculate_arguments(test_cmd.get_expressionstart(), exe);

        cout << exe.string() ;//*/

        return 0;
}