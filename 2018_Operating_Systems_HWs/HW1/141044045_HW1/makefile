all: main

main: main.o 8080emu.o gtuos.o
	g++ -o sim8080 main.o 8080emu.o gtuos.o

main.o: main.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 main.cpp

8080emu.o: 8080emu.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 8080emu.cpp

gtuos.o: gtuos.cpp
	g++ -c -ansi -pedantic-errors -std=c++11 gtuos.cpp

run0:
	./sim8080 $(FILE) 0

run1:
	./sim8080 $(FILE) 1

run2:
	./sim8080 $(FILE) 2

clean: 
	rm *.o sim8080
