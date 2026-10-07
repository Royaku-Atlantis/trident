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

#include <filesystem>
#define FILE_EXT_LEN 4
#define FILE_EXT ".atl"
int filepath_atl_function_name_get_size(String path)
{
        //check if it end in .atl
        if (!ends_with(path, FILE_EXT)) return -1;

        int size = 0;
        for (int i=path.size()-FILE_EXT_LEN-1; i>=0; i--)
        {
                if (path[i] == '/' or path[i] == '\\') break;
                size ++;
        }
        return size;
}
String get_function_name(String path, int file_name_size)
{
        return path.substr(
                path.size()-file_name_size-FILE_EXT_LEN,
                file_name_size);
}
#undef FILE_EXT_LEN
#undef FILE_EXT

int main(int argc, char ** args)
{
        say( BLUE "start of ALL the program" RESET);
        String program_name = args[1];

        Executer exe;
        exe.add_function("main", program_name+"/main.atl");

        //add all functions
        //*
        for(const auto & entry : filesystem::directory_iterator(program_name+"/functions")) 
        {
                String function_file_path = entry.path().string();

                int filesize = filepath_atl_function_name_get_size(function_file_path);

                if (filesize==-1)
                {
                        //cout << " -> not a func file";
                }
                else
                {
                        String funcfile_name = get_function_name(function_file_path, filesize);
                        //add this function
                        exe.add_function(funcfile_name, function_file_path);
                }
        }//

        exe.run();
        /*/
        cout<<"\n1"<<Value(1, false)<<"\n";
        cout<<"\n1"<<variable_to_reference(Value(1, false))<<"\n";
        cout<<"\n2"<<Value(2, true)<<"\n";
        cout<<"\n2"<<variable_to_reference(Value(2, true))<<"\n";
        cout<<"\n3"<<Value(3.0)<<"\n";
        cout<<"\n3"<<variable_to_reference(Value(3.0))<<"\n";//*/


        return 0;
}
