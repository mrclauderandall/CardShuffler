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
	int button;	// 0 = utg, 1 = utg+1, 2 = utg+2,..., (nPlayers - 2) = SB, (nPlayers - 1) = BB
	int bet;	// amount of bet for current stree, reset to zero after each street
	bool active, ai;
	int turns; // number of turns the player has had during the current street
};

struct table {
	Player utg, cur;	// cur = current player with right to have a turn
	int nPlayers, activeP, BB, SB, Ante, round;
	Deck mainDeck, communityCards;
	int street;	// -1 = pre deal, 0 = preflop, 1 = flop, 2 = turn, 3 = river, 4 = showdown
	int hand_size;	// 2 for texas hold em, 4 for omaha (fuck omaha)
	int deck_size;	// size of the full deck with no cards dealt
	int pot;
	int bet;	// bet amount for current street
};



/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ helper definitions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

void invokeAction(Table t, Player p, int move);







/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Work In Progress ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	deck has been shufled 
	buttons have been placed
	cards have been dealt
	blinds have been collected

	this is or texus holdem 
*/
void playStreets(Table t) {
	// check valid table 
	if (t == NULL) {
		printf("playStreets: must pass valid table\n");
		exit(1);
	}

	// declare variables
	int cards, i;
	bool turnFlag;
	int street = 0;
	Player cur;


	while (street < 4) {
		


		if (street > 0) {
			// reset bet amount
			t->bet = 0;

			// init player data
			cur = t->utg;
			for (i = 0; i < t->nPlayers; i++) {
				cur->bet = 0;
				cur->turns = 0;
				cur = cur->next;
			}
		}
		
		//printf("\n\n\n\n");
		//printf("street %d starting\n", street);
		//printTable(t);
		//printf("\n\n");


		// check valid street
		if (street == 0) {
			// preflop
			cards = 0;
		} else if (street == 1) {
			// flop
			cards = 3;
		} else if (street == 2 || street == 3) {
			// river and turn
			cards = 1;
		} else {
			printf("playStreets: invalid street. t->street = %d\n", street);
			exit(1);
		}

		// deal community cards
		for (i = 0; i < cards; i++) {
			addCard(removeCard(t->mainDeck, 0), t->communityCards, -1);
		}

		// print community cards
		if (deckSize(t->communityCards) > 0) {
			printf("community cards: ");
			printDeck(t->communityCards);
			printf("\n");
		} 

		// players take their turns
		turnFlag = true;
		while (turnFlag) {
			// next player takes a turn
			playerMove(t);

			// check if any more players need to have a turn
			if (!streetActive(t)) {
				turnFlag = false;
				//printf("\n\n");
				//printf("street %d finished\n", street);
				//printTable(t);
				//printf("\n\n\n\n");
			}
		}

		// check if a player has won
		if (t->activeP == 1) break;

		street++;
	}

	Player winner = showdownWinner(t);

	// give pot to winning player
	winner->chips += t->pot;

	// print winner
	printf("%s wins %d chips!\n", winner->name, t->pot);

	// update table data
	t->pot = 0;
}

Player showdownWinner(Table t) {
	// check valid table
	if (t == NULL) {
		printf("showdownWinner: must pass valid table\n");
		exit(1);
	}

	// declare variables
	Player cur = t->utg;
	Player winner;
	int i;

	if (t->activeP == 1) {
		// find last player
		for (i = 0; i < t->nPlayers; i++) {
			if (cur->active) {
				winner = cur;
				break;
			}
			
			cur = cur->next;		
		}
	} else {
		// print community cards
		printf("community cards: ");
		printDeck(t->communityCards);
		printf("\n");

		// loop through printing hands for each player
		for (i = 0; i < t->nPlayers; i++) {
			if (cur->active) {
				printf("%d: %s's hand: ", cur->button, cur->name);
				printDeck(cur->hand);
				printf("\n");
			}
			
			cur = cur->next;		
		}

		// take user input to choose winner
		int w;
		printf("pick winner: ");
		scanf("%d", &w);

		// find the winner
		cur = t->utg;
		for (i = 0; i < w; i++) {
			cur = cur->next;
		}

		// set winner
		winner = cur;
	}

	return winner;
}


































