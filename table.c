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
	strcpy(p->name, name);
	//p->name = name;
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

	// print players name
	printf("Player %s:\n", p->name);

	// print players chips
	printf("chips: %d\n", p->chips);

	// print the name of the player next to player p
	if (p->next == NULL) {
		printf("next player: X\n");
	} else {
		printf("next player: %s\n", p->next->name);
	}

	// print the players hand
	printf("hand: ");
	printDeck(p->hand);
	printf("\n");

	// print players position
	printf("pos = %d\n", p->pos);

}


Table newTable(void) {
	// allocate memory for the table
	Table t = malloc(sizeof(*t));

	// check memory was allocated correctly
	// check memory was allocated correctly
	if (t == NULL) {
		fprintf(stderr, "couldn't allocate memory for the table\n");
		exit(1);
	}

	// initialize data
	t->utg = NULL;
	
	t->nPlayers = 0;
	t->BB = 0;
	t->SB = 0;
	t->Ante = 0;
	t->street = -1;
	t->pot = 0;
	t->bet = -1;
	
	t->communityCards = newEmptyDeck();
	t->mainDeck = newStandardDeck();
	
	// return the new table
	return t;
}

void freeTable(Table t) {
	Player p = t->utg;

	int i = 0;
	while (p != NULL && i < nPlayers(t)) {
		Player temp = p;
		p = p->next;
		freePlayer(temp);
		i++;
	}

	freeDeck(t->communityCards);
	freeDeck(t->mainDeck);
	free(t);
}

void addPlayer(Player p, Table t) {

	// check valid player and table
	if (t == NULL || p == NULL) {
		printf("addPlayer: must pass valid deck and card\n");
		return;
	}

	// add player to table
	if (nPlayers(t) == 0) {
		t->utg = p;
		p->pos = 0;
	} else if (nPlayers(t) > 8) {
		printf("cannot add more than 9 players to a table\n");
		return;
	} else {
		Player cur = t->utg;
		int i = 1;
		while (i < nPlayers(t) && cur != NULL) {
			cur = cur->next;
			i++;
		}

		cur->next = p;
		p->pos = i;
		p->next = t->utg;
	}

	// incrament players
	t->nPlayers++;
}

int nPlayers(Table t) {
	if (t == NULL) return 0;

	return t->nPlayers;
}

void printTable(Table t) {
	printf("nPlayers: %d, %d/%d, ante: %d\n", nPlayers(t), t->BB, t->SB, t->Ante);
	printf("mainDeck: ");
	printDeck(t->mainDeck);
	printf("\ncommunityCards: ");
	printDeck(t->communityCards);
	printf("\ncurrent street: %d\n", t->street);
	printf("current pot: %d\n", t->pot);
	printf("bet amount for current street: %d\n", t->bet);

	// print all players
	Player p = t->utg;
	printf("players: (starting at utg)\n");
	int i = 0;
	while(p != NULL && i < nPlayers(t)) {
		printPlayer(p);
		p = p->next;
		i++;
	}
}

void removePlayer(Table t, int pos) {

	if (nPlayers(t) == 0 || pos >= nPlayers(t)) return;

	Player cur = t->utg;

	if (cur->next == NULL) {
		t->utg = NULL;
		freePlayer(cur);
	} else {
		while (cur->next->pos != pos) {
			cur = cur->next;
		}
		
		// check if next is utg
		if (cur->next->pos == t->utg->pos) {
			t->utg = t->utg->next;
		}

		Player temp = cur->next;
		cur->next = cur->next->next;
		freePlayer(temp);

		// adjust the position of the remaining players
		for (int i = 0; i < nPlayers(t) -1; i++) {
			if (cur->pos > pos) cur->pos--;
			cur = cur->next;
		}
		
	}

	t->nPlayers--;
}




