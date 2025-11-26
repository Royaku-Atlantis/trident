windres trident_executer_icon.rc -O coff -o trident_executer_icon.res
g++ -c main.cpp -o main.o
g++ main.o trident_executer_icon.res -o trident_alpha3.exe
