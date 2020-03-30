all: main

main : main.o
	g++ main.o -o exe
	
main.o : main.cpp
	g++ -c -ansi -pedantic-errors --std=c++11 main.cpp
	
run1:
	./exe CPU2.txt 0
run2:
	./exe CPU2.txt 1
clean:
	rm *.o exe

