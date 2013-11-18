#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

#include "pokemon.h"
#include "util.h"
#include "constants.h"
#include "moves.h"

using namespace std;

int main(int argc, char** argv) {
	srand (time(NULL));

	Pokemon mons[12];
	GameState g;

	for (int i = 0; i < 12; i++) mons[i].game = &g;

	newGame(&g, mons);
	newPoke(&mons[0], "Reshiram", 100, 120, 100, 150, 120, 90, FIRE, DRAGON, TURBOBLAZE, 0);
	newPoke(&mons[1], "Kyogre", 100, 100, 90, 150, 140, 90, WATER, NONE, DRIZZLE, 0);
	invest(&mons[0], CHOICE_SPECS, 4, 0, 0, 252, 0, 252, 31, 31, 31, 31, 31, 31);
	invest(&mons[0], CHOICE_SCARF, 4, 0, 0, 252, 0, 252, 31, 31, 31, 31, 31, 31);

#include "movetab.h"

	setMoves(&mons[0], mtab, ACROBATICS, AQUA_TAIL, AEROBLAST, AGILITY);
	mons[0].use(mons[0].moves[1], &mons[1]);

	return 0;
}