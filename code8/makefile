all: bin/main.o bin/general.o bin/values.o bin/expressions.o bin/arguments.o bin/commands.o bin/functions.o bin/scopes.o bin/executer.o bin/parser.o
	g++ bin/main.o bin/general.o bin/values.o bin/expressions.o bin/arguments.o bin/commands.o bin/functions.o bin/scopes.o bin/executer.o bin/parser.o -g -o bin/trident.exe -std=c++20

bin/main.o: src/main.cpp
	g++ -c src/main.cpp -g -o bin/main.o
bin/general.o: src/definitions/general.cpp
	g++ -c src/definitions/general.cpp -g -o bin/general.o

bin/values.o: src/definitions/values.cpp
	g++ -c src/definitions/values.cpp -g -o bin/values.o

bin/expressions.o: src/definitions/expressions.cpp
	g++ -c src/definitions/expressions.cpp -g -o bin/expressions.o

bin/arguments.o: src/definitions/arguments.cpp
	g++ -c src/definitions/arguments.cpp -g -o bin/arguments.o

bin/commands.o: src/definitions/commands.cpp
	g++ -c src/definitions/commands.cpp -g -o bin/commands.o

bin/functions.o: src/definitions/functions.cpp
	g++ -c src/definitions/functions.cpp -g -o bin/functions.o

bin/scopes.o: src/definitions/scopes.cpp
	g++ -c src/definitions/scopes.cpp -g -o bin/scopes.o

bin/executer.o: src/definitions/executer.cpp
	g++ -c src/definitions/executer.cpp -g -o bin/executer.o
bin/parser.o: src/definitions/parser.cpp
	g++ -c src/definitions/parser.cpp -g -o bin/parser.o
release:
	g++ src/main.cpp src/definitions/general.cpp src/definitions/values.cpp src/definitions/expressions.cpp src/definitions/arguments.cpp src/definitions/commands.cpp src/definitions/functions.cpp src/definitions/scopes.cpp src/definitions/executer.cpp -g -o bin\trident.exe -O4

clean:
	rm bin/*.o

veryclean:
	rm bin/*
