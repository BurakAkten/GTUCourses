all: _mainTester

_mainTester: _mainTester.o Bigram.o BigramDyn.o BigramMap.o
	g++ -o exe _mainTester.o Bigram.o BigramDyn.o BigramMap.o

_mainTester.o : _mainTester.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 _mainTester.cpp

Bigram.o : Bigram.cpp
	 g++ -c -ansi -pedantic-errors -std=c++11 Bigram.cpp

BigramDyn.o : BigramDyn.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 BigramDyn.cpp

BigramMap.o : BigramMap.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 BigramMap.cpp

clean:
	rm *.o exe

 
