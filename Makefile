CC=gcc
CFLAGS= -std=c11
SRC= main.c owner.c pet.c game.c
HDR= owner.h pet.h game.h

all: $(SRC) $(HDR)
	$(CC) -o MyPet $(SRC) $(CFLAGS)
