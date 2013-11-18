#ifndef __MOVES_H
#define __MOVES_H

#include <iostream>
#include <cstdlib>

#include "pokemon.h"
#include "util.h"
#include "constants.h"

using namespace std;

#define SG_FACTOR (user->ability == SERENE_GRACE ? 2.0 : 1.0)
#define secondaryEffect(p,a) if (randf() < p * SG_FACTOR / 100 && !(user->ability == SHEER_FORCE) && dmg != 0) a
#define setParams(n, b, a, i, t, p, c, f, q) name = n; _bp = b; _acc = a; id = i; type = t; priority = p; category = c; flags = f; maxPP = curPP = q
#define MOVE(n) class n: public Move {public

MOVE(Acrobatics):
	Acrobatics() {
		setParams("Acrobatics", 55, 100, ACROBATICS, FLYING, 0, PHYSICAL, CONTACT, 24);
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
		setParams("Acupressure", 0, 0, ACUPRESSURE, NORMAL, 0, STATUS, 0, 48);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int rnd = rand() % 7;
		user->boost(rnd, 1);
		return 0;
	}
};
MOVE(Aeroblast):
	Aeroblast() {
		setParams("Aeroblast", 100, 100, AEROBLAST, FLYING, 0, SPECIAL, HIGH_CH, 8);
	}
};
MOVE(Agility):
	Agility() {
		setParams("Agility", 0, 0, AGILITY, PSYCHIC, 0, STATUS, 0, 48);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPE, 2);
		return 0;
	}
};
MOVE(AirSlash):
	AirSlash() {
		setParams("Air Slash", 70, 90, AIR_SLASH, FLYING, 0, SPECIAL, SEC_EFFECT, 32);
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
		setParams("Amnesia", 0, 0, AMNESIA, PSYCHIC, 0, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPD, 2);
		return 0;
	}
};
MOVE(AncientPower):
	AncientPower() {
		setParams("AncientPower", 60, 100, ANCIENTPOWER, ROCK, 0, SPECIAL, SEC_EFFECT, 8);
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
		setParams("Aqua Jet", 40, 100, AQUA_JET, WATER, 1, PHYSICAL, 0, 32);
	}
};
MOVE(AquaRing):
	AquaRing() {
		setParams("Aqua Ring", 0, 0, AQUA_RING, WATER, 0, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (user->side == 1) user->game->aqua1 = 1;
		if (user->side == 2) user->game->aqua2 = 1;
		return 0;
	}
};
MOVE(AquaTail):
	AquaTail() {
		setParams("Aqua Tail", 90, 90, AQUA_TAIL, WATER, 0, PHYSICAL, 0, 16);
	}
};
MOVE(Aromatherapy):
	Aromatherapy() {
		setParams("Aromatherapy", 0, 0, AROMATHERAPY, GRASS, 0, STATUS, 0, 8);
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
		setParams("Attack Order", 90, 100, ATTACK_ORDER, BUG, 0, PHYSICAL, HIGH_CH, 24);
	}
};
MOVE(AuraSphere):
	AuraSphere() {
		setParams("Aura Sphere", 80, 100, AURA_SPHERE, FIGHTING, 0, SPECIAL, 0, 24);
	}
};
MOVE(Barrier):
	Barrier() {
		setParams("Barrier", 0, 0, BARRIER, PSYCHIC, 0, STATUS, 0, 48);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 2);
		return 0;
	}
};
MOVE(BellyDrum):
	BellyDrum() {
		setParams("Belly Drum", 0, 0, BELLY_DRUM, NORMAL, 0, STATUS, 0, 16);
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
		setParams("Blaze Kick", 85, 90, BLAZE_KICK, FIRE, 0, PHYSICAL, CONTACT | HIGH_CH | SEC_EFFECT, 16);
	}
};
MOVE(Blizzard):
	Blizzard() {
		setParams("Blizzard", 110, 70, BLIZZARD, ICE, 0, SPECIAL, SEC_EFFECT, 8);
	}
	float acc(Pokemon *poke) {
		if (poke->ability == NO_GUARD) return 0;
		if (poke->game->weather == HAIL) return 0;
		return _acc;
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(10, target->inflictStatus(FREEZE));
		return dmg;
		return 0;
	}
};
MOVE(BlueFlare):
	BlueFlare() {
		setParams("Blue Flare", 130, 85, BLUE_FLARE, FIRE, 0, SPECIAL, SEC_EFFECT, 8);
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
		setParams("Body Slam", 80, 100, BODY_SLAM, NORMAL, 0, PHYSICAL, SEC_EFFECT, 24);
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
		setParams("Bolt Strike", 130, 85, BOLT_STRIKE, ELECTRIC, 0, PHYSICAL, SEC_EFFECT, 8);
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
		setParams("Bonemerang", 50, 100, BONEMERANG, GROUND, 0, PHYSICAL, TWO_HIT, 16);
	}
};
MOVE(Bounce):
	Bounce() {
		setParams("Bounce", 80, 100, BOUNCE, FLYING, 0, PHYSICAL, TWO_TURN, 8);
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
		setParams("Brave Bird", 120, 100, BRAVE_BIRD, FLYING, 0, PHYSICAL, RECOIL, 24);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		user->recoil(dmg / 3);
		return dmg;
	}
};
MOVE(BrickBreak):
	BrickBreak() {
		setParams("Brick Break", 75, 100, BRICK_BREAK, FIGHTING, 0, PHYSICAL, SEC_EFFECT, 24);
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
		setParams("Bug Bite", 60, 100, BUG_BITE, BUG, 0, PHYSICAL, SEC_EFFECT, 32);
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
		setParams("Bug Buzz", 90, 100, BUG_BUZZ, BUG, 0, SPECIAL, SEC_EFFECT | SOUND_BASED, 16);
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
		setParams("Bulk Up", 0, 0, BULK_UP, FIGHTING, 0, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->boost(ATK, 1);
		target->boost(DEF, 1);
		return 0;
	}
};
MOVE(BulletPunch):
	BulletPunch() {
		setParams("Bullet Punch", 40, 100, BULLET_PUNCH, STEEL, 0, PHYSICAL, 0, 48);
	}
};
class BulletSeed: public Move {
public:
	BulletSeed() {
		setParams("Bullet Seed", 25, 100, BULLET_SEED, GRASS, 0, PHYSICAL, N_HIT, 48);
	}
};
MOVE(CalmMind):
	CalmMind() {
		setParams("Calm Mind", 0, 0, CALM_MIND, PSYCHIC, 0, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(SPA, 1);
		user->boost(SPD, 1);
		return 0;
	}
};
MOVE(ChargeBeam):
	ChargeBeam() {
		setParams("Charge Beam", 50, 90, CHARGE_BEAM, ELECTRIC, 0, SPECIAL, SEC_EFFECT, 16);
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
		setParams("Circle Throw", 60, 90, CIRCLE_THROW, FIGHTING, 0, PHYSICAL, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		int unphazeable = (target->ability == SUCTION_CUPS) || (target->side == 1 ? target->game->ingrain1 : target->game->ingrain2);
		target->takeDmg(dmg);
		if (target->curHP != 0 && !unphazeable && dmg != 0) {
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
		setParams("Close Combat", 120, 100, CLOSE_COMBAT, FIGHTING, 0, PHYSICAL, 0, 8);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		if (dmg != 0) {
			user->lower(DEF, 1);
			user->lower(SPD, 1);
		}
		return dmg;
	}
};
MOVE(Coil):
	Coil() {
		setParams("Coil", 0, 0, COIL, POISON, 0, STATUS, 0, 32);
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
		setParams("Cosmic Power", 0, 0, COSMIC_POWER, PSYCHIC, 0, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 1);
		user->boost(SPD, 1);
		return 0;
	}
};
MOVE(CottonGuard):
	CottonGuard() {
		setParams("Cotton Guard", 0, 0, COTTON_GUARD, GRASS, 0, STATUS, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(DEF, 3);
		return 0;
	}
};
MOVE(Counter):
	Counter() {
		setParams("Counter", 1, 100, COUNTER, FIGHTING, -5, PHYSICAL, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->takeDmg(2 * user->lastdmg);
	}
};
MOVE(CrabHammer):
	CrabHammer() {
		setParams("Crabhammer", 90, 90, CRABHAMMER, WATER, 0, PHYSICAL, HIGH_CH, 16);
	}
};
MOVE(CrossChop):
	CrossChop() {
		setParams("Cross Chop", 100, 80, CROSS_CHOP, FIGHTING, 0, PHYSICAL, HIGH_CH, 8);
	}
};
MOVE(CrossPoison):
	CrossPoison() {
		setParams("Cross Poison", 70, 100, CROSS_POISON, POISON, 0, PHYSICAL, HIGH_CH | SEC_EFFECT, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(10, target->inflictStatus(POISON));
	}
};
MOVE(Crunch):
	Crunch() {
		setParams("Crunch", 80, 100, CRUNCH, DARK, 0, PHYSICAL, CONTACT | SEC_EFFECT, 24);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(20, target->lower(DEF, 1));
	}
};
MOVE(CrushClaw):
	CrushClaw() {
		setParams("Crush Claw", 75, 100, CRUSH_CLAW, NORMAL, 0, PHYSICAL, CONTACT | SEC_EFFECT, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(50, target->lower(DEF, 1));
	}
};
MOVE(Curse):
	Curse() {
		setParams("Curse", 0, 0, CURSE, GHOST, 0, STATUS, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(ATK, 1);
		user->boost(DEF, 1);
		user->lower(SPE, 1);
	}
};
MOVE(DarkPulse):
	DarkPulse() {
		setParams("Dark Pulse", 80, 100, DARK_PULSE, DARK, 0, SPECIAL, SEC_EFFECT, 24);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(20, target->flinch());
	}
};
MOVE(DarkVoid):
	DarkVoid() {
		setParams("Dark Void", 0, 80, DARK_VOID, DARK, 0, STATUS, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->inflictStatus(SLEEP);
	}
};
MOVE(Defog):
	Defog() {
		setParams("Defog", 0, 0, DEFOG, NORMAL, 0, STATUS, 0, 24);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->game->rocks1 = target->game->rocks2 = 0;
		target->game->spikes1 = target->game->spikes2 = 0;
		target->lower(EVA, 1);
		return 0;
	}
};
MOVE(DestinyBond):
	DestinyBond() { 
		setParams("Destiny Bond", 0, 0, DESTINY_BOND, 0, GHOST, STATUS, 0, 8);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->destined = 1;
		target->dbPartner = user;
		return 0;
	}
};
MOVE(Disable):
	Disable() {
		setParams("Disable", 0, 0, DISABLE, 0, GHOST, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		if (target->lastidx >= 0) {
			target->dmove_flags |= (1 << target->lastidx);
		}
		return 0;
	}
};
MOVE(Discharge):
	Discharge() {
		setParams("Discharge", 80, 100, DISCHARGE, 0, ELECTRIC, SPECIAL, SEC_EFFECT, 24);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(30, target->inflictStatus(PARALYZE));
	}
};
MOVE(DoubleTeam):
	DoubleTeam() {
		setParams("Double Team", 0, 0, DOUBLE_TEAM, 0, PSYCHIC, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(EVA, 1);
	}
};
MOVE(DoubleEdge):
	DoubleEdge() {
		setParams("Double Edge", 120, 100, DOUBLE_EDGE, 0, NORMAL, PHYSICAL, RECOIL, 24);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		user->recoil(dmg / 3);
		return dmg;
	}
};
MOVE(DracoMeteor):
	DracoMeteor() {
		setParams("Draco Meteor", 120, 90, DRACO_METEOR, 0, DRAGON, SPECIAL, 0, 8);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		if (dmg != 0) user->lower(SPA, 2);
		return dmg;
	}
};
MOVE(DragonClaw):
	DragonClaw() {
		setParams("Dragon Claw", 80, 100, DRAGON_CLAW, 0, DRAGON, PHYSICAL, 0, 24);
	}
};
MOVE(DragonDance):
	DragonDance() {
		setParams("Dragon Dance", 0, 0, DRAGON_DANCE, 0, DRAGON, STATUS, 0, 32);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->boost(ATK, 1);
		user->boost(SPE, 1);
		return 0;
	}
};
MOVE(DragonPulse):
	DragonPulse() {
		setParams("Dragon Pulse", 85, 100, DRAGON_PULSE, 0, DRAGON, SPECIAL, 0, 15);
	}
};
MOVE(DragonRush):
	DragonRush() {
		setParams("Dragon Rush", 100, 75, DRAGON_RUSH, 0, DRAGON, PHYSICAL, SEC_EFFECT, 15);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(20, target->flinch());
		return dmg;
	}
};
MOVE(DragonTail):
	DragonTail() {
		setParams("Dragon Tail", 60, 90, DRAGON_TAIL, DRAGON, 0, PHYSICAL, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		int unphazeable = (target->ability == SUCTION_CUPS) || (target->side == 1 ? target->game->ingrain1 : target->game->ingrain2);
		target->takeDmg(dmg);
		if (target->curHP != 0 && !unphazeable && dmg != 0) {
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
MOVE(DrainPunch):
	DrainPunch() {
		setParams("Drain Punch", 75, 100, DRAIN_PUNCH, FIGHTING, 0, PHYSICAL, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		int lastHP = target->curHP;
		int newHP = target->takeDmg(dmg);
		int taken = lastHP - newHP;
		user->absorb(target, taken / 2);
		return dmg;
	}
};
MOVE(DrillPeck):
	DrillPeck() {
		setParams("Drill Peck", 80, 100, DRILL_PECK, FLYING, 0, PHYSICAL, 0, 32);
	}
};
MOVE(DrillRun):
	DrillRun() {
		setParams("Drill Run", 80, 100, DRILL_RUN, GROUND, 0, PHYSICAL, HIGH_CH, 16);
	}
};
MOVE(DualChop):
	DualChop() {
		setParams("Dual Chop", 40, 100, DUAL_CHOP, DRAGON, 0, PHYSICAL, TWO_HIT, 14);
	}
};
MOVE(DynamicPunch):
	DynamicPunch() {
		setParams("DynamicPunch", 100, 50, DYNAMICPUNCH, FIGHTING, 0, PHYSICAL, SEC_EFFECT, 8);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(100, target->confuse());
		return dmg;
	}
};
MOVE(EarthPower):
	EarthPower() {
		setParams("Earth Power", 90, 100, EARTH_POWER, GROUND, 0, SPECIAL, SEC_EFFECT, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(10, target->lower(SPD, 1));
		return dmg;
	}
};
MOVE(Earthquake):
	Earthquake() {
		setParams("Earthquake", 100, 100, EARTHQUAKE, GROUND, 0, PHYSICAL, 0, 16);
	}
};
MOVE(Encore):
	Encore() {
		setParams("Encore", 0, 0, ENCORE, NORMAL, 0, STATUS, 0, 8);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->encored = 1;
		return 0;
	}
};
MOVE(Endeavor):
	Endeavor() {
		setParams("Endeavor", 1, 100, ENDEAVOR, NORMAL, 0, PHYSICAL, 0, 8);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int lastHP = target->curHP;
		if (user->curHP < target->curHP) {
			target->curHP = user->curHP;
		} else {
			if (!user->game->quiet) cout << "But it failed!" << endl;
		}
		return lastHP - user->curHP;
	}
};
MOVE(Endure):
	Endure() {
		setParams("Endure", 0, 0, ENDURE, NORMAL, 0, STATUS, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		user->enduring = 1;
	}
};
MOVE(EnergyBall):
	EnergyBall() {
		setParams("Energy Ball", 80, 100, ENERGY_BALL, GRASS, 0, SPECIAL, 0, 16);
	}
	int exec(Pokemon* user, Pokemon* target) {
		int dmg = calcDmg(user, target, this);
		target->takeDmg(dmg);
		secondaryEffect(10, target->lower(SPD, 1));
		return dmg;
	}
};
MOVE(Entrainment):
	Entrainment() {
		setParams("Entrainment", 0, 0, ENTRAINMENT, NORMAL, 0, STATUS, 0, 24);
	}
	int exec(Pokemon* user, Pokemon* target) {
		target->ability = user->ability;
		return 0;
	}
};
MOVE(Eruption):
	Eruption() {
		setParams("Eruption", 150, 100, ERUPTION, FIRE, 0, SPECIAL, 0, 8);
	}
	int bp(Pokemon* poke) {
		return _bp * poke->curHP / poke->maxHP;
	}
};
#endif