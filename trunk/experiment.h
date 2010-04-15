#ifndef _EXPERIMENT_H_
	#define _EXPERIMENT_H_
	
	#include <iostream>
	#include <string>
	#include <vector>
	#include "board.h"
	#include "player.h"
	
	enum READY_STATE {EXP_NOREADY, EXP_READY_COVAR, EXP_READY_MAXEXP};
	
	class EXPERIMENT {
	protected:
		BOARD board;
		int minExp, maxExp;
		double Covar;
		int minLvl, maxLvl;
	public:
		EXPERIMENT(const BOARD &_board, int _minExp, int _maxExp, double _Covar, int minLvl, int maxLvl);
		void run(PGAMER plr, const std::string &filename);
	protected:
		READY_STATE isReady(const std::vector<int> &times, double &M);
	};
	
#endif

