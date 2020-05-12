// Interface for table

#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include "deck.h"

typedef struct player *Player;
typedef struct table *Table;


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

// move player positions
void moveButtons(Table t);

// take inital blind bets from players
void takeBlinds(Table t);

// deal cards to players
void dealCards(Table t);

// retrieve cards from players
void retrieveCards(Table t);

// give pot to a player

// player makes a move

// print player data
void printPlayer(Player p);

// print table
void printTable(Table t);

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




