#include "owner.h"
#include "pet.h"
#include "game.h"
#include <stdio.h>

int main(void) {
	Pet *MyPet;
	Owner *Player;

	Game_Init(&Player, &MyPet);
	Game_Loop(Player, MyPet);
	Game_Exit(Player, MyPet);


	return 0;
}
