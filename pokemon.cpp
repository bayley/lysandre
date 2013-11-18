#include <iostream>
#include <string>
#include <cstdlib>

#include "pokemon.h"
#include "constants.h"
#include "util.h"

using namespace std;

int Pokemon::getStat(int statID) {
	switch (statID) {
	case HP:
		return curHP;
	case ATK:
		return calcStat(bAtk, eAtk, iAtk, 1.0) * boostFactor(mAtk) * (status == BURN && ability != GUTS ? 0.5 : 1.0) 
			* (item == CHOICE_BAND ? 1.5 : 1.0) * (item == LIFE_ORB ? 1.3 : 1.0) * (ability == GUTS && status != NONE ? 1.5: 1.0);
	case DEF:
		return calcStat(bDef, eDef, iDef, 1.0) * boostFactor(mDef);
	case SPA:
		return calcStat(bSpA, eSpA, iSpA, 1.0) * boostFactor(mSpA) * (item == CHOICE_SPECS ? 1.5 : 1.0);
	case SPD:
		return calcStat(bSpD, eSpD, iSpD, 1.0) * boostFactor(mSpD);
	case SPE:
		return calcStat(bSpe, eSpe, iSpe, 1.0) * boostFactor(mSpe) * (status == PARALYZE ? 0.25 : 1.0) 
			* (item == CHOICE_SCARF ? 1.5 : 1.0) * (ability == CHLOROPHYLL && game->weather == SUN ? 2.0 : 1.0);
	default:
		return 0;
	}
}

float Pokemon::getAcc() {
	if (mAcc >= 0) {
		return (3.0 + (float) mAcc) / 3.0;
	}
	return 3.0 / (3.0 + (float) mAcc);
}

float Pokemon::getEva() {
	if (mAcc >= 0) {
		return 3.0 / (3.0 + (float) mAcc);
	}
	return (3.0 + (float) mAcc) / 3.0;
}

int Pokemon::takeDmg(int dmg) {
	int sash_flag = 0;
	if (curHP == maxHP) {
		if (ability == STURDY) sash_flag = 1;
		if (item == FOCUS_SASH) sash_flag = 1;
	}
	curHP -= dmg;
	if (curHP < 0) curHP = 0;
	if (sash_flag && curHP == 0) {
		curHP = 1;
		if (item == FOCUS_SASH) item = NONE;
	}
	if (!game->quiet) cout << name << " took " << dmg << " damage!" << endl;
	if (curHP == 0 && !game->quiet) cout << name << " fainted!" << endl;
	return curHP;
}

int Pokemon::recoil(int dmg) {
	if (ability == MAGIC_GUARD) return curHP;
	curHP -= dmg;
	if (curHP < 0) curHP = 0;
	if (curHP == 0 && !game->quiet) cout << name << " fainted!" << endl;
	return curHP;
}

int Pokemon::boost(int statID, int stages) {
	if (ability == CONTRARY) {
		return lower(statID, stages);
	}
	string adj, stat;
	int* modifier;
	switch (statID) {
	case ATK:
		modifier = &mAtk;
		stat = "Attack";
		break;
	case DEF:
		modifier = &mDef;
		stat = "Defense";
		break;
	case SPA:
		modifier = &mSpA;
		stat = "Special Attack";
		break;
	case SPD:
		modifier = &mSpD;
		stat = "Special Defense";
		break;
	case SPE:
		modifier = &mSpe;
		stat = "Speed";
		break;
	case ACC:
		modifier = &mAcc;
		stat = "Accuracy";
		break;
	case EVA:
		modifier = &mEva;
		stat = "Evasion";
		break;
	}
	int m_stages = (ability == SIMPLE ? 2 * stages : stages);
	if (m_stages == 1) adj = " ";
	if (m_stages == 2) adj = " sharply ";
	if (m_stages > 2) adj = " drastically ";
	*modifier += m_stages;
	if (*modifier >= 6) *modifier = 6;
	if (!game->quiet) cout << name << "'s " << stat << adj << "increased!" << endl;
	return *modifier;
}