/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ play functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

void initRound(Table t) {
	// check valid table
	if (t == NULL) {
		printf("initRound: must pass valid table\n");
		exit(1);
	}

	// declare variables
	Player cur;
	int i;
	
	// retrieve cards
	retrieveCards(t);

	// move buttons
	moveButtons(t);

	// set cur
	t->cur = t->utg;

	// shuffle deck
	shuffle(t->mainDeck);

	// update table data
	t->pot = 0;
	t->bet = 0;
	t->street = 0;
	t->activeP = t->nPlayers;

	// update all players data
	cur = t->utg;
	for (i = 0; i < t->nPlayers; i++) {
		cur->bet = 0;
		cur->active = true;
		cur->turns = 0;
		cur = cur->next;	
	}

	// collect blinds
	collectBlinds(t);

	// reset player turns
	cur = t->utg;
	for (i = 0; i < t->nPlayers; i++) {
		cur->turns = 0;
		cur = cur->next;	
	}

	// deal cards
	dealCards(t);

}

void playerMove(Table t) {
	// check valid table
	if (t == NULL) {
		printf("streetActive: must pass valid table\n");
		exit(1);
	}

	// declare variables
	Player cur = t->cur;
	int move = 1;

	// check if player is active
	if (cur->active) {
		// get player action
		if (cur->ai) {
			printf("ai players have not yet been implamented\n");
			move = 0;
		} else {
			move = humanMove(t, cur);
		}

		// invoke player action
		invokeAction(t, cur, move);		

		// increase player turns
		cur->turns++;
	}

	// move cur to next player
	t->cur = t->cur->next;
}

bool streetActive(Table t) {
	if (t == NULL) {
		printf("streetActive: must pass valid table\n");
		exit(1);
	}

	// check if only 1 player remains
	if (t->activeP < 2) return false;

	// declare variables
	Player cur = t->utg;

	// check how many turns each player has had 
	for (int i = 0; i < t->nPlayers; i++) {
		if (cur->turns < 1 && cur->active) {
			return true;
		}

		cur = cur->next;
	}

	return false;
}

void collectBlinds(Table t) {
	// check valid table
	if (t == NULL) {
		printf("collectBlinds: must pass valid table\n");
		return;
	}

	Player cur = t->utg;
	for (int i = 0; i < nPlayers(t); i++) {
		if (cur->button == nPlayers(t) - 1) {
			// remove chips from player
			cur->chips -= t->BB;

			// add chips to bot
			t->pot += t->BB;

			// set players bet amount
			cur->bet = t->BB;

			// set bet amount for table
			t->bet = t->BB;
			
		} else if (cur->button == nPlayers(t) - 2) {
			// remove chips from player
			cur->chips -= t->SB;

			// add chips to bot
			t->pot += t->SB;

			// set players bet amount
			cur->bet = t->SB;
		} else {
			// remove chips from player
			cur->chips -= t->Ante;

			// add chips to bot
			t->pot += t->Ante;

			// set players bet amount
			cur->bet = t->Ante;
		}

		cur = cur->next;
	}	
}





/*
pot:		12
josh: 		6		big blind           chips 94
claude:		6		small blind (utg)	chips 94
t->bet = 6


josh calls (4)
	invoke bet(t, josh, 4)


*/
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

	// check bet amount is enough
	if ((p->bet + bet) < t->bet) {
		printf("playerBet: bet amount must be greater than or"
			"equal to the largest bet of the current street\n");
		return;
	} else if ((p->bet + bet) > t->bet) {
		// reset player turns
		Player cur = t->utg;
		for (int i = 0; i < t->nPlayers; i++) {
			cur->turns = 0;
		}
	}

	// remove chips from player
	p->chips -= bet;

	// add chips to pot
	t->pot += bet;

	// set players bet amount
	p->bet += bet;

	// set bet amount for table
	t->bet = p->bet;

	// incrament player turns
	p->turns++;
}

void playerFold(Table t, Player p) {
	// check valid table and player
	if (t == NULL || p == NULL) {
		printf("foldPlayer: must pass valid table and player\n");
		return;
	}

	// update player data
	p->bet = -1;
	p->active = false;

	// update table data
	t->activeP--;
}

void playerCheck(Table t, Player p) {
	// check valid table and player
	if (t == NULL || p == NULL) {
		printf("foldPlayer: must pass valid table and player\n");
		return;
	}

	// incrament player turn
	p->turns++;
}

int humanMove(Table t, Player p) {
	printf("player move called\n");

	// check valid table and player
	if (t == NULL || p == NULL) {
		printf("playerMove: must pass valid table\n");
		exit(1);
	}

	// declare variables
	bool check_legal = false;
	int move = -1;
	char key;
	bool setFlag = false;
	int prints = 0;

	// check valid street and player not folded
	if (t->street == -1 || p->active != true) {
		return move;
	}
	
	// calculate call bet
	int call_bet = t->bet - p->bet;

	// print players name
	printf("\n%s's turn!\n", p->name);
	printf("chips: %d\n", p->chips);

	// print hand
	printf("hand: ");
	printDeck(p->hand);
	printf("\n");

	// print legal moves
	printf("legal moves:\n");
	printf("    F  Fold         ");
	prints++;

	if (p->bet >= t->bet) {
		printf("    C  Check        ");
		prints++;
		check_legal = true;
	} else if (p->chips > t->bet) {
		printf("    C  Call    (%d) ", call_bet);
		check_legal = false;
		prints++;
	}

	if (prints > 1) {
		printf("\n");
		prints = 0;
	}

	if (p->chips > 0 && t->bet == 0) {
		printf("    B  Bet          ");
		prints++;
	} else if (p->chips > t->bet) {
		printf("    R  Raise        ");
		prints++;
	}

	if (prints > 1) {
		printf("\n");
		prints = 0;
	}

	if (p->chips > 0) {
		printf("    A  All in (%d)   ", p->chips);
		prints++;
	}

	if (prints > 1) {
		printf("\n");
		prints = 0;
	}

	while (!setFlag) {
		printf("enter move: ");
		scanf("%c", &key);
		if (key == 'F' || key == 'f') {
			move = 0;
			setFlag = true;
		} else if (key == 'C' || key == 'c') {
			if (check_legal) {
				move = 1;
			} else {
				move = 2;
			}
			setFlag = true;
		} else if (key == 'B' || key == 'b') {
			move = 3;
			setFlag = true;
		} else if (key == 'R' || key == 'r') {
			move = 4;
			setFlag = true;
		} else if (key == 'A' || key == 'a') {
			move = 5;
			setFlag = true;
		} else {
			printf("invalid key\n");
			setFlag = false;
		}	
	}	

	return move;
}








/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ player ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

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
	p->active = true;
	p->turns = 0;
	p->ai = false;

	return p;
}

void freePlayer(Player p) {
	p->next = NULL;
	free(p->name);
	freeDeck(p->hand);
	free(p);
}

Player getPlayer(Table t, int pos) {
	// check valid table
	if (t == NULL) {
		printf("getPlayer: must pass valid deck and card\n");
		exit(1);
	}

	// check table isn't empty
	if (t->nPlayers < 1) {
		printf("getPlayer: talbe is empty\n");
	}

	// check valid position
	if (pos > t->nPlayers || pos < 0) {
		printf("getPlayer: pos must be between 0 and nPlayers\n");
	}

	Player cur = t->utg;
	for (int i = 0; i < pos; i++) {
		cur = cur->next;
	}

	return cur;
}

