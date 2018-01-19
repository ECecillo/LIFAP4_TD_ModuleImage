

CCOPTIONS	= -Wall -pedantic -ansi -g   #-O2   # pour optimiser
CC			= g++ $(CCOPTIONS)


prog: main.o menu.o
	$(CC) main.o menu.o -o prog

menu.o: menu.cpp menu.h
	$(CC) -c menu.cpp

main.o: main.cpp menu.h
	$(CC) -c main.cpp


clean:
	\rm -rf *.o prog