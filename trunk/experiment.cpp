#include <iostream>
#include <time.h>
#include <math.h>
#include "board.h"
#include "player.h"
#include "game.h"
#include "ai.h"
#include "experiment.h"

/* methods of the experiment class */

// class constructor
EXPERIMENT::EXPERIMENT(const BOARD &_board, PCOLOR _ptype, int _minExp, int _maxExp, double _Covar, int _minLvl, int _maxLvl):
	minExp(_minExp), maxExp(_maxExp), Covar(_Covar), minLvl(_minLvl), maxLvl(_maxLvl)
{
	board = _board;
	ptype = _ptype;
};

void EXPERIMENT::run(PGAMER plr) {
	if (plr == HUMAN) exit(1);
	board.start_move(ptype);
	PLAYER *player = GAME::createPlayer(plr);
	player->setType(ptype);
	std::cout << "Player: " << PLAYER::getPlrText(plr) << std::endl;
	time_t start_time, end_time;
	// go round need levels
	for (int n = minLvl; n <= maxLvl; n++) {
		player->setLevel(n);
		times_array times;
		double M = -1.0;
		READY_STATE res;
		// make experiment for current level
		int k = 0;
		while ((res = isReady(times, M)) == EXP_NOREADY) {
			start_time = time(NULL);
			player->get_move(board);
			end_time = time(NULL);
			// adds time difference to array
			//std::cout << "[" << ++k << "] time: " << difftime(end_time, start_time) << std::endl;
			times.push_back(difftime(end_time, start_time));
		}
		// remember results
		std::cout << n << " | ";
		switch (res) {
			case EXP_READY_MAXEXP: std::cout << "maxexp"; break;
			case EXP_READY_COVAR:  std::cout << "covar"; break;
		}
		std::cout << " | " << M << std::endl;
	}
	std::cout << std::endl;
	delete player;
}

READY_STATE EXPERIMENT::isReady(const times_array &times, double &M) {
	// detect minExp
	if (times.size() < minExp) return EXP_NOREADY;
	
	// exit with maxExp
	if (times.size() >= maxExp) return EXP_READY_MAXEXP;
	
	// calculate covar
	M = 0;
	double M2 = 0, D = 0, covar;
	for (int i = 0; i < times.size(); i++) {
		M += times[i];
		M2 += pow(times[i], 2);
	}
	M /= (double)times.size();
	M2 /= (double)times.size();
	D = M2 - pow(M, 2);
	covar = sqrt(D)/M;
	if (covar <= Covar) return EXP_READY_COVAR;
	
	// continue experiment
	return EXP_NOREADY;
}

