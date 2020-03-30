all: System

System: requirements.o hw3.o
	gcc -o exe hw3.o requirements.o

requirements.o : requirements.c
	gcc -c -ansi -pedantic-errors requirements.c
	
hw3.o: hw3.c
	gcc -c -ansi -pedantic-errors hw3.c

clean:
	rm *.o exe

	
