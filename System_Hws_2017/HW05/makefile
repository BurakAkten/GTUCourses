all: System

System: requirements.o hw5.o
	gcc -o grepSh hw5.o requirements.o -pthread

requirements.o : requirements.c
	gcc -c requirements.c -pthread
	
hw5.o: hw5.c
	gcc -c hw5.c -pthread

clean:
	rm *.o grepSh

	
