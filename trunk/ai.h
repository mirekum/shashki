#ifndef _AI_H_
	#define _AI_H_
	
	#include <iostream>
	#include "player.h"
	
	// class of the ai player
	class AI_PLAYER: public PLAYER {
	protected:
		// minimax limit
		const static int MINMAX_END = 2000000;
		// alpha-beta pruning
		bool ab;
		// search tree depth
		unsigned int max_step;
		// statictiс rating function
		virtual int srf(BOARD board);
	public:
		// class constructor
		AI_PLAYER() {max_step = 4; ab = true;}
		// chooses partial half-move
		virtual MOVE get_move(BOARD board);
	protected:
		// choose the best partial half-move
		virtual int choose(BOARD board, PCOLOR _type, MOVE *res, int step = 0, int last = -MINMAX_END, bool smflag = true, int depth = 0);
	};
	
	// another class of the ai player
	class AI_PLAYER2: public AI_PLAYER {
	public:
		AI_PLAYER2() {max_step = 4; ab = true;}
	};
	
#endif

