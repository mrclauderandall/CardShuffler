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
	Player Dealer, BigBlind, SmallBlind, UTG, cur;
	int nPlayers, BB, SM, Ante;
	Deck communityCards;
	int street;	// 0 = preflop, 1 = flop, 2 = turn, 3 = river, 4 = showdown
	int pot;
	int bet;	// bet amount for current street
	Player better;	// player that made the bet
};





// create a new player
Player newPlayer(char *name, int chips);

// free a player'
void freePlayer(Player p);

// create a new table

// free a table

// add a player to a table

// remove a player from a table

// assign positions to the players

// move player positions

// deal cards to players

// retrieve cards from players

// add chips to the pot 

// give pot to a player

// player makes a move

// print player data
void printPlayer(Player p);











