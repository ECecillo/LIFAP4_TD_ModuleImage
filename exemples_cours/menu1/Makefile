

CCOPTIONS	= -Wall -pedantic -ansi -g
CCOPTIONS_R	= -Wall -pedantic -ansi -O2
CC			= g++ $(CCOPTIONS)

debug: prog
release: prog

prog: main.o menu.o
	$(CC) main.o menu.o -o prog

menu.o: menu.cpp menu.h
	$(CC) -c menu.cpp

main.o: main.cpp menu.h
	$(CC) -c main.cpp


clean:
	\rm -rf *.o prog
