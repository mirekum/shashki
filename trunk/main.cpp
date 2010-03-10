#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <cstdlib>
#include <ncurses.h>

#include "board.h"
#include "player.h"
#include "human.h"
#include "ai.h"
#include "game.h"

using namespace std;

// точка входа
int main () {
	// белые, чёрные
	GAME shashki(AI2, AI);
	return 0;
}

