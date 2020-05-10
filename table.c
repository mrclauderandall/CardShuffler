// implamentation of table 

#include "table.h"
#include <string.h>

Player newPlayer(char *name, int chips) {
	Player p = malloc(sizeof(*p));

	if (p == NULL) {
		fprintf(stderr, "couldn't allocate memory for player\n");
		exit(EXIT_FAILURE);
	}


	p->name = malloc(sizeof(name));
	p->name = name;
	p->chips = chips;
	p->next = NULL;
	p->hand = newEmptyDeck();
	p->pos = -1;

	return p;
}


void freePlayer(Player p) {
	p->next = NULL;
	free(p->name);
	freeDeck(p->hand);
	free(p);
}

void printPlayer(Player p) {
	
	// check valid player
	if (p == NULL) {
		printf("X\n");
		return;
	}

	printf("Player %s:\n", p->name);
	printf("chips: %d\n", p->chips);
	if (p->next == NULL) {
		printf("next player: X\n");
	} else {
		printf("next player: %s\n" p->next->name);
	}
	
}
