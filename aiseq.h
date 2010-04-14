#ifndef _AISEQ_H_
	#define _AISEQ_H_
	
	#include <iostream>
	#include "player.h"
	
	// class of the sequential ai player
	class AI_SEQ_PLAYER: public PLAYER {
	protected:
		// minimax limit
		const static int MINMAX_END = 2000000;
		// is alpha-beta pruning on?
		bool ab;
		// search tree depth
		unsigned int max_step;
		// statictiс rating function
		virtual int srf(BOARD board);
	public:
		AI_SEQ_PLAYER() {max_step = 6; ab = true;}
		virtual MOVE get_move(BOARD board); // choose partial half-move
		void set_level(int level) {max_step = level;};
	protected:
		// choose the best partial half-move
		virtual int choose(BOARD board, PCOLOR _type, MOVE *res, int step = 0, int last = -MINMAX_END, bool smflag = true);
	};
	
	class AI_SEQ_PLAYER2: public AI_SEQ_PLAYER {
	public:
		AI_SEQ_PLAYER2() {max_step = 6; ab = true;}
	};
	
#endif

