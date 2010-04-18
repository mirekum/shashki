#ifndef _EXPERIMENT_H_
	#define _EXPERIMENT_H_
	
	#include <iostream>
	#include <vector>
	#include "board.h"
	#include "player.h"
	
	typedef std::vector<double> times_array;
	
	enum READY_STATE {EXP_NOREADY, EXP_READY_COVAR, EXP_READY_MAXEXP};
	
	class EXPERIMENT {
	protected:
		BOARD board;
		PCOLOR ptype;
		int minExp, maxExp;
		double Covar;
		int minLvl, maxLvl;
	public:
		EXPERIMENT(const BOARD &_board, PCOLOR _ptype, int _minExp, int _maxExp, double _Covar, int minLvl, int maxLvl);
		void run(PGAMER plr);
	protected:
		READY_STATE isReady(const times_array &times, double &M);
	};
	
#endif

