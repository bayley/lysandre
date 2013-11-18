#include <cstdlib>
#include <iostream>
#include <string>

#include "pokemon.h"
#include "util.h"
#include "constants.h"
#include "typechart.h"

using namespace std;

int calcStat(int base, int EV, int IV, float nature) {
	return (int) (nature * (2 * base + EV / 4 + IV));
}

int calcDmg(Pokemon* user, Pokemon* target, Move* move) {
	int atk, def;
	if (move->category == SPECIAL) {
		atk = user->getStat(SPA);
		def = user->getStat(SPD);
	} else if (move->category == PHYSICAL) {
		atk = user->getStat(ATK);
		def = user->getStat(DEF);
	} else {
		return 0;
	}

	float stab = move->type == user->type1 || move->type == user->type2 ? (user->ability == ADAPTABILITY ? 2.0 : 1.5) : 1.0;
	float rval = (float) rand() / RAND_MAX;
	float rch = (float) rand() / RAND_MAX;
	int crit = rch < 1.0 / (move->flags & HIGH_CH ? 8 : 16);
	if (crit) {
		if (!user->game->quiet) cout << "A critical hit!" << endl;
		if (target->ability == ANGER_POINT) {
			if (!user->game->quiet) cout << "Anger Point activated!" << endl;
			target->boost(ATK, 6);
		}
	}
	float rmod = 1.0 + 0.2 * (rval - 0.5);
	float ch = crit ? (user->ability == SNIPER ? 2.25 : 1.5) : 1.0;
	float tmod1 = target->type1 >= 0 ? typechart[move->type][target->type1] : 1;
	float tmod2 = target->type2 >= 0 ? typechart[move->type][target->type2] : 1;
	float amod1 = (target->ability == HUSTLE ? 1.5: 1.0);
	float wmod = (move->type == FIRE && user->game->weather == SUN ||
		move->type == WATER && user->game->weather == RAIN) ? 1.5 : 1.0;
	float scrmod = (target->side == 1 && target->game->lightscreen1 == 1 ||
					target->side == 2 && target->game->lightscreen2 == 1) && move->category == SPECIAL ||
				   (target->side == 1 && target->game->reflect1 == 1 ||
				   target->side == 2 && target->game->reflect2 == 1) && move->category == PHYSICAL ? 0.5 : 1.0;

	return (int) ((42 * atk * move->bp(user) / 50 / def + 2) * stab * rmod * tmod1 * tmod2 * ch * amod1 * wmod * scrmod);
}

float boostFactor(int stages) {
	if (stages >= 0) return (float) stages / 2.0 + 1;
	return 2.0 / (2.0 - (float) stages);
}

void newGame(GameState* g, Pokemon* mons) {
	g->pokemon = mons;
	g->active1 = 0;
	g->active2 = 6;
	g->gravity = g->lightscreen1 = g->lightscreen2 = 0;
	g->reflect1 = g->reflect2 = 0;
	g->safeguard1 = g->safeguard2 = 0;
	g->ingrain1 = g->ingrain2 = 0;
	g->aqua1 = g->aqua2 = 0;
	g->weather = NONE;
	g->lastdmg = 0;
	g->lastmove = (Move*) 0;
	g->quiet = 0;
}

void newPoke(Pokemon* p, string name, int hp, int atk, int def, int spa, int spd, int spe, 
			 int type1, int type2, int ability, int player) {
	p->name = name;
	p->bHP = hp;
	p->bAtk = atk;
	p->bDef = def;
	p->bSpA = spa;
	p->bSpD = spd;
	p->bSpe = spe;
	p->ability = ability;
	p->type1 = type1;
	p->type2 = type2;
	p->side = player;
	p->mAtk = p->mDef = p->mSpA = p->mSpD = p->mSpe = p->mAcc = 0;
	p->status = p->flinched = p->protecting = p->rampaging = p->flash_fire = 0;
	p->confused = p->taunted = 0;
	p->maxHP = 2 * p->bHP + p->iHP + p->eHP / 4 + 100;
	p->curHP = p->maxHP;
}

void invest(Pokemon* p, int item, int ehp, int eatk, int edef, int espa, int espd, int espe,
			int ihp, int iatk, int idef, int ispa, int ispd, int ispe) {
	p->item = item;
	p->eHP = ehp;
	p->eAtk = eatk;
	p->eDef = edef;
	p->eSpA = espa;
	p->eSpD = espd;
	p->eSpe = espe;
	p->iHP = ihp;
	p->iAtk = iatk;
	p->iDef = idef;
	p->iSpA = ispa;
	p->iSpD = ispd;
	p->iSpe = ispe;
}

void setMoves(Pokemon* p, Move** movetab, int move1, int move2, int move3, int move4) {
	p->moves[0] = movetab[move1];
	p->moves[1] = movetab[move2];
	p->moves[2] = movetab[move3];
	p->moves[3] = movetab[move4];
}

int checkNegatingAbility(Pokemon* user, Pokemon* target, Move* m) {
	if (user->ability != MOLD_BREAKER && user->ability != TURBOBLAZE && user->ability != TERAVOLT) {
		if (m->category == STATUS && target->ability == MAGIC_BOUNCE) {
			target->use(m, user);
			return 0;
		}
		if (m->type == GROUND && target->ability == LEVITATE) return 0;
		if (m->type == WATER && target->ability == STORM_DRAIN) {
			target->boost(SPA, 1);
			return 0;
		}
		if (m->type == WATER && target->ability == WATER_ABSORB || target->ability == DRY_SKIN) {
			target->curHP += target->maxHP / 4;
			return 0;
		}
		if (m->type == ELECTRIC && target->ability == LIGHTNINGROD) {
			target->boost(SPA, 1);
			return 0;
		}
		if (m->type == FIRE && target->ability == FLASH_FIRE) {
			target->flash_fire = 1;
			return 0;
		}
		if (m->type == GRASS && target->ability == SAP_SIPPER) {
			target->boost(ATK, 1);
			return 0;
		}
	}
	return 1;
}