all: System

System: seewhat.o
	gcc -o seeWhat seewhat.o -lm

seewhat.o: seewhat.c
	gcc -c  seewhat.c

seewhat.c : timerServer.o
	gcc -o timerServer timerServer.o -lm
	
timerServer.o : timerServer.c
	gcc -c timerServer.c
	
timerServer.c : showResult.o
	gcc -o showResult showResult.o
showResult.o :
	gcc -c showResult.c
	
clean:
	rm *.o seeWhat showResult timerServer

	
