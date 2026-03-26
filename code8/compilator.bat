rm bin\trident.exe
g++ src/main.cpp src/definitions/values.cpp src/definitions/general.cpp src/definitions/executer.cpp -g -o bin\trident.exe -std=c++20
.\exe.bat