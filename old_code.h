/*

This file contains code that is no longer in use that we 
wish to save. This is not compilable code

*/


// code for testing the random number distrobution of 
// left_deck(int a);
int test[52] = {0};
int n = 0;
for (int i = 0; i < 10000; i++) {
	n = left_deck(i);
	test[n] = test[n] + 1;
}

for (int i = 0; i < 52; i++) {
	printf("card[%d] = %d\n", i, test[i]);
}


// test remove top card
	Card c;
	for (int i = 0; i < 53; i++) {
		// remove the top card
		c = removeTopCard(d);

		// print the top card
		printf("							removed card: ");
		printCard(c);
		printf("\n");

		// print the deck
		showDeck(d);

		// free the card
		free(c);
	}








	// old show card function
	int count = 0;
	while (c != NULL) {
		
		printCard(c);

		count++;

		if (count >= 13) {
			printf("\n");
			count = 0;
		}

		if (c == d->bottom) {
			break;
		} else {
			c = c->bellow;
		}
	}
	printf("..end of deck..\n\n");
	
	printf("from bottom to top:\n");

	c = d->bottom;

	count = 0;
	while (c != NULL) {
		
		printCard(c);

		count++;

		if (count >= 13) {
			printf("\n");
			count = 0;
		}

		if (c == d->top) {
			break;
		} else {
			c = c->above;
		}
	}
	printf("..end of deck..\n\n");




	// cut the deck with random size
	int size = left_deck(0);
	DoubleDeck dd = cutDeck(d, size);
	printf("\n\nTHE DECK HAS BEEN CUT\n\n");
	printf("left deck:\n");
	showDeck(dd->left);
	printf("\n\n\nright deck:\n");
	showDeck(dd->right);
	printf("\n\n\noriginal deck:	(should be the same as the right deck)\n");
	showDeck(d);





				insert_card = removeBottomCard(dd->left);
				insert_card->bellow = c;
				
				if (c == dd->right->top) {
					c->above = insert_card;
					dd->right->top = insert_card;

				} else {
					insert_card->above = c->above;
					c->above = insert_card;
					insert_card->above->bellow = insert_card;
				}





	// print the deck
	printf("original deck:\n");
	showDeck(d);

	// perfect riffle shuffle deck
	
	for (int i = 0; i < 9; i++) {
		printf("\nriffle shuffling deck:\n");
		d = riffle(d, 0);
		showDeck(d);
	}
	

	// show deck
	
	// show the deck
	printf("original deck: ");
	showDeck(d);
	printf("\n\n");
    
	// riffle deck 7 times and show deck after each riffle
	for (int i = 0; i < 53; i++) {
		printf("now starting riffle shuffle number %d\n", i);

		// riffle deck
    	riffle(d, 0);
    	
    	//show the deck riffled
    	printf("after riffle number %d:		d->size = %d\n", i, d->size);
    	showDeck(d);
    	printf("\n");
	}





	// old	

	// add card to the top of the deck
	if (d->top == NULL) {
		d->top = c;
		d->bottom = c;
	} else {
		d->top->above = c;
		d->top->above->bellow = d->top;
		d->top = d->top->above;
	}





/*
// remove and return the top card from the deck
Card removeTopCard(Deck d) {

	if (d->size == 0) return newCard('x', 0);

	// set card c as the top card
	Card c = d->top;

	// check this is not the last card
	if (d->top == d->bottom) {
		c = d->top;
		d->top = NULL;
		d->bottom = NULL;
	} else {
		// remove links between top card
		// and the card bellow it
		d->top->bellow->above = NULL;
		d->top = d->top->bellow;
		c->bellow = NULL;
	}

	// deincrament size of deck
	d->size--;

	// return the top card
	return c;
}

Card removeBottomCard(Deck d) {
	if (d->size == 0) return newCard('x', 0);

	// set card c as the bottom card
	Card c = d->bottom;

	// check this is not the last card
	if (d->top == d->bottom) {
		//c = d->top;
		d->top = NULL;
		d->bottom = NULL;
	} else {
		// remove links between bottom card
		// and the card above it
		d->bottom = d->bottom->above;
		d->bottom->bellow = NULL;
		c->above = NULL;
	}

	// deincrament size of deck
	d->size--;

	// return the top card
	return c;
}
*/
Card removeSpecificCard(Deck d, int value, char suit) {
	// check valid deck
	if (d == NULL) {
		printf("invalid deck\n");
		return NULL;
	}

	// declare variables
	Card cur = d->top;
	Card return_card;

	// loop through deck searching for card
	while (cur != NULL) {
		
		// check if current card is card c
		if (cur->value == value && cur->suit == suit) {
			// return position of the card
			return_c
		}

		cur = cur->bellow;
	}

}














/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ player ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	create a new player with the given name
*/
Player newPlayer(char *name);

/*
	free all memory used for player p
*/
void freePlayer(Player p);


// set ///////////////////////////////////////////////////////////////////////////////////////////

/*
	set the amount of chips for a player
*/
void setChips(Player p, int chips);

/*
	set the button of a player
*/
void setPlayerButton(Player p, int button);

/*
	set the players bet for the current street
*/
void setPlayerBet(Player p, int bet);

/*
	set the amount of turns a player has had this street
*/
void setPlayerTurns(Player p, int turns);

/*
	set the players active status
*/
void setPlayerActive(Player p, bool flag);

// get ///////////////////////////////////////////////////////////////////////////////////////////

/*
	return the players name
*/
const char *playerName(Player p);

/*
	return the players hand
*/
Deck playerHand(Player p);

/*
	return the players chips
*/
int playerChips(Player p);

/*
	return the position of a player
*/
int playerPos(Player p);

/*
	return the button of a player
*/
int playerButton(Player p);

/*
	return the players bet for the current stree	
*/
int playerBet(Player p);

/*
	return the amount of turns a player has had this street
*/
int playerTurns(Player p);

/*
	return the players active status
*/
bool playerActive(Player p);

/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ table ADT functions  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	create a new empty table
*/
Table newTable(void);

/*
	free all memory used for a table
*/
void freeTable(Table t);

// set ///////////////////////////////////////////////////////////////////////////////////////////

/*
	add a player to a table
	and set their position
*/
void addPlayer(Table t, Player p);

/*
	set the amount of chips in the pot
*/
void setPot(Table t, int chips);

/*
	set the current street
*/
void setStreet(Table t, int street);

/*
	set the blind amounts
*/
void setBlinds(Table t, int b, int s, int a);

/*
	set the highest bet amount for the current street
*/
void setTableBet(Table t, int bet);

/*
	set the amount of rounds played
*/
void setRounds(Table t, int rounds);


// get ///////////////////////////////////////////////////////////////////////////////////////////

/*
	return number of players at table
*/
int nPlayers(Table t);

/*
	return the number of chips in the pot
*/
int pot(Table t);

/*
	return the current street
*/
void street(Table t);

/*
	return the big bling for the table
*/
int bigBlind(Table t);

/*
	return the small bling for the table
*/
int smallBlind(Table t);

/*
	return the big bling for the table
*/
int ante(Table t);

/*
	return the highest bet amount for the current street
*/
int betTable(Table t);

/*
	return the amount of rounds played
*/
int rounds(Table t);

/*
	return the main deck for the table
*/
Deck tableDeck(Table t);

/*
	return the community cards for the table
*/
Deck tableCC(Table t);

/*
	return the player in position pos
*/
Player getPlayer(Table t, int pos);








































/*
	remove a player from a table
*/
void removePlayer(Table t, int i);

/*
	add chips to the tables pot
*/
void addPotChips(Table t, int chips);

/*
	remove all chips from the pot and return
	the number of chips in the pot
*/
int removePotChips(Table t);

// return table data functions 
/*
	return number of players on the table
*/
int nPlayers(Table t);

/*
	return current street
*/
int street(Table t);

/*
	return number of rounds played
*/
int rounds(Table t);

/*
	return player i
*/
Player tablePlayer(Table t, int i);

/*
	return the button of player i
*/
int playerButton(Table t, int i);

/*
	return the index of the player whos 
	turn it currently is
*/
int currentPlayer(Table t);

/*
	return the number of turns player i has
	had during the current street
*/
int playerTurns(Table t, )






















