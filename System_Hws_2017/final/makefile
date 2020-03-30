all: System

System: clients.o
	gcc -o clients clients.o -pthread -lm

clients.o: clients.c
	gcc -c  clients.c

clients.c : server.o
	gcc -o server server.o inverse.o -pthread -lm
	
server.o : server.c
	gcc -c server.c

server.c : inverse.o
	gcc -c inverse.c
		
clean:
	rm *.o server clients

	
