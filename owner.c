#include <stdlib.h>
#include <string.h>
#include "owner.h"
#include "game.h"
#include "pet.h"

Owner * Owner_New(void) {
	Owner *new = malloc(sizeof(Owner));
	new->name = malloc(MAXST * sizeof(char));
	new->Inventory = malloc(ITEMS * sizeof(int));
	new->SetName = Owner_SetName;
	
	new->money = 100;
	return new;
}

void Owner_SetName(Owner *self, char *name) {
	strncpy(self->name, name, MAXST);
}
