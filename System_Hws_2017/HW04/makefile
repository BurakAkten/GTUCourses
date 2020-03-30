all: System

System: requirements.o hw4.o
	gcc -o grepTh hw4.o requirements.o -pthread

requirements.o : requirements.c
	gcc -c requirements.c -pthread
	
hw3.o: hw3.c
	gcc -c hw4.c -pthread

clean:
	rm *.o grepTh

	
