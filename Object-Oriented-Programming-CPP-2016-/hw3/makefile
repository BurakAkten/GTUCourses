all: main

main: main.o CPU.o CPUProgram.o
	g++ -o  exe main.o CPU.o CPUProgram.o

main.o: main.cpp
	g++ -c -ansi -pedantic-errors --std=c++11 main.cpp
	
CPU.o: CPU.cpp
	g++ -c -ansi -pedantic-errors --std=c++11 CPU.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c -ansi -pedantic-errors --std=c++11 CPUProgram.cpp

clean:
	rm *.o exe
