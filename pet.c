#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pet.h"
#include "owner.h"
#include "game.h"

Pet * Pet_New(char type) {
	Pet *NewPet = malloc(sizeof(Pet));

	NewPet->name = malloc(MAXST * sizeof(char));
	NewPet->hunger = NewPet->thirst = 0;
	NewPet->coat = 10;
	NewPet->energy = 50;
	NewPet->age = 0;
	
	NewPet->SetName = Pet_SetName;
	switch(type) {
		case 'd':
		case 'D':
			NewPet->Feed = Dog_Feed;
			NewPet->Play = Dog_Play;
			NewPet->Wash = Dog_Wash;
			NewPet->type = 'd';
		break;
		case 'c':
		case 'C':
//			NewPet->Feed = Cat_Feed;
//			NewPet->Play = Cat_Play;
//			NewPet->Wash = Cat_Wash;
			NewPet->type = 'c';
		break;
	}

	return NewPet;
}

void Pet_SetName(Pet *self, char *name) {
	strncpy(self->name, name, MAXST);
}

void Dog_Feed(Pet *self, Owner *owner) {
	char choice;

	if (self->hunger < 1) {
		printf("%s is too full to eat right now!\n", self->name);
		sleep(1);
		return;
	}
	printf("Food & Drink:\n\tf) Dog food (%d)\n\tt) Dog treat (%d)\n\tw) Water (%d)\n"
	       "What would you like to give to %s? ", owner->Inventory[DOGFOOD],
		    owner->Inventory[DOGTREAT], owner->Inventory[WATER], self->name);
	choice = chget();
	while (strchr("ftw", choice) == NULL) {
		puts("Please enter 'f' for Dog food, 't' for Dog treat, or 'w' for Water!");
		choice = chget();
	}
	switch (choice) {
		case 'f':
			if (owner->Inventory[DOGFOOD] == 0) {
				puts("You don't have any dog food!\nYou can buy some at the Shop.");
				sleep(1);
				return;
			}
			self->hunger -= 6;
			self->energy += 25;
			owner->Inventory[DOGFOOD] -= 1;
			printf("%s is sniffing the bowl...", self->name);
			sleep(2);
			printf("\n%s ate the dog food!\n", self->name);
			sleep(1);
		break;
		case 't':
			if (owner->Inventory[DOGTREAT] == 0) {
				puts("You don't have any dog treats!\nYou can buy some at the Shop.");
				sleep(1);
				return;
			}
			self->hunger -= 2;
			self->energy += 40;
			owner->Inventory[DOGTREAT] -= 1;
			printf("%s barks in excitement!", self->name);
			sleep(1);
			printf("\n%s loved the dog treat!\n", self->name);
			sleep(1);
		break;
		case 'w':
			if (owner->Inventory[WATER] == 0) {
				puts("You don't have any water!\nYou can buy some at the Shop.");
				sleep(1);
				return;
			}
			self->thirst -= 6;
			self->energy += 15;
			owner->Inventory[WATER] -= 1;
			printf("%s runs towards the water bowl!", self->name);
			sleep(1);
			printf("\n%s drank it all!\n", self->name);
			sleep(1);
		break;
	}
	if (self->hunger < 0) {
		self->hunger = 0;
	}
	if (self->thirst < 0) {
		self->thirst = 0;
	}
	if (self->energy > 50) {
		self->energy = 50;
	}
}

void Dog_Play(Pet *self, Owner *owner) {
	char choice;
	putchar('\n');
	if (self->energy < 11) {
		printf("%s is too tired to play.\n", self->name);
		sleep(1);
		return;
	}
	if (self->hunger > 7) {
		printf("%s is too hungry to play.\n", self->name);
		sleep(1);
		return;
	}
	if (self->thirst > 7) {
		printf("%s is too thirsty to play.\n", self->name);
		sleep(1);
		return;
	}
	
	printf("Toys:\n\tb) Tennis Ball\n\tc) Chew Toy\n");
	printf("What do you want to use to play with %s? ", self->name);
	choice = chget();
	while (strchr("bc", choice) == NULL) {
		puts("Please enter 'b' for Tennis Ball or 'c' for Chew Toy.");
		choice = getchar();
	}
	switch (choice) {
		case 'b':
			if (owner->Inventory[TENNISBALL] == 0) {
				puts("You don't have a tennis ball!\nYou can buy one at the Shop.");
				sleep(1);
				return;
			}
			printf("%s is playing with the tennis ball!\n", self->name);
			sleep(4);
			self->hunger += 1;
			self->thirst += 3;
			self->energy -= 20;
			if (self->energy < 0) {
				self->energy = 0;
			}
			self->coat -= 2;
			switch (self->energy) {
				case 0 ... 11:
					printf("%s got all tired out from playing!\n", self->name);
					sleep(1);
				break;
				case 12 ... 50:
					printf("%s had a lot of fun playing!\n", self->name);
					sleep(1);
				break;
			}
		break;
		case 'c':
			if (owner->Inventory[CHEWTOY] == 0) {
				puts("You don't have a chew toy!\nYou can buy one at the Shop.");
				sleep(1);
				return;
			}
			printf("%s is chewing happily on the toy...", self->name);
			sleep(4);
			self->hunger += 3;
			self->thirst += 1;
			self->energy -= 10;
			self->coat -= 4;
			switch (self->energy) {
				case 0 ... 11:
					printf("%s is worn out.\n", self->name);
					sleep(1);
				break;
				case 12 ... 50:
					printf("\n%s loved chewing on the chew toy!\n", self->name);
					sleep(1);
				break;
			}
		break;
	}
	if (self->energy < 0) {
		self->energy = 0;
	}
	if (self->coat < 0) {
		self->coat = 0;
	}
}

void Dog_Wash(Pet *self, Owner *owner) {
	if (owner->Inventory[DOGSHAMPOO] == 0) {
		puts("You don't have any dog shampoo!\nYou can buy some at the Shop.");
		sleep(1);
		return;
	}
	switch (self->coat) {
		case 0 ... 5:
			printf("\n%s is really dirty!\nTime for a bath!", self->name);
			sleep(6);
			printf("\n%s is much cleaner now!", self->name);
		break;
		case 6 ... 10:
			printf("%s could use a scrubbin'!", self->name);
			sleep(3);
			printf("%s feels refreshed!", self->name);
		break;
	}
	self->coat += 4;
	if (self->coat > 10) {
		self->coat = 10;
	}
	owner->Inventory[DOGSHAMPOO] -= 1;
	sleep(1);
}
