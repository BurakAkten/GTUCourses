all: _mainTester

_mainTester: _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o 
	g++ -o exe _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o

_mainTester.o: _mainTester.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 _mainTester.cpp
	
CPU.o: CPU.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 CPU.cpp
	
CPUProgramDyn.o: CPUProgramDyn.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 CPUProgramDyn.cpp

Memory.o: Memory.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 Memory.cpp

Computer.o: Computer.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 Computer.cpp

clean:
	rm *.o exe
