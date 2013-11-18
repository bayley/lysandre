#ifndef __MOVES_H
#define __MOVES_H

#include <iostream>
#include <cstdlib>

#include "pokemon.h"
#include "util.h"
#include "constants.h"

using namespace std;

#define SG_FACTOR (user->ability == SERENE_GRACE ? 2.0 : 1.0)
#define secondaryEffect(p,a) if (randf() < p * SG_FACTOR / 100 && !(user->ability == SHEER_FORCE)) a
#define setParams(n, b, a, i, t, p, c, f) name = n; _bp = b; _acc = a; id = i; type = t; priority = p; category = c; flags = f
#define MOVE(n) class n: public Move {public

MOVE(Acrobatics):
	Acrobatics() {
		setParams("Acrobatics", 55, 100, ACROBATICS, FLYING, 0, PHYSICAL, CONTACT);
	}
	int exec(Pokemon* user,Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if (user->item < 0) dmg *= 2;
		target->takeDmg(dmg);
		return dmg;
	}
};
MOVE(Acupressure):
	Acupressure() {
		setParams("Acupressure", 0, 0, ACUPRESSURE, NORMAL, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int rnd = rand() % 7;
		user->boost(rnd, 1);
		return 0;
	}
};
MOVE(Aeroblast):
	Aeroblast() {
		setParams("Aeroblast", 100, 100, AEROBLAST, FLYING, 0, SPECIAL, HIGH_CH);
	}
};
MOVE(Agility):
	Agility() {
		setParams("Agility", 0, 0, AGILITY, PSYCHIC, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPE, 2);
		return 0;
	}
};
MOVE(AirSlash):
	AirSlash() {
		setParams("Air Slash", 70, 90, AIR_SLASH, FLYING, 0, SPECIAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(30, target->flinch());
		return dmg;
	}
};
MOVE(Amnesia):
	Amnesia() {
		setParams("Amnesia", 0, 0, AMNESIA, PSYCHIC, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPD, 2);
		return 0;
	}
};
MOVE(AncientPower):
	AncientPower() {
		setParams("AncientPower", 60, 100, ANCIENTPOWER, ROCK, 0, SPECIAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(10, {
			user->boost(ATK, 1);
			user->boost(DEF, 1);
			user->boost(SPA, 1);
			user->boost(SPD, 1);
			user->boost(SPE, 1);
		});
		return dmg;
	}
};
MOVE(AquaJet):
	AquaJet() {
		setParams("Aqua Jet", 40, 100, AQUA_JET, WATER, 1, PHYSICAL, 0);
	}
};
MOVE(AquaRing):
	AquaRing() {
		setParams("Aqua Ring", 0, 0, AQUA_RING, WATER, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (user->side == 1) user->game->aqua1 = 1;
		if (user->side == 2) user->game->aqua2 = 1;
		return 0;
	}
};
MOVE(AquaTail):
	AquaTail() {
		setParams("Aqua Tail", 90, 90, AQUA_TAIL, WATER, 0, PHYSICAL, 0);
	}
};
MOVE(Aromatherapy):
	Aromatherapy() {
		setParams("Aromatherapy", 0, 0, AROMATHERAPY, GRASS, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		for (int i = 6 * (user->side); i < 6 * (user->side) + 6; i++) {
			(user->game->pokemon + i)->status = NONE;
		}
		return 0;
	}
};
MOVE(AttackOrder):
	AttackOrder() {
		setParams("Attack Order", 90, 100, ATTACK_ORDER, BUG, 0, PHYSICAL, HIGH_CH);
	}
};
MOVE(AuraSphere):
	AuraSphere() {
		setParams("Aura Sphere", 80, 100, AURA_SPHERE, FIGHTING, 0, SPECIAL, 0);
	}
};
MOVE(Barrier):
	Barrier() {
		setParams("Barrier", 0, 0, BARRIER, PSYCHIC, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 2);
		return 0;
	}
};
MOVE(BellyDrum):
	BellyDrum() {
		setParams("Belly Drum", 0, 0, BELLY_DRUM, NORMAL, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (user->curHP <= user->maxHP / 2) return 0;
		user->curHP -= user->maxHP / 2;
		user->mAtk = 6;
		if (!user->game->quiet) cout << user->name << " cut its HP and maximized its Attack!" << endl;
		return 0;
	}
};
MOVE(BlazeKick):
	BlazeKick() {
		setParams("Blaze Kick", 85, 100, BLAZE_KICK, FIRE, 0, PHYSICAL, CONTACT);
	}
};
MOVE(Blizzard):
	Blizzard() {
		setParams("Blizzard", 110, 70, BLIZZARD, ICE, 0, SPECIAL, SEC_EFFECT);
	}
	float acc(Pokemon *poke) {
		if (poke->game->weather == HAIL) return 0;
		return _acc;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(10, target->inflictStatus(FREEZE));
		return dmg;
	}
};
MOVE(BlueFlare):
	BlueFlare() {
		setParams("Blue Flare", 130, 85, BLUE_FLARE, FIRE, 0, SPECIAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		secondaryEffect(20, target->inflictStatus(BURN));
		target->takeDmg(dmg);
		return dmg;
	}
};
MOVE(BodySlam):
	BodySlam() {
		setParams("Body Slam", 80, 100, BODY_SLAM, NORMAL, 0, PHYSICAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		secondaryEffect(30, target->inflictStatus(PARALYZE));
		target->takeDmg(dmg);
		return dmg;
	}
};
MOVE(BoltStrike):
	BoltStrike() {
		setParams("Bolt Strike", 130, 85, BOLT_STRIKE, ELECTRIC, 0, PHYSICAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		secondaryEffect(20, target->inflictStatus(PARALYZE));
		target->takeDmg(dmg);
		return dmg;
	}
};
MOVE(Bonemerang):
	Bonemerang() {
		setParams("Bonemerang", 50, 100, BONEMERANG, GROUND, 0, PHYSICAL, TWO_HIT);
	}
};
MOVE(Bounce):
	Bounce() {
		setParams("Bounce", 80, 100, BOUNCE, FLYING, 0, PHYSICAL, TWO_TURN);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(30, target->inflictStatus(PARALYZE));
		return dmg;
	}
};
MOVE(BraveBird):
	BraveBird() {
		setParams("Brave Bird", 120, 100, BRAVE_BIRD, FLYING, 0, PHYSICAL, RECOIL);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		user->recoil(dmg / 4);
		return dmg;
	}
};
MOVE(BrickBreak):
	BrickBreak() {
		setParams("Brick Break", 75, 100, BRICK_BREAK, FIGHTING, 0, PHYSICAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (!(user->ability == SHEER_FORCE)) {
			if (target->side == 1) {
				target->game->lightscreen1 = 0;
				target->game->reflect1 = 0;
			}
			if (target->side == 2) {
				target->game->lightscreen2 = 0;
				target->game->reflect2 = 0;
			}
		}
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
MOVE(BugBite):
	BugBite()  {
		setParams("Bug Bite", 60, 100, BUG_BITE, BUG, 0, PHYSICAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if (target->item & F_BERRY && !(user->ability == SHEER_FORCE)) target->item = NONE;
		target->takeDmg(dmg);
		return dmg;
	}
};
MOVE(BugBuzz):
	BugBuzz() {
		setParams("Bug Buzz", 90, 100, BUG_BUZZ, BUG, 0, SPECIAL, SEC_EFFECT | SOUND_BASED);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(10, target->lower(SPD, 1));
		return dmg;
	}
};
MOVE(BulkUp):
	BulkUp() {
		setParams("Bulk Up", 0, 0, BULK_UP, FIGHTING, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->boost(ATK, 1);
		target->boost(DEF, 1);
		return 0;
	}
};
MOVE(BulletPunch):
	BulletPunch() {
		setParams("Bullet Punch", 40, 100, BULLET_PUNCH, STEEL, 0, PHYSICAL, 0);
	}
};
class BulletSeed: public Move {
public:
	BulletSeed() {
		setParams("Bullet Seed", 25, 100, BULLET_SEED, GRASS, 0, PHYSICAL, N_HIT);
	}
};
MOVE(CalmMind):
	CalmMind() {
		setParams("Calm Mind", 0, 0, CALM_MIND, PSYCHIC, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPA, 1);
		user->boost(SPD, 1);
		return 0;
	}
};
MOVE(ChargeBeam):
	ChargeBeam() {
		setParams("Charge Beam", 70, 90, CHARGE_BEAM, ELECTRIC, 0, SPECIAL, SEC_EFFECT);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		secondaryEffect(70, user->boost(SPA, 1));
		target->takeDmg(dmg);
		return dmg;
	}
};
MOVE(CircleThrow):
	CircleThrow() {
		setParams("Circle Throw", 60, 90, CIRCLE_THROW, FIGHTING, 0, PHYSICAL, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		int unphazeable = (target->ability == SUCTION_CUPS) || (target->side == 1 ? target->game->ingrain1 : target->game->ingrain2);
		target->takeDmg(dmg);
		if (target->curHP != 0 && !unphazeable) {
			int newactive = (target->side == 1 ? target->game->active1 : target->game->active2);
			while (newactive == (target->side == 1 ? target->game->active1 : target->game->active2)) {
				newactive = rand() % 6 + (target->side - 1) * 6;
			}
			if (target->side == 1) {
				target->game->active1 = newactive;
			} else {
				target->game->active2 = newactive;
			}
		}
		return dmg;
	}
};
MOVE(CloseCombat):
	CloseCombat() {
		setParams("Close Combat", 120, 100, CLOSE_COMBAT, FIGHTING, 0, PHYSICAL, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		user->lower(DEF, 1);
		user->lower(SPD, 1);
		return dmg;
	}
};
MOVE(Coil):
	Coil() {
		setParams("Coil", 0, 0, COIL, POISON, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(ATK, 1);
		user->boost(DEF, 1);
		user->boost(ACC, 1);
		return 0;
	}
};
MOVE(CosmicPower):
	CosmicPower() {
		setParams("Cosmic Power", 0, 0, COSMIC_POWER, PSYCHIC, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 1);
		user->boost(SPD, 1);
		return 0;
	}
};
MOVE(CottonGuard):
	CottonGuard() {
		setParams("Cotton Guard", 0, 0, COTTON_GUARD, GRASS, 0, STATUS, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 3);
		return 0;
	}
};
class Counter: public Move {
public:
	Counter() {
		setParams("Counter", 1, 100, COUNTER, FIGHTING, -5, PHYSICAL, 0);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->takeDmg(2 * user->game->lastdmg);
	}
};
class CrabHammer: public Move {
public:
	CrabHammer() {
		setParams("Crabhammer", 80, 90, CRABHAMMER, WATER, 0, PHYSICAL, HIGH_CH);
	}
};
class CrossChop: public Move {
public:
	CrossChop() {
		setParams("Cross Chop", 80, 100, CROSS_CHOP, FIGHTING, 0, PHYSICAL, HIGH_CH);
	}
};
#endif