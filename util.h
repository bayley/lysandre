#ifndef __UTIL_H
#define __UTIL_H

#include "pokemon.h"

//random float between 0 and 1
float randf();

//computes the non-HP stat of a Pokemon, ignoring boosts
int calcStat(int base, int EV, int IV, float nature);

//computes the base damage
int calcDmg(Pokemon* user, Pokemon* target, Move* move);

//calculate boost factor
float boostFactor(int stages);

//new gamestate
void newGame(GameState* g, Pokemon* mons);

//new Pokemon
void newPoke(Pokemon* p, string name, int hp, int atk, int def, int spa, int spd, int spe, 
			 int type1, int type2, int ability, int player);

void invest(Pokemon* p, int item, int ehp, int eatk, int edef, int espa, int espd, int espe,
			int ihp, int iatk, int idef, int ispa, int ispd, int ispe);

void setMoves(Pokemon* p, Move** movetab, int move1, int move2, int move3, int move4);

//When user uses a move on target, checks if target has an ability which negates it and acts accordingly
//accounts for Flash Fire boosts, Storm Drain SpA boost, etc.
int checkNegatingAbility(Pokemon* user, Pokemon* target, Move* m);

#endif