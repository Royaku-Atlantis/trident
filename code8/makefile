all: bin/main.o bin/trident.o bin/general.o
	g++ bin/main.o bin/trident.o bin/general.o -g -o bin/trident.exe -std=c++20

bin/main.o: src/main.cpp
	g++ src/main.cpp -g -o bin/main.o -std=c++20

bin/trident.o: src/trident.cpp
	g++ src/trident.cpp -g -o bin/trident.o -std=c++20

bin/general.o: src/general.cpp
	g++ src/general.cpp -g -o bin/general.o -std=c++20

release:
	g++ src/main.cpp src/trident.cpp src/general.cpp -g -o bin\trident.exe -std=c++20 -O3

clean:
	rm bin/*.o

veryclean:
	rm trident.exe