void addPlayer(Player p, Table t) {

	// check valid player and table
	if (t == NULL || p == NULL) {
		printf("addPlayer: must pass valid deck and card\n");
		exit(1);
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



bool activePlayer(Player p) {
	if (p == NULL) return false;

	return p->active;
}






/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ table  ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

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
	t->cur = NULL;
	
	t->nPlayers = 0;
	t->activeP = 0;
	t->BB = 0;
	t->SB = 0;
	t->Ante = 0;
	t->street = -1;
	t->pot = 0;
	t->bet = -1;
	t->round = 0;
	t->hand_size = 2;
	t->deck_size = 52;
	
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

int nPlayers(Table t) {
	if (t == NULL) return 0;

	return t->nPlayers;
}

int tableRound(Table t) {
	if (t == NULL) return 0;

	return t->round;	
}

int streetBet(Table t) {
	if (t == NULL) return 0;

	return t->bet;	
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

void dealCards(Table t) {
	if (t == NULL) {
		printf("dealCards: must pass valid table\n");
		return;
	}

	// declare variables
	Player cur = t->utg;
	int cards = (t->hand_size) * nPlayers(t);

	// loop through the players dealing cards
	for (int i = 0; i < cards; i++) {
		addCard(removeCard(t->mainDeck, 0), cur->hand, 0);
		cur = cur->next;
	}

	// update the street
	t->street = 0;
}

void retrieveCards(Table t) {
	// check valid table
	if (t == NULL) {
		printf("retrieveCards: must pass valid table\n");
		exit(1);
	}

	// declare variables
	int cards, count, i, cards_community;
	Player cur;

	// check how many community cards were in play
	cards_community = deckSize(t->communityCards);

	// retrieve community cards
	for (i = 0; i < cards_community; i++) {
		addCard(removeCard(t->communityCards, 0), t->mainDeck, -1);
	}

	// check how many cards have been dealt
	cards = t->deck_size - deckSize(t->mainDeck) + cards_community;

	// remove cards from players until all cards have been retrieved
	count = 0;
	cur = t->utg;
	while (count < cards) {
		
		// remove all cards from the player 
		for (i = 0; i < deckSize(cur->hand); i++) {
			addCard(removeCard(cur->hand, 0), t->mainDeck, -1);
			count++;
		}

		cur = cur->next;
	}
	
}

int smallBlind(Table t) {
	if (t == NULL) {
		printf("smallBlind: must pass valid table\n");
		exit(1);
	}

	return t->SB;	
}

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


void setBlinds(Table t, int BigBlind, int SmallBlind, int Ante) {
	if (t == NULL) {
		printf("setBlinds: must pass valid table\n");
		exit(1);
	}

	t->BB = BigBlind;
	t->SB = SmallBlind;
	t->Ante = Ante;
}






/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ printing and testing ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

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

/*
	// print the name of the player next to player p
	if (p->next == NULL) {
		printf("next player: X\n");
	} else {
		printf("next player: %s\n", p->next->name);
	}
*/
	// print the players hand
	printf("hand: ");
	printDeck(p->hand);
	printf("\n");

	// print players bet
	printf("current bet: %d\n", p->bet);

	// print players button
	printf("button = %d\n", p->button);

}

void printTable(Table t) {
	//printf("nPlayers: %d, %d/%d, ante: %d\n", nPlayers(t), t->BB, t->SB, t->Ante);
	//printf("mainDeck: ");
	//printDeck(t->mainDeck);
	printf("\ncommunityCards: ");
	printDeck(t->communityCards);
	//printf("\ncurrent street: %d\n", t->street);
	printf("\ncurrent pot: %d\n", t->pot);
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





/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ helper functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

void invokeAction(Table t, Player p, int move) {
	int bet;

	switch (move) {
		case 0:
			// player folds
			playerFold(t, p);
			printf("%s folds\n", p->name);
			break;
		case 1:
			// player checks
			playerCheck(t, p);
			printf("%s checks\n", p->name);
			break;
		case 2:
			// player calls
			bet = t->bet - p->bet;
			playerBet(t, p, bet);
			printf("%s calls\n", p->name);
			break;
		case 3:
			// player bets
			printf("bet amount: ");
			scanf("%d", &bet);
			playerBet(t, p, bet);
			printf("%s bets %d chips\n", p->name, bet);
			break;
		case 4:
			// player raises
			printf("raise amount: ");
			scanf("%d", &bet);
			printf("%s raises to %d chips\n", p->name, bet);
			bet -= p->bet;
			playerBet(t, p, bet);		
			break;
		case 5:
			// player goes all in
			bet = p->chips;
			playerBet(t, p, bet);
			printf("%s goes all in!!	(%d chips)\n", p->name, bet);
			break;
		default:
			printf("invokeAction: swtich error, move = %d\n", move);
	}
}


























