CC=gcc
CFLAGS= -std=c11
SRC= src/main.c src/owner.c src/pet.c src/game.c
HDR= src/owner.h src/pet.h src/game.h

all: $(SRC) $(HDR)
	$(CC) -o MyPet $(SRC) $(CFLAGS)
