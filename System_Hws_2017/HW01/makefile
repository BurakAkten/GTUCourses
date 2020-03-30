all: System

System: System_01.o
	gcc -o list System_01.o
System_01.o: System_01.c
	gcc -c -ansi -pedantic-errors System_01.c

run:
	 valgrind --leak-check=yes ./list ece deneme.txt

clean:
	rm *.o list

	
