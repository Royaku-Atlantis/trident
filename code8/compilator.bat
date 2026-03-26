rm bin\trident.exe
g++ src/main.cpp src/definitions/general.cpp src/definitions/values.cpp src/definitions/expressions.cpp src/definitions/arguments.cpp src/definitions/commands.cpp src/definitions/functions.cpp src/definitions/scopes.cpp src/definitions/executer.cpp -g -o bin\trident.exe -std=c++20
.\exe.bat
