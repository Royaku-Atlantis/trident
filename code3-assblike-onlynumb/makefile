all: main.exe
main.exe: main.o
	g++ main.o ../vscode_extention/icons/trident_executer_icon.res -o trident_alpha3.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm *.o

veryclean: clean
	rm *.exe