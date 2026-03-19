all: bin/main.o bin/trident.o bin/general.o
	g++ bin/main.o bin/trident.o bin/general.o -g -o bin/trident.exe -std=c++20

bin/main.o: src/main.cpp
	g++ src/main.cpp -o bin/main.o

bin/trident.o: src/trident.cpp
	g++ src/trident.cpp -o bin/trident.o

bin/general.o: src/general.cpp
	g++ src/general.cpp -o bin/general.o

clean:
	rm bin/*.o

veryclean:
	rm trident.exe
