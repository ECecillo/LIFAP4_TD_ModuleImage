# =========== Nom Exec ===================
EXEC = bin/exemple/prog

# =========== Commande de compil ===========
CC = g++
FLAGS = -g -Wall

# =========== Chemins ================

SRC_PATH = src/
OBJ_PATH = obj/

# =========== Fichiers ===========


# Fichiers .o et .cpp du programme principale
MAIN_CPP = mainTest.cpp
MAIN_O = mainTest.o


SRC = $(SRC_PATH)$(MAIN_CPP) $(SRC_PATH)Image.cpp $(SRC_PATH)Pixel.cpp 
OBJ = $(OBJ_PATH)$(MAIN_O) $(OBJ_PATH)Image.o $(OBJ_PATH)Pixel.o 

	# Module Image
	IMAGE = $(SRC_PATH)Image.cpp $(SRC_PATH)Image.h
	IMAGE_H = $(SRC_PATH)Image.h 
	# Module Pixel
	PIXEL = $(SRC_PATH)Pixel.h $(SRC_PATH)Pixel.cpp
	PIXEL_H = $(SRC_PATH)Pixel.h

# ====================== Makefile ======================

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(EXEC)

$(OBJ_PATH)$(MAIN_O): $(SRC_PATH)$(MAIN_CPP) $(IMAGE_H) $(PIXEL_H)
	$(CC) $(FLAGS) -c $(SRC_PATH)$(MAIN_CPP) -o $(OBJ_PATH)mainTest.o

$(OBJ_PATH)Image.o: $(IMAGE) $(PIXEL_H)
	$(CC) $(FLAGS) -c $(SRC_PATH)Image.cpp -o $(OBJ_PATH)Image.o

$(OBJ_PATH)Pixel.o: $(PIXEL)
	$(CC) $(FLAGS) -c $(SRC_PATH)Pixel.cpp -o $(OBJ_PATH)Pixel.o

clean:
	rm -f $(OBJ_PATH)*.o *.out

veryclean: 
	rm -f $(EXEC) $(OBJ_PATH)*.o