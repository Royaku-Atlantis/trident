#include <iostream>
#include <vector>
using namespace std;

#include <cstdarg>
void print(const char* fmt...) // C-style "const char* fmt, ..." is also valid
{
    va_list args;
    va_start(args, fmt);
 
    while (*fmt != '\0')
    {
        if (*fmt == 'd')
        {
            int i = va_arg(args, int);
            std::cout << i << ' ';
        }
        else if (*fmt == 'c')
        {
            // note automatic conversion to integral type
            int c = va_arg(args, int);
            std::cout << static_cast<char>(c) << ' ';
        }
        else if (*fmt == 'f')
        {
            double d = va_arg(args, double);
            std::cout << d << ' ';
        }
        ++fmt;
    }

    va_end(args);
}
 

// basic funcs
int getch(){
        cout << "End of ts, enter a numb:";
        int a;
        cin >> a;
        return a;
}


// trident type shit

class Program{
private:
        char * command_buffer;
        int command_buffer_size = 0;
        vector<float> valstack;
        vector<int> returnstack;
public:
        void execute(){
                for (int i=0; i<command_buffer_size; i++){
                        cout << "char " << i << " = " << (unsigned int)command_buffer[i] << " / \'" << command_buffer[i] << "\' \n";
                }
        }
        void add_char(char value){
                command_buffer[command_buffer_size] = value;
                command_buffer_size++;
        }
};





int main(int argc, char * argv[]){

        Program joe;

        print("dcff", 3, 'a', 1.999, 42.5);

        joe.execute();

        return getch();
}