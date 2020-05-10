// table ADT header file

#include "deck.h"


typedef struct player *Player;
struct player {
	char *name;
	int chips;
	Player next;
	Deck hand;
	int pos;	// used to indicate position on table, bb, sb, dealer, utg
};

typedef struct table *Table;
struct table {
	Player utg;
	int nPlayers, BB, SB, Ante;
	Deck mainDeck, communityCards;
	int street;	// 0 = preflop, 1 = flop, 2 = turn, 3 = river, 4 = showdown
	int pot;
	int bet;	// bet amount for current street
};





// create a new player
Player newPlayer(char *name, int chips);

// free a player
void freePlayer(Player p);

// create a new table
Table newTable(void);

// free a table and all the players at the table
void freeTable(Table t);

// add a player to a table
void addPlayer(Player p, Table t);

// remove and free player from a table
void removePlayer(Table t, int pos);

// assign positions to the players

// move player positions

// deal cards to players

// retrieve cards from players

// add chips to the pot 

// give pot to a player

// player makes a move

// print player data
void printPlayer(Player p);

// print table
void printTable(Table t);

// return the number of players on a table
int nPlayers(Table t);









