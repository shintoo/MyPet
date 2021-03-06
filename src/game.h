#ifndef _GAME_H_
#define _GAME_H_

#define MAXST   20
#define MAXPETS 5
#define ITEMS   15

#include "pet.h"
#include "owner.h"

enum Index {DOGFOOD, DOGTREAT, CATFOOD, CATTREAT, WATER,
              TENNISBALL, CHEWTOY, LURE, TOYMOUSE,
              DOGSHAMPOO, LEASH, CATSHAMPOO};

typedef struct shopitem {
	int option;
	int price;
	int resellValue;
	char *name;
	int count;
} ShopItem;


void Game_Init(Owner **Player, Pet **MyPet);
void Game_Loop(Owner *Player, Pet *MyPet);
void Game_Exit(Owner *Player, Pet *MyPet);
char ShowMenu(Owner *Player, Pet *MyPet);
void Shop(Owner *Player);
void Save(Owner *Player, Pet *player);
void Load(Owner *Player, Pet *player);

char * s_gets(char * st, int n);
char chget(void);
void eatline(void);

extern const ShopItem ShopCatalog[12];

#endif
