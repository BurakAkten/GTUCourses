all: System

System: hw2.o
	gcc -o listdir hw2.o
hw2.o: hw2.c
	gcc -c -ansi -pedantic-errors --std=c99 hw2.c

run1 : 
	valgrind --leak-check=yes ./listdir adada files


run2 :
	./listdir adada files
clean:
	rm *.o listdir total.txt

	
