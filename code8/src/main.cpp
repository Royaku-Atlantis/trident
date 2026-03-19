#include <iostream>
#include "general.hpp"
using namespace std;
#include "trident.hpp"

int main(){

        ArgumentList args;
        //ValueType : VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR
        
        args.add_val(Value(true));
        args.add_val(Value(15.0));
        args.add_val(Value(OPn_ADD));
        
        args.add_val(Value(1.0));
        args.add_val(Value(2.0));
        args.add_val(Value(OPn_SUB));

        args.add_val(Value((std::string)"j'aime manger du "));
        args.add_val(Value((std::string)"PAIN"));
        args.add_val(Value(OPn_ADD));

        args.add_val(Value(OPn_ADD));

        args.add_val(Value());

        cout << args.string() ;
        
        return 0;
}