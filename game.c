#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "pet.h"
#include "owner.h"
#include "game.h"

extern const ShopItem ShopCatalog[12];

void Game_Init(Owner **Player, Pet **MyPet) {
	char type[4];
	char PlayerName[MAXST];
	char PetName[MAXST];

	*Player = Owner_New();
	printf("Welcome to MyPets!\nWhat is your name?\nName: ");
	s_gets(PlayerName, MAXST);
	(*Player)->SetName(*Player, PlayerName);
	
/*	printf("Would you like to start with a dog, or a cat? ");
	s_gets(type, 5);
	while (strchr("DdCc", type[0]) == NULL) {
		printf("Please enter \"dog\" or \"cat\": ");
		s_gets(type, 5);
	}
*/	(*MyPet) = Pet_New('d');

	printf("What would you like to name your %s? ", (*MyPet)->type == 'd' ? "dog" : "cat");
	s_gets(PetName, MAXST);
	(*MyPet)->SetName(*MyPet, PetName);

	printf("%s is happy to join you!\n", (*MyPet)->name);
	sleep(1);
}

void Game_Loop(Owner *Player, Pet *MyPet) {
	char ch = ShowMenu(Player, MyPet);
	int time = 1;

	while (ch != 'q') {
		switch(ch) {
			case 'p': MyPet->Play(MyPet, Player); break;
			case 'f': MyPet->Feed(MyPet, Player); break;
			case 'b': MyPet->Wash(MyPet, Player); break;
			case 's': Shop(Player); break;
			case 'w': MyPet->Walk(MyPet, Player); break;
		}
		ch = ShowMenu(Player, MyPet);
		time++;
		if (time % 10 == 0) {
			MyPet->age++;
		}
		if (time % 5 == 0) {
			MyPet->hunger++;
			if (MyPet->hunger > 10) {
				MyPet->hunger = 10;
			}
			MyPet->thirst++;
			if (MyPet->thirst > 10) {
				MyPet->thirst = 10;
			}
			MyPet->coat--;
			if (MyPet->coat < 0) {
				MyPet->coat = 0;
			}
		}
		MyPet->energy += 2;
	}
}

void Game_Exit(Owner *Player, Pet *MyPet) {
	printf("%s %s goodbye!\nThanks for playing MyPets!\n", MyPet->name, MyPet->type == 'd' ? "barks" : "meows");
	sleep(1);
	free(Player->name);
	free(Player->Inventory);
	free(Player);
	free(MyPet->name);
	free(MyPet);
}

char ShowMenu(Owner *Player, Pet *MyPet) {
	char *hunger;
	char *thirst;
	char *coat;
	char *energy;
	char choice;

	switch (MyPet->hunger) {
		case 0 ... 1:  hunger = "Full"; break;
		case 2 ... 4:  hunger = "Normal"; break;
		case 5 ... 7:  hunger = "Hungry"; break;
		case 8 ... 10: hunger = "Famished"; break;
	}

	switch (MyPet->thirst) {
		case 0 ... 1:  thirst = "Quenched"; break;
		case 2 ... 4:  thirst = "Normal"; break;
		case 5 ... 7:  thirst = "Thirsty"; break;
		case 8 ... 10: thirst = "Parched"; break;
	}

	switch (MyPet->coat) {
		case 0 ... 1: coat = "Stinky"; break;
		case 2 ... 4: coat = "Dirty"; break;
		case 5 ... 7: coat = "Normal"; break;
		case 8 ... 9: coat = "Clean"; break;
		case 10:      coat = "Perfect"; break;
	}
	printf("\n\n\n\n\n\n\n%s\tCash: $%d\n", Player->name, Player->money);
	printf("%s\t\t%s\n", MyPet->name, MyPet->type == 'd' ? "Dog" : "Cat");
	printf("\tAge:\t%d\nStatus:\n\tHunger:\t%s\n\tThirst:\t%s\n\tCoat:\t%s\n\n",
	       MyPet->age, hunger, thirst, coat);

	printf("p) Play with %s\tf) Feed %s\n"
		   "b) Bathe %s\t\ts) Go to the Shop\nw) Walk\t\tq) Quit\n",
		   MyPet->name, MyPet->name, MyPet->name);
	printf("What would you like to do? ");
	choice = chget();
	while (strchr("PpFfBbSsWwQq", choice) == NULL) {
		printf("Please enter an option from the menu (p, f, w, s, or q): ");
		choice = chget(); 
	}
	choice = tolower(choice);
	return choice;
}

void Shop(Owner *Player) {
	int choice;

	printf("\n\n\n\n\n\nWelcome to MyPets Shop!\nCatalog:\n");
	for (int i = 0; i < 12; i++) {
		printf("%d) $%d %s (%d)\t", i, ShopCatalog[i].price, ShopCatalog[i].name, ShopCatalog[i].count);
		if ((i+1) % 2 == 0 && i > 0) {
			putchar('\n');
		}
	}
	putchar('\n');
	printf("What would you like to buy? ");
	scanf("%d", &choice);
	getchar();
	while (choice < 0 || choice > 11) {
		printf("Please enter a number between 0 and 10: ");
		choice = chget();
		choice -= '0';
	}
	Player->Inventory[choice] += ShopCatalog[choice].count;
	Player->money -= ShopCatalog[choice].price;
	printf("Thank you for shopping at the MyPets Shop!\n");
	sleep(1);
}


char * s_gets(char * st, int n) {
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val) {
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
	} else {
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

char chget(void) {
	char str[3];
	s_gets(str, 3);
	return str[0];
}
