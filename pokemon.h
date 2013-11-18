#ifndef __POKEMON_H
#define __POKEMON_H

#include <iostream>
#include "constants.h"

using namespace std;

class GameState;
class Move; 
class Pokemon;

class Pokemon {
public:
	//current game
	GameState* game;
	//side of the field it is on
	int side;
	//name
	string name;
	//moves
	Move* moves[4];
	//base stats
	int bHP, bAtk, bDef, bSpA, bSpD, bSpe;
	//IV's
	int iHP, iAtk, iDef, iSpA, iSpD, iSpe;
	//EV's
	int eHP, eAtk, eDef, eSpA, eSpD, eSpe;
	//boost (*m*odifier) stages
	int mAtk, mDef, mSpA, mSpD, mSpe, mAcc, mEva;
	//types
	int type1, type2;
	//max, current HP
	int maxHP, curHP;
	//status
	int status;
	//flinched?
	int flinched;
	//confused?
	int confused;
	//taunted?
	int taunted;
	//Leech Seed
	int seeded;
	//Destiny Bond
	int destined;
	//If so, destiny bond counterpart
	Pokemon* dbPartner;
	//Perish Count
	int perishcount;
	//Disabled moves
	int dmove_flags;
	//abilities
	int ability;
	//hold item
	int item;
	//protecting?
	int protecting;
	//outrage/thrash/petal dance rampage
	int rampaging;
	//flash fire boost
	int flash_fire;
	//index of last move used
	int lastidx;
	
	int getStat(int statID);
	float getAcc();
	float getEva();
	int takeDmg(int dmg);
	int recoil(int dmg);
	int boost(int statID, int stages);
	int lower(int statID, int stages);
	int inflictStatus(int statusID);
	int flinch();
	int use_move(Move* m, Pokemon* target);
	int use(int move_index, Pokemon* target);
};


class Move {
public:
	string name;
	int type, category, id;
	int _bp;
	int maxPP, curPP;
	int flags;
	int priority;
	float _acc;

	virtual int bp(Pokemon* poke);
	virtual float acc(Pokemon* poke);
	virtual int exec(Pokemon* user, Pokemon* target);
};


class GameState {
public:
	GameState();
	Pokemon* pokemon;
	int active1, active2;
	int lightscreen1, lightscreen2;
	int reflect1, reflect2;
	int safeguard1, safeguard2;
	int ingrain1, ingrain2;
	int aqua1, aqua2;
	int rocks1, rocks2;
	int spikes1, spikes2;
	int gravity;
	int weather;
	int quiet;
	int lastdmg;
	Move* lastmove;
};

#endif