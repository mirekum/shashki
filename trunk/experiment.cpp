#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include "board.h"
#include "player.h"
#include "game.h"
#include "experiment.h"

/* methods of the experiment class */

// class constructor
EXPERIMENT::EXPERIMENT(const BOARD &_board, int _minExp, int _maxExp, double _Covar, int _minLvl, int _maxLvl):
	minExp(_minExp), maxExp(_maxExp), Covar(_Covar), minLvl(_minLvl), maxLvl(_maxLvl)
{
	board = _board;
};

void EXPERIMENT::run(PGAMER plr, const std::string &filename) {
	if (plr == HUMAN) exit(1);
	PLAYER *player = GAME::createPlayer(plr);
	time_t start_time, end_time;
	// go round need levels
	for (int n = minLvl; n <= maxLvl; n++) {
		player->setLevel(n);
		std::vector<int> times;
		double M;
		READY_STATE res;
		// make experiment for current level
		while ((res = isReady(times, M)) == EXP_NOREADY) {
			time(&start_time);
			player->get_move(board);
			time(&end_time);
			// adds time difference to array
			times.push_back(difftime(end_time, start_time));
		}
		// remember results
		std::cout << filename << ": " << n << " | ";
		switch (res) {
			case EXP_READY_MAXEXP: std::cout << "maxexp"; break;
			case EXP_READY_COVAR:  std::cout << "covar "; break;
		}
		std::cout << " | " << M << std::endl;
	}
	std::cout << std::endl;
	delete player;
}

READY_STATE EXPERIMENT::isReady(const std::vector<int> &times, double &M) {
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

