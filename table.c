// implamentation of table 

#include "table.h"

Player newPlayer(char *name, int chips) {
	Player p = malloc(sizeof(*p));

	if (p == NULL) {
		fprintf(stderr, "couldn't allocate memory for player\n");
		exit(EXIT_FAILURE);
	}

	p->name = malloc(sizeof(name));
	p->name = stpcpy(p->name, name);
	p->chips = chips;
	p->next = NULL;
	p->hand = newEmptyDeck();
	int p->pos = -1;

	return p;
}
