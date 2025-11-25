all: main.exe
main.exe: main.o console_graphic.o
	g++ -g main.o console_graphic.o main.exe 

main.o: main.cpp
	g++ -g -Wall main.cpp console_graphic.h -o main.o

console_graphic.o: console_graphic.cpp
	g++ -g -Wall console_graphic.cpp console_graphic.h  -o console_graphic.o

clean:
	rm *.o

veryclean: clean
	rm *.exe