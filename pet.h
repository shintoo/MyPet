#ifndef _PET_H_
#define _PET_H_

struct owner;
typedef struct owner Owner;

typedef struct pet {
	char *name;
	char type;
	int hunger;
	int thirst;
	int coat;
	int energy;
	int age;
	
	void (*SetName)(struct pet *self, char *name);
	
	void (*Feed)(struct pet *self, Owner *owner);
	void (*Play)(struct pet *self, Owner *owner);
	void (*Wash)(struct pet *self, Owner *owner);
	void (*Walk)(struct pet *self, Owner *owner);
} Pet;


Pet * Pet_New(char type);
void Pet_SetName(Pet *self, char *name);

void Dog_Feed(Pet *self, Owner *owner);
void Dog_Play(Pet *self, Owner *owner);
void Dog_Wash(Pet *self, Owner *owner);
void Dog_Walk(Pet *self, Owner *owner);

void Cat_Feed(Pet *self, Owner *owner);
void Cat_Play(Pet *self, Owner *owner);
void Cat_Wash(Pet *self, Owner *owner);

#endif
