#ifndef __MOVES_H
#define __MOVES_H

#include <iostream>
#include <cstdlib>

#include "pokemon.h"
#include "util.h"
#include "constants.h"

using namespace std;

#define SG_FACTOR (user->ability == SERENE_GRACE ? 2.0 : 1.0)

class Acrobatics: public Move {
public:
	Acrobatics() {
		name = "Acrobatics";
		_bp = 55;
		_acc = 100;
		id = ACROBATICS;
		type = FLYING;
		priority = 0;
		category = PHYSICAL;
		flags = CONTACT;
	}
	int exec(Pokemon* user,Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if (user->item < 0) dmg *= 2;
		target->takeDmg(dmg);
		return dmg;
	}
};

class Acupressure: public Move {
public:
	Acupressure() {
		name = "Acupressure";
		_bp = 0;
		_acc = 0;
		id = ACUPRESSURE;
		type = NORMAL;
		priority = 0;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int rnd = rand() % 7;
		user->boost(rnd, 1);
		return 0;
	}
};
class Aeroblast: public Move {
public:
	Aeroblast() {
		name = "Aeroblast";
		_bp = 100;
		_acc = 100;
		id = AEROBLAST;
		type = FLYING;
		priority = 0;
		category = SPECIAL;
		flags = HIGH_CH;
	}
	int exec(Pokemon* user,Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class Agility: public Move {
public:
	Agility() {
		name = "Agility";
		_bp = 0;
		_acc = 0;
		id = AGILITY;
		type = PSYCHIC;
		priority = 0;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPE, 2);
		if (user->mSpe > 6) user->mSpe = 6;
		if (user->mSpe < -6) user->mSpe = -6;
		return 0;
	}
};
class AirSlash: public Move {
public:
	AirSlash() {
		name = "Air Slash";
		_bp = 70;
		_acc = 100;
		id = AIR_SLASH;
		type = FLYING;
		priority = 0;
		category = SPECIAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		float rval = (float) rand() / RAND_MAX;
		if (rval < 0.3 * SG_FACTOR) target->flinch();
		return dmg;
	}
};
class Amnesia: public Move {
public:
	Amnesia() {
		name = "Amensia";
		_bp = 0;
		_acc = 0;
		id = AMNESIA;
		type = PSYCHIC;
		priority = 0;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPD, 2);
		return 0;
	}
};
class AncientPower: public Move {
public:
	AncientPower() {
		name = "Ancient Power";
		_bp = 60;
		_acc = 100;
		id = ANCIENTPOWER;
		type = ROCK;
		priority = 0;
		category = SPECIAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		float rval = (float) rand() / RAND_MAX;
		if (rval < 0.1 * SG_FACTOR) {
			user->boost(ATK, 1);
			user->boost(DEF, 1);
			user->boost(SPA, 1);
			user->boost(SPD, 1);
			user->boost(SPE, 1);
		}
		return dmg;
	}
};
class PriorityPhysical: public Move {
public:
	PriorityPhysical(string s, int t, int i) {
		name = s;
		_bp = 40;
		_acc = 100;
		id = i;
		type = t;
		priority = 1;
		category = PHYSICAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class AquaJet: public PriorityPhysical {
public:
	AquaJet() 
		:PriorityPhysical("Aqua Jet", WATER, AQUA_JET) {
	}
};
class AquaRing: public Move {
public:
	AquaRing() {
		name = "Aqua Ring";
		_bp = 0;
		_acc = 0;
		id = AQUA_RING;
		type = WATER;
		priority = 0;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (user->side == 1) user->game->aqua1 = 1;
		if (user->side == 2) user->game->aqua2 = 1;
		return 0;
	}
};
class AquaTail: public Move {
public:
	AquaTail() {
		name = "Aqua Tail";
		_bp = 90;
		_acc = 90;
		id = AQUA_TAIL;
		type = WATER;
		priority = 0;
		category = PHYSICAL;
		flags = CONTACT;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class Aromatherapy: public Move {
public:
	Aromatherapy() {
		name = "Aromatherapy";
		_bp = 0;
		_acc = 0;
		id = AROMATHERAPY;
		type = GRASS;
		priority = 0;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		for (int i = 6 * (user->side); i < 6 * (user->side) + 6; i++) {
			(user->game->pokemon + i)->status = -1;
		}
		return 0;
	}
};
class AttackOrder: public Move {
public:
	AttackOrder() {
		name = "Attack Order";
		_bp = 90;
		_acc = 100;
		id = ATTACK_ORDER;
		type = BUG;
		priority = 0;
		category = PHYSICAL;
		flags = HIGH_CH;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class AuraSphere: public Move {
public:
	AuraSphere() {
		name = "Aura Sphere";
		_bp = 90;
		_acc = 0;
		id = AURA_SPHERE;
		type = FIGHTING;
		priority = 0;
		category = SPECIAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class Barrier: public Move {
public:
	Barrier() {
		name = "Barrier";
		_bp = 0;
		_acc = 0;
		id = BARRIER;
		type = PSYCHIC;
		priority = 0;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 2);
		return 0;
	}
};
class BellyDrum: public Move {
public:
	BellyDrum() {
		name = "Belly Drum";
		_bp = 0;
		_acc = 0;
		id = BELLY_DRUM;
		type = NORMAL;
		priority = 0;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (user->curHP <= user->maxHP / 2) return 0;
		user->curHP -= user->maxHP / 2;
		user->mAtk = 6;
		if (!user->game->quiet) cout << user->name << " cut its HP and maximized its Attack!" << endl;
		return 0;
	}
};
class BlazeKick: public Move {
public:
	BlazeKick() {
		name = "Blaze Kick";
		_bp = 85;
		_acc = 100;
		id = BLAZE_KICK;
		type = FIRE;
		priority = 0;
		category = PHYSICAL;
		flags = CONTACT;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		user->takeDmg(dmg);
		return dmg;
	}
};
class Blizzard: public Move {
public:
	Blizzard() {
		name = "Blizzard";
		_bp = 110;
		_acc = 70;
		id = BLIZZARD;
		type = ICE;
		priority = 0;
		category = SPECIAL;
	}
	float acc(Pokemon *poke) {
		if (poke->game->weather == HAIL) return 0;
		return _acc;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class BlueFlare: public Move {
public:
	BlueFlare() {
		name = "Blue Flare";
		_bp = 130;
		_acc = 85;
		id = BLUE_FLARE;
		type = FIRE;
		priority = 0;
		category = SPECIAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if ((float) rand() / RAND_MAX < 0.2 && target->status == NONE) target->status = BURN;
		target->takeDmg(dmg);
		return dmg;
	}
};
class BodySlam: public Move {
public:
	BodySlam() {
		name = "Body Slam";
		_bp = 80;
		_acc = 100;
		id = BODY_SLAM;
		type = NORMAL;
		priority = 0;
		category = PHYSICAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if ((float) rand() / RAND_MAX < 0.3 && target->status == NONE) target->status = PARALYZE;
		target->takeDmg(dmg);
		return dmg;
	}
};
class BoltStrike: public Move {
public:
	BoltStrike() {
		name = "Bolt Strike";
		_bp = 130;
		_acc = 85;
		id = BOLT_STRIKE;
		type = ELECTRIC;
		priority = 0;
		category = PHYSICAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if ((float) rand() / RAND_MAX < 0.2 && target->status == NONE) target->status = PARALYZE;
		target->takeDmg(dmg);
		return dmg;
	}
};
class Bonemerang: public Move {
public:
	Bonemerang() {
		name = "Bonemerang";
		_bp = 50;
		_acc = 100;
		id = BONEMERANG;
		type = GROUND;
		priority = 0;
		category = PHYSICAL;
		flags = TWO_HIT;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class Bounce: public Move {
public:
	Bounce() {
		name = "Bounce";
		_bp = 80;
		_acc = 100;
		id = BOUNCE;
		type = FLYING;
		priority = 0;
		category = PHYSICAL;
		flags = TWO_TURN;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class BraveBird: public Move {
public:
	BraveBird() {
		name = "Brave Bird";
		_bp = 120;
		_acc = 100;
		id = BOUNCE;
		type = FLYING;
		priority = 0;
		category = PHYSICAL;
		flags = RECOIL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		user->recoil(dmg / 4);
		return dmg;
	}
};
class BrickBreak: public Move {
public:
	BrickBreak() {
		name = "Brick Break";
		_bp = 75;
		_acc = 100;
		id = BRICK_BREAK;
		type = FIGHTING;
		priority = 0;
		category = PHYSICAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (target->side == 1) {
			target->game->lightscreen1 = 0;
			target->game->reflect1 = 0;
		}
		if (target->side == 2) {
			target->game->lightscreen2 = 0;
			target->game->reflect2 = 0;
		}
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class BugBite: public Move {
public:
	BugBite()  {
		name = "Bug Bite";
		_bp = 60;
		_acc = 100;
		id = BUG_BITE;
		type = BUG;
		priority = 0;
		category = PHYSICAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if (target->item & F_BERRY) target->item = NONE;
		target->takeDmg(dmg);
		return dmg;
	}
};
class BugBuzz: public Move {
public:
	BugBuzz() {
		name = "Bug Buzz";
		_bp = 90;
		_acc = 100;
		id = BUG_BUZZ;
		type = BUG;
		category = SPECIAL;
		flags = SOUND_BASED;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		if ((float) rand() / RAND_MAX < 0.1) target->lower(SPD, 1);
		return dmg;
	}
};
class BulkUp: public Move {
public:
	BulkUp() {
		name = "Bulk Up";
		_bp = 0;
		_acc = 0;
		id = BULK_UP;
		type = FIGHTING;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->boost(ATK, 1);
		target->boost(DEF, 1);
		return 0;
	}
};
class BulletPunch: public PriorityPhysical {
public:
	BulletPunch() 
		:PriorityPhysical("Bullet Punch", STEEL, BULLET_PUNCH) {
	}
};
class BulletSeed: public Move {
public:
	BulletSeed() {
		name = "Bullet Seed";
		_bp = 25;
		_acc = 100;
		id = BULLET_SEED;
		type = GRASS;
		category = PHYSICAL;
		flags = N_HIT;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class CalmMind: public Move {
public:
	CalmMind() {
		name = "Calm Mind";
		_bp = 0;
		_acc = 0;
		id = CALM_MIND;
		type = PSYCHIC;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPA, 1);
		user->boost(SPD, 1);
		return 0;
	}
};
class ChargeBeam: public Move {
public:
	ChargeBeam() {
		name = "Charge Beam";
		_bp = 70;
		_acc = 90;
		id = CHARGE_BEAM;
		type = ELECTRIC;
		category = SPECIAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		if ((float) rand() / RAND_MAX < 0.7) user->boost(SPA, 1);
		target->takeDmg(dmg);
		return dmg;
	}
};
class CircleThrow: public Move {
public:
	CircleThrow() {
		name = "Circle Throw";
		_bp = 60;
		_acc = 90;
		id = CIRCLE_THROW;
		type = FIGHTING;
		category = PHYSICAL;
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
class CloseCombat: public Move {
public:
	CloseCombat() {
		name = "Close Combat";
		_bp = 120;
		_acc = 100;
		id = CLOSE_COMBAT;
		type = FIGHTING;
		category = PHYSICAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		user->lower(DEF, 1);
		user->lower(SPD, 1);
		return dmg;
	}
};
class Coil: public Move {
public:
	Coil() {
		name = "Coil";
		_bp = 0;
		_acc = 0;
		id = COIL;
		type = POISON;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(ATK, 1);
		user->boost(DEF, 1);
		user->boost(ACC, 1);
		return 0;
	}
};
class CosmicPower: public Move {
public:
	CosmicPower() {
		name = "Cosmic Power";
		_bp = 0;
		_acc = 0;
		id = COSMIC_POWER;
		type = PSYCHIC;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 1);
		user->boost(SPD, 1);
		return 0;
	}
};
class CottonGuard: public Move {
public:
	CottonGuard() {
		name = "Cotton Guard";
		_bp = 0;
		_acc = 0;
		id = COTTON_GUARD;
		type = GRASS;
		category = STATUS;
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 3);
		return 0;
	}
};
class Counter: public Move {
public:
	Counter() {
		name = "Counter";
		_bp = 1;
		_acc = 100;
		id = COUNTER;
		type = FIGHTING;
		category = PHYSICAL;
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->takeDmg(2 * user->game->lastdmg);
	}
};
class CrabHammer: public Move {
public:
	CrabHammer() {
		name = "Crabhammer";
		_bp = 80;
		_acc = 90;
		id = CRABHAMMER;
		type = WATER;
		category = PHYSICAL;
		flags = HIGH_CH;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
class CrossChop: public Move {
public:
	CrossChop() {
		name = "Cross Chop";
		_bp = 80;
		_acc = 100;
		id = CROSS_CHOP;
		type = FIGHTING;
		category = PHYSICAL;
		flags = HIGH_CH;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		return dmg;
	}
};
#endif