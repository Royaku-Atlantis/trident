all: obj\main.o obj\basiclib.o obj\trident.o
	g++ obj\main.o obj\basiclib.o obj\trident.o -o trident.exe

obj\main.o: src\main.cpp
	g++ -c src\main.cpp -o obj\main.o

obj\basiclib.o: src\basiclib.cpp
	g++ -c src\basiclib.cpp -o obj\basiclib.o

obj\trident.o: src\trident.cpp
	g++ -c src\trident.cpp -o obj\trident.o

clean:
	del obj\*.o

veryclean:
	del obj\*.exe
