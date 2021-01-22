# =========== Nom Exec ===================
EXEC = prog.out

# =========== Commande de compil ===========
CC = gcc
FLAGS = -g -Wall

# =========== Fichiers ===========
SRC = mainTest.cpp image.cpp pixel.cpp 
OBJ = mainTest.o image.o pixel.o 

	# Module Image
	IMAGE = image.cpp image.h
	IMAGE_H = image.h 
	# Module Pixel
	PIXEL = pixel.h pixel.cpp
	PIXEL_H = pixel.h

# ====================== Makefile ======================

all: $(EXEC)

$(EXEC): $(obj)
	$(CC) $(OBJ) -o $(EXEC)

mainTest.o: main.cpp $(IMAGE_H) $(PIXEL_H)
	$(CC) -c main.cpp

image.o: $(IMAGE) $(PIXEL_H)
	$(CC) -c image.cpp
pixel.o: $(PIXEL)
	$(CC) -c pixel.cpp

clean:
	rm -f *.o *.out

veryclean: 
	rm -f $(EXEC) $(obj) *.out 