#ifndef _OWNER_H_
#define _OWNER_H_

typedef struct owner {
	char *name;
	int money;
	int *Inventory;

	void (*SetName)(struct owner *self, char *name);
} Owner;

Owner * Owner_New(void);

void Owner_SetName(Owner *self, char *st);
#endif
