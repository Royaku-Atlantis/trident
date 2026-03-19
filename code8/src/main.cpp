#include <iostream>
#include "general.hpp"
using namespace std;
#include "trident.hpp"

int main(){

        ArgumentList args;
        //ValueType : VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR
        args.add_val(Value(true));
        args.add_val(Value(1));
        args.add_val(Value((std::string)"caca"));
        args.add_val(Value(420.69));
        args.add_val(Value());
        args.add_val(Value((OperatorType)'+'));
        cout << args.string() ;

        //ValueType : VALUE_UNDEF, VALUE_NUMB, VALUE_BOOL, VALUE_STRING, VALUE_VARIABLE, VALUE_OPERATOR
        
        
        return 0;
}