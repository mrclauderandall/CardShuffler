// Interface for table ADT
// written by J+C

#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>


typedef struct player *Player;
typedef struct table *Table;


/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ player ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	create a new player with the given
	name and amount of chips
*/
Player newPlayer(char *name, int chips);

/*
	add player p to a table t
*/
void addPlayer(Player p, Table t);

/* 
	free all the memory allocated for player p
*/
void freePlayer(Player p);

/*
	return the player in position pos in 
	table t without modifying the table
*/
Player getPlayer(Table t, int pos);

/* 
	return true if player p is still active
	in the current round and hasn't folded
	return false if the player has folded
*/
bool activePlayer(Player p);

/*
	print all legal moves that player p can make
	take in user input and return the intager 
	corresponding to the player move, see 
	notes for details on intager move keys
	this function is only for human players
*/
int humanMove(Table t, Player p);

/*
	make player p fold, update table t and 
	player p accordingly
*/
void playerFold(Table t, Player p);

/*
	make player p check, update table t and 
	player p accordingly
*/
void playerCheck(Table t, Player p);

/*
	player makes a move 
*/
void playerMove(Table t);


/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ table  ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	create a new empty table
*/
Table newTable(void);

/*
	free a table and all the players at the table
*/
void freeTable(Table t);

/*
	take inital blind bets from players
*/
void collectBlinds(Table t);

/*
	set the blinds and ante for table t
*/
void setBlinds(Table t, int BigBlind, int SmallBlind, int Ante);

/*
	return the current round of the table
*/
int tableRound(Table t);

/*
	return the largest bet amount for the current street
*/
int streetBet(Table t);

/*
	deal cards to players
*/
void dealCards(Table t);

/*
	retrieve cards from players
*/
void retrieveCards(Table t);

/*
	return true if there are still players that
	need to make a move in the current street
*/
bool streetActive(Table t);

/*
	initialize a new round, move the buttons, 
	set cur to utg, shuffle the deck, collect 
	blinds, deal cards and set table and 
	player data

*/
void initRound(Table t);

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ printing and testing ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	print all the data of player p
*/
void printPlayer(Player p);

/*
	print all the data of table t
	including all the players
*/
void printTable(Table t);
































void showHand(Player p);


Player showdownWinner(Table t);





void playStreets(Table t);

// remove and free player from a table
void removePlayer(Table t, int pos);

// move player positions
void moveButtons(Table t);







// give pot to a player

// player makes a move



// return the number of players on a table
int nPlayers(Table t);

// return small blind amount
int smallBlind(Table t);

// return bigblind amount
int bigBlind(Table t);

// return the ante amount
int ante(Table t);

// return players chips
int playerChips(Player p);

// player makes a bet
void playerBet(Table t, Player p, int bet);


#endif

/*
	!!!    NOTES    !!!!

	buttons:
		0				uder the gun
		nPlayers - 1	Small blind
		nPlayers		Big blind

	moves:
		0		F		fold
		1		C		check
		2		C		call
		3		B		bet
		4		R		raise
		5		A		all in
		6		S 		show hand

*/


