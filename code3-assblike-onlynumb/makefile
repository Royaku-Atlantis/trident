all: main.exe
main.exe: main.o ElementL.o Liste.o
	g++ -g main.o ElementL.o Liste.o main.exe 

main.o: main.cpp
	g++ -g -Wall -c main.cpp

ElementL.o: ElementL.cpp
	g++ -g -Wall ElementL.cpp

Liste.o: Liste.cpp
	g++ -g -Wall Liste.cpp

clean:
	rm *.o

veryclean: clean
	rm *.exe