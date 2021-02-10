# =========== Nom Exec ===================
EXEC1 = bin/exemple/mainExemple
EXEC2 = bin/test/mainTest
EXEC3 = bin/affichage/mainAffichage

# =========== Commande de compil ===========
CC = g++
FLAGS = -g -Wall
INCLUDE_DIR_SDL = -I/usr/include/SDL2
LIBS_SDL = -lSDL2 -lSDL2_image 

# =========== Chemins ================

SRC_PATH = src/
OBJ_PATH = obj/

# =========== Fichiers ===========


# Fichiers .o et .cpp du programme principal
MAIN1_CPP = mainExemple.cpp
MAIN1_O = mainExemple.o

MAIN2_CPP = mainTest.cpp
MAIN2_O = mainTest.o

MAIN3_CPP = mainAffichage.cpp
MAIN3_O = mainAffichage.o


SRC = $(SRC_PATH)$(MAIN_CPP) $(SRC_PATH)Image.cpp $(SRC_PATH)Pixel.cpp 
OBJ1 = $(OBJ_PATH)$(MAIN1_O) $(OBJ_PATH)Image.o $(OBJ_PATH)Pixel.o
OBJ2 = $(OBJ_PATH)$(MAIN2_O) $(OBJ_PATH)Image.o $(OBJ_PATH)Pixel.o
OBJ3 = $(OBJ_PATH)$(MAIN3_O) $(OBJ_PATH)Image.o $(OBJ_PATH)Pixel.o

	# Module Image
	IMAGE = $(SRC_PATH)Image.cpp $(SRC_PATH)Image.h
	IMAGE_H = $(SRC_PATH)Image.h 
	# Module Pixel
	PIXEL = $(SRC_PATH)Pixel.h $(SRC_PATH)Pixel.cpp
	PIXEL_H = $(SRC_PATH)Pixel.h

# ====================== Makefile ======================

all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJ1)
	$(CC) $(FLAGS) $(OBJ1) -o $(EXEC1) $(LIBS_SDL)

$(EXEC2): $(OBJ2)
	$(CC) $(FLAGS) $(OBJ2) -o $(EXEC2) $(LIBS_SDL)

$(EXEC3): $(OBJ3)
	$(CC) $(FLAGS) $(OBJ3) -o $(EXEC1) $(LIBS_SDL)

$(OBJ_PATH)$(MAIN1_O): $(SRC_PATH)$(MAIN1_CPP) $(IMAGE_H) $(PIXEL_H)
	$(CC) $(FLAGS) -c $(SRC_PATH)$(MAIN1_CPP) -o $(OBJ_PATH)$(MAIN1_O) $(INCLUDE_DIR_SDL)

$(OBJ_PATH)$(MAIN2_O): $(SRC_PATH)$(MAIN2_CPP) $(IMAGE_H) $(PIXEL_H)
	$(CC) $(FLAGS) -c $(SRC_PATH)$(MAIN2_CPP) -o $(OBJ_PATH)$(MAIN2_O) $(INCLUDE_DIR_SDL)

$(OBJ_PATH)$(MAIN3_O): $(SRC_PATH)$(MAIN3_CPP) $(IMAGE_H) $(PIXEL_H)
	$(CC) $(FLAGS) -c $(SRC_PATH)$(MAIN3_CPP) -o $(OBJ_PATH)$(MAIN3_O) $(INCLUDE_DIR_SDL)

$(OBJ_PATH)Image.o: $(IMAGE) $(PIXEL_H)
	$(CC) $(FLAGS) -c $(SRC_PATH)Image.cpp -o $(OBJ_PATH)Image.o $(INCLUDE_DIR_SDL)

$(OBJ_PATH)Pixel.o: $(PIXEL)
	$(CC) $(FLAGS) -c $(SRC_PATH)Pixel.cpp -o $(OBJ_PATH)Pixel.o

clean:
	rm -f $(OBJ_PATH)*.o *.out

veryclean: 
	rm -f $(EXEC1) $(EXEC2) $(EXEC3) $(OBJ_PATH)*.o