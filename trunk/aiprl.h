#ifndef _AIPRL_H_
	#define _AIPRL_H_
	
	#include <iostream>
	#include <pthread.h>
	#include <vector>
	#include "board.h"
	#include "player.h"
	#include "aiseq.h"
	
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
	class AI_PRL_PLAYER: public AI_SEQ_PLAYER {
	protected:
		int thr_num;
	public:
		AI_PRL_PLAYER() {max_step = 4; ab = true; thr_num = 2;}
		virtual MOVE get_move(BOARD board); // choose partial half-move
	friend void *ai_prl_first_choose(void *ptr);
	};
	
	class AI_PRL_PLAYER2: public AI_PRL_PLAYER {
	public:
		AI_PRL_PLAYER2() {max_step = 4; ab = true; thr_num = 4;}
	};
	
	class AI_PRL_PLAYER3: public AI_PRL_PLAYER {
	public:
		AI_PRL_PLAYER3() {max_step = 4; ab = true; thr_num = 1;}
	};
	
	struct MOVES_SYNC {
	public:
		AI_PRL_PLAYER *plr;
		BOARD *board;
		int next_move_num;
		CHOOSEN_MOVE_ARRAY *moves_queue;
		pthread_mutex_t *queue_mutex;
		int mark;
		pthread_mutex_t *mark_mutex;
	};
	
#endif

