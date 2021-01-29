# =========== Nom Exec ===================
EXEC = prog.out

# =========== Commande de compil ===========
CC = gcc
FLAGS = -g -Wall

# =========== Chemins ================

SRC_PATH = src/
OBJ_PATH = obj/
#EXEC_PATH = bin/exemple/ 

# =========== Fichiers ===========

# Fichiers .o et .cpp du programme principale
MAIN_CPP = mainTest.cpp
MAIN_O = mainTest.o


SRC = $(SRC_PATH)$(MAIN_CPP) $(SRC_PATH)image.cpp $(SRC_PATH)pixel.cpp 
OBJ = $(OBJ_PATH)$(MAIN_O) $(OBJ_PATH)image.o $(OBJ_PATH)pixel.o 

	# Module Image
	IMAGE = $(SRC_PATH)image.cpp $(SRC_PATH)image.h
	IMAGE_H = $(SRC_PATH)image.h 
	# Module Pixel
	PIXEL = $(SRC_PATH)pixel.h $(SRC_PATH)pixel.cpp
	PIXEL_H = $(SRC_PATH)pixel.h

# ====================== Makefile ======================

all: $(EXEC)

$(EXEC): $(obj)
	$(CC) $(OBJ) -o bin/exemple/$(EXEC)

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