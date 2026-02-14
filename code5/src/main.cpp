#include "basiclib.hpp"
#include "trident.hpp"
#include <iostream>



int main(int argc, char * argv[]){

        print_argcv(argc, argv);

        basiclib_libaction();
        trident_libaction();

        return 0;
}