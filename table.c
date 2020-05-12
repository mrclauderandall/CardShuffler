// implamentation of table 

#include <stdio.h>
#include <string.h>

#include "deck.h"
#include "table.h"

struct player {
	char *name;
	int chips;
	Player next;
	Deck hand;
	int hand_size;	// 2 for texas hold em, 4 for omaha (fuck omaha)
	int button;	// 0 = utg, 1 = utg+1, 2 = utg+2,..., (nPlayers - 2) = SB, (nPlayers - 1) = BB
	int bet;	// amount of bet for current round, reset to zero after each round
};

struct table {
	Player utg;
	int nPlayers, BB, SB, Ante;
	Deck mainDeck, communityCards;
	int street;	// 0 = preflop, 1 = flop, 2 = turn, 3 = river, 4 = showdown
	int pot;
	int bet;	// bet amount for current street
};

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
	p->button = -1;

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
	printf("button = %d\n", p->button);

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
		p->button = 0;
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
		p->button = i;
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
		printf("\n\n\n");
		printPlayer(p);
		p = p->next;
		i++;
	}
}

void removePlayer(Table t, int button) {

	if (nPlayers(t) == 0 || button >= nPlayers(t)) return;

	Player cur = t->utg;

	if (cur->next == NULL) {
		t->utg = NULL;
		freePlayer(cur);
	} else {
		while (cur->next->button != button) {
			cur = cur->next;
		}
		
		// check if next is utg
		if (cur->next->button == t->utg->button) {
			t->utg = t->utg->next;
		}

		Player temp = cur->next;
		cur->next = cur->next->next;
		freePlayer(temp);

		// adjust the position of the remaining players
		for (int i = 1; i < nPlayers(t); i++) {
			if (cur->button > button) cur->button--;
			cur = cur->next;
		}
		
	}

	t->nPlayers--;
}

void moveButtons(Table t) {
	// check valid table
	if (t == NULL) {
		printf("moveButtons: must pass valid table\n");
		return;
	}

	t->utg->button = nPlayers(t) - 1;
	t->utg = t->utg->next;
	Player cur = t->utg;
	for (int i = 1; i < nPlayers(t); i++) {
		cur->button--;
		cur = cur->next;
	}
}

void takeBlinds(Table t) {
	// check valid table
	if (t == NULL) {
		printf("moveButtons: must pass valid table\n");
		return;
	}

	Player cur = t->utg;
	for (int i = 1; i < nPlayers(t); i++) {
		if (cur->button == nPlayers(t) - 1) {
			playerBet(t, cur, bigBlind(t));
		} else if (cur->button == nPlayers(t) - 2) {
			playerBet(t, cur, smallBlind(t));
		} else {
			playerBet(t, cur, ante(t));
		}

		cur = cur->next;
	}	
}

void playerBet(Table t, Player p, int bet) {
	// check valid table and player
	if (t == NULL || p == NULL) {
		printf("playerBet: must pass valid table and player\n");
		return;
	}

	// check player has enough chips
	if (bet > playerChips(p)) {
		printf("player does not have enough chips\n");
		return;
	}

	// remove chips from player
	p->chips -= bet;

	// add chips to bot
	t->pot += bet;

	// set players bet amount
	p->bet = bet;

	// set bet amount for table
	if (bet > t->bet) {
		t->bet = bet;
	}
}

// return small blind amount
int smallBlind(Table t) {
	if (t == NULL) {
		printf("smallBlind: must pass valid table\n");
		exit(1);
	}

	return t->SB;	
}

// return bigblind amount
int bigBlind(Table t) {
	if (t == NULL) {
		printf("bigBlind: must pass valid table\n");
		exit(1);
	}

	return t->BB;
}

int ante(Table t) {
	if (t == NULL) {
		printf("ante: must pass valid table\n");
		exit(1);
	}

	return t->Ante;
}

int playerChips(Player p) {
	if (p == NULL) {
		printf("playerChips: must pass valid table\n");
		exit(1);
	}

	return p->chips;
}


// WORK IN PROGRESS
void dealCards(Table t) {
	if (t == NULL) {
		printf("dealCards: must pass valid table\n");
		exit(1);
	}

	Player cur = t->utg;

	for (int i = 0; i < 2*nPlayers(t); i++) {
		addCard(removeCard(t->mainDeck, 0), cur->hand, 0);
		cur = cur->next;
	}
}

void retrieveCards(Table t) {
	if (t == NULL) {
		printf("retrieveCards: must pass valid table\n");
		exit(1);
	}

	Player cur = t->utg;

	for (int i = 0; i < nPlayers(t); i++) {
		// get size of players hand



		addCard(removeCard(t->mainDeck, 0), cur->hand, 0);
		cur = cur->next;
	}	
}



































