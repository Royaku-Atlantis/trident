all:test.exe
test.exe: main.o randomlib.o
	g++ -g main.o randomlib.o -o test.exe

main.o: main.cpp
	g++ -c main.cpp

randomlib.o: randomlib.cpp
	g++ -c randomlib.cpp

clean:
	rm *.o

veryclean: clean
	rm *.exe