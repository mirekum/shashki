#ifndef _EXPERIMENT_H_
	#define _EXPERIMENT_H_
	
	#include <iostream>
	#include <vector>
	#include "Model/board.h"
	#include "Players/player.h"
	
	typedef std::vector<double> times_array;
	
	enum READY_STATE {EXP_NOREADY, EXP_READY_COVAR, EXP_READY_MAXEXP};
	
	class EXPERIMENT {
	protected:
		BOARD board;
		COLOR ptype;
		int minExp, maxExp;
		double Covar;
		int minLvl, maxLvl;
	public:
		EXPERIMENT(const BOARD &_board, COLOR _ptype, int _minExp, int _maxExp, double _Covar, int minLvl, int maxLvl);
		void run(GAMER plr);
	protected:
		READY_STATE isReady(const times_array &times, double &M, double &covar);
	};
	
#endif

