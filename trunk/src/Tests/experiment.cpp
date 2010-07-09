#include <iostream>
#include <time.h>
#include <math.h>
#include "Model/board.h"
#include "Players/player.h"
#include "Model/game.h"
#include "Players/ai.h"
#include "Tests/experiment.h"

/* methods of the experiment class */

// class constructor
EXPERIMENT::EXPERIMENT(const BOARD &_board, COLOR _ptype, int _minExp, int _maxExp, double _Covar, int _minLvl, int _maxLvl):
	minExp(_minExp), maxExp(_maxExp), Covar(_Covar), minLvl(_minLvl), maxLvl(_maxLvl)
{
	board = _board;
	ptype = _ptype;
};

void EXPERIMENT::run(GAMER plr) {
	if (plr == 0) exit(1);
	board.startMove(ptype);
	PLAYER *player = GAME::createPlayer(plr);
	player->setType(ptype);
	std::cout << "Player: " << PLAYER::getPlrText(plr) << std::endl;
	time_t start_time, end_time;
	// go round need levels
	for (int n = minLvl; n <= maxLvl; n++) {
		player->setLevel(n);
		times_array times;
		double M = -1.0, covar = -1.0;
		READY_STATE res;
		// make experiment for current level
		int k = 0;
		while ((res = isReady(times, M, covar)) == EXP_NOREADY) {
			time(&start_time);
			player->getMove(board);
			time(&end_time);
			// adds time difference to array
			//std::cout << "[" << ++k << "] time: " << difftime(end_time, start_time) << " | " << covar << std::endl;
			times.push_back(difftime(end_time, start_time));
		}
		// remember results
		std::cout << n << " | ";
		switch (res) {
			case EXP_READY_MAXEXP: std::cout << "maxexp"; break;
			case EXP_READY_COVAR:  std::cout << "covar"; break;
		}
		std::cout << " | " << M << " | " << covar << std::endl;
	}
	std::cout << std::endl;
	delete player;
}

READY_STATE EXPERIMENT::isReady(const times_array &times, double &M, double &covar) {
	// detect minExp
	if (times.size() < minExp) return EXP_NOREADY;
	
	// calculate covar
	double M2 = 0, D = 0; M = 0;
	for (int i = 0; i < times.size(); i++) {
		M += times[i];
		M2 += pow(times[i], 2);
	}
	M /= (double)times.size();
	M2 /= (double)times.size();
	D = M2 - pow(M, 2);
	covar = sqrt(D)/M;
	if (covar <= Covar) return EXP_READY_COVAR;
	
	// exit with maxExp
	if (times.size() >= maxExp) return EXP_READY_MAXEXP;
	
	// continue experiment
	return EXP_NOREADY;
}