int Pokemon::lower(int statID, int stages) {
	if (ability == CONTRARY) {
		return lower(statID, stages);
	}
	string adj, stat;
	int* modifier;
	switch (statID) {
	case ATK:
		modifier = &mAtk;
		stat = "Attack";
		break;
	case DEF:
		modifier = &mDef;
		stat = "Defense";
		break;
	case SPA:
		modifier = &mSpA;
		stat = "Special Attack";
		break;
	case SPD:
		modifier = &mSpD;
		stat = "Special Defense";
		break;
	case SPE:
		modifier = &mSpe;
		stat = "Speed";
		break;
	case ACC:
		modifier = &mAcc;
		stat = "Accuracy";
		break;
	case EVA:
		modifier = &mEva;
		stat = "Evasion";
		break;
	}
	int m_stages = (ability == SIMPLE ? 2 * stages : stages);
	if (m_stages == 1) adj = " ";
	if (m_stages == 2) adj = " sharply ";
	if (m_stages > 2) adj = " drastically ";
	*modifier -= m_stages;
	if (*modifier < -6) *modifier = -6;
	if (!game->quiet) cout << name << "'s " << stat << adj << "decreased!" << endl;
	if (ability == DEFIANT) boost(ATK, 2);
	return *modifier;
}

int Pokemon::inflictStatus(int statusID) {
	if (side == 1 && game->safeguard1 ||
		side == 2 && game->safeguard2) return -1;
	if (ability == INSOMNIA && statusID == SLEEP) return -1;
	if (ability == LIMBER && statusID == PARALYZE) return -1;
	if (ability == IMMUNITY && statusID == POISON) return -1;
	if (type1 == FIRE || type2 == FIRE && statusID == BURN) return -1;
	if (type1 == ICE || type2 == ICE && statusID == FREEZE) return -1;
	switch (statusID) {
	case BURN:
		if (!game->quiet) cout << name << " was burned!" << endl;
		break;
	case FREEZE:
		if (!game->quiet) cout << name << " was frozen solid!" << endl;
		break;
	case PARALYZE:
		if (!game->quiet) cout << name << " was paralyzed!" << endl;
		break;
	case SLEEP:
		if (!game->quiet) cout << name << " fell asleep!" << endl;
		break;
	case POISON:
		if (!game->quiet) cout << name << " was poisoned!" << endl;
		break;
	}
	return status = statusID;
}

int Pokemon::flinch() {
	if (ability == INNER_FOCUS) return -1;
	if (!game->quiet) cout << name << " flinched!" << endl;
	return flinched = 1;
}

int Pokemon::use_move(Move* m, Pokemon* target) {
	if (!game->quiet) cout << name << " used " << m->name  << "!" << endl;
	int hits = 1, dmg = 0;
	if (m->flags & TWO_HIT) hits = 2;
	if (m->flags & N_HIT) {
		float rhits = randf();
		if (rhits < 0.33)
			hits = 2;
		else if (rhits < 0.67)
			hits = 3;
		else if (rhits < 0.84)
			hits = 4;
		else
			hits = 5;
	}
	for (int hit = 0; hit < hits; hit++) {
		float racc = randf();
		float macc = m->acc(this) * getAcc() / target->getEva() / 100;
		if (macc == 0) macc = 1.0;
		if (racc > macc) {
			if (!game->quiet) cout << target->name << " avoided the attack!" << endl;
			return 0;
		}
		if (!checkNegatingAbility(this, target, m)) return 0;
		dmg = m->exec(this, target);
		if (dmg > 0 && item == LIFE_ORB) {
			if (!game->quiet) cout << name << " hung on to life!" << endl;
			recoil(maxHP / 10);
		}
		if (item == SHELL_BELL) curHP += dmg / 8;
	}
	m->curPP--;
	return dmg;
}

int Pokemon::use(int move_index, Pokemon* target) {
	if (dmove_flags & (1 << move_index)) {
		cout << "This move is disabled!" << endl;
		lastidx = NONE;
	}
	lastidx = move_index;
	return use_move(moves[move_index], target);
}

float Move::acc(Pokemon* poke) {
	return _acc * (poke->game->gravity ? 1.3 : 1.0) * (poke->ability == HUSTLE && category == PHYSICAL ? 0.8: 1.0);
}

int Move::bp(Pokemon* poke) {
	float mul = 1.0;
	mul *= (poke->ability == TECHNICIAN && _bp <= 60 ? 1.5 : 1.0);
	mul *= (poke->flash_fire && type == FIRE ? 1.5 : 1.0);
	mul *= (poke->ability == FAIRY_AURA && type == FAIRY ||
		poke->ability == DARK_AURA && type == DARK ? 1.3 : 1.0);
	mul *= (poke->ability == SHEER_FORCE && flags & SEC_EFFECT ? 1.3 : 1.0);
	mul *= (poke->ability == RECKLESS && flags & RECOIL ? 1.3 : 1.0);
	return (int) (_bp * mul);
}

int Move::exec(Pokemon* user, Pokemon* target) {
	int dmg = calcDmg(user, target, this);
	target->takeDmg(dmg);
	return dmg;
}

GameState::GameState() {
	active1 = 0;
	active2 = 6;
	weather = NONE;
}