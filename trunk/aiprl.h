#ifndef _AIPRL_H_
	#define _AIPRL_H_
	
	#include <iostream>
	#include <pthread.h>
	#include <vector>
	#include "board.h"
	#include "player.h"
	
	class CHOOSEN_MOVE {
	public:
		CELL from, to;
		int mark;
		CHOOSEN_MOVE() {mark = 0;};
		CHOOSEN_MOVE(CELL _from, CELL _to, int _mark = 0) {
			from = _from;
			to = _to;
			mark = _mark;
		};
	};
	
	typedef std::vector<CHOOSEN_MOVE> CHOOSEN_MOVE_ARRAY;
	
	void *ai_prl_first_choose(void *ptr);
	
	// class of the parallel ai player
	class AI_PRL_PLAYER: public PLAYER {
	protected:
		// minimax limit
		const static int MINMAX_END = 2000000;
		// search tree depth
		unsigned int max_step;
		// statictiс rating function
		virtual int srf(BOARD board);
	public:
		AI_PRL_PLAYER() {max_step = 8;}
		// chooses partial half-move
		virtual MOVE get_move(BOARD board);
	protected:
		// choose the best partial half-move
		virtual int choose(BOARD board, PCOLOR _type, MOVE *res, int step = 0, int last = -MINMAX_END, bool smflag = true);
	friend void *ai_prl_first_choose(void *ptr);
	};
	
	struct MOVES_SYNC {
	public:
		AI_PRL_PLAYER *plr;
		BOARD *board;
		CHOOSEN_MOVE_ARRAY *moves_queue;
		pthread_mutex_t *queue_mutex;
		int next_move_num;
	};
	
#endif

