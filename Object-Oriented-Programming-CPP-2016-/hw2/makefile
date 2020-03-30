all: main

main : main.o
	g++ main.o -o exe
	
main.o : main.cpp
	g++ -c -ansi -pedantic-errors --std=c++11 main.cpp
	
clean:
	rm *.o exe

