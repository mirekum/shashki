#ifndef _AI_H_
	#define _AI_H_
	#include "player.h"
	
	#define MINMAX_END 2000000
	
	// class of the ai player
	class AI_PLAYER: public PLAYER {
	protected:
		// alpha-beta pruning
		const static int ab = 1;
		// search tree depth
		int max_step;
		// statictiс rating function
		virtual int srf(BOARD board);
	public:
		// class constructor
		AI_PLAYER() {max_step = 4;}
		// chooses partial half-move
		virtual MOVE move(BOARD board);
	protected:
		// choose the best partial half-move
		virtual int choose(BOARD board, int _type, MOVE *res, int step = 0, int last = -MINMAX_END, bool smflag = true);
	};
	
	// another class of the ai player
	class AI_PLAYER2: public AI_PLAYER {
	public:
		AI_PLAYER2() {max_step = 4;}
	};
	
#endif

