all : sayisal

sayisal : sayısal1.o
	g++ -o exe sayısal1.o -lm

sayısal1.o : sayısal1.cpp
	g++ -c -ansi -pedantic-errors --std=c++11 sayısal1.cpp

clear:
	rm *.o exe
