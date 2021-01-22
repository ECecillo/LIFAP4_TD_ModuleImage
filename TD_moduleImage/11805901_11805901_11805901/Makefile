# =========== Nom Exec ===================
EXEC = prog.out

# =========== Commande de compil ===========
CC = gcc
FLAGS = -g -Wall

# =========== Chemins ================

SRC_PATH = src/
OBJ_PATH = src/o/ 

# =========== Fichiers ===========

SRC = $(SRC_PATH)mainTest.cpp $(SRC_PATH)image.cpp $(SRC_PATH)pixel.cpp 
OBJ = $(OBJ_PATH)mainTest.o $(OBJ_PATH)image.o $(OBJ_PATH)pixel.o 

	# Module Image
	IMAGE = $(SRC_PATH)image.cpp $(SRC_PATH)image.h
	IMAGE_H = $(SRC_PATH)image.h 
	# Module Pixel
	PIXEL = $(SRC_PATH)pixel.h $(SRC_PATH)pixel.cpp
	PIXEL_H = $(SRC_PATH)pixel.h

# ====================== Makefile ======================

all: $(EXEC)

$(EXEC): $(obj)
	$(CC) $(OBJ) -o $(EXEC)

mainTest.o: main.cpp $(IMAGE_H) $(PIXEL_H)
	$(CC) -c $(SRC_PATH)main.cpp

image.o: $(IMAGE) $(PIXEL_H)
	$(CC) -c $(SRC_PATH)image.cpp
pixel.o: $(PIXEL)
	$(CC) -c $(SRC_PATH)pixel.cpp

clean:
	rm -f $(OBJ_PATH)*.o *.out

veryclean: 
	rm -f $(EXEC) $(OBJ_PATH)$(obj) 