#include "basiclib.hpp"
#include "trident.hpp"
#include <iostream>



int main(int argc, char * argv[]){

        print_argcv(argc, argv);

        Executer joe;

        debug("add print action:\n");

        //const char * newcodeline = ;
        joe.addcodeline("\2Hello World!\n\255");
        joe.addcodeline("\1");
        joe.addcodeline("\2Goodby World >:)\n");
        //joe.addcodeline("\1Caca");

        joe.execute();

        return 0;
}