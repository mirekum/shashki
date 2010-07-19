#ifndef _AI_H_
	#define _AI_H_
	
	#include <pthread.h>
	#include <vector>
	#include "Players/player.h"
	
	// chosen move
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
	
	// array of chosen moves
	typedef std::vector<CHOOSEN_MOVE> CHOOSEN_MOVE_ARRAY;
	
	// first call of choose function
	void *ai_prl_first_choose(void *ptr);
	
	class Ai_Player: public Player {
	protected:
		// minimax limit
		const static int MINMAX_END = 2000000;
		// is alpha-beta pruning on?
		bool ab;
		// level (search tree depth)
		unsigned int max_step;
		// statistiс rating function
		virtual int srf(BOARD board);
		// threads number
		unsigned int thr_num;
	public:
		// initialization
		Ai_Player(int level = 4) {max_step = level; ab = true; thr_num = 1;}
		// get player type
		virtual PLAYER_TYPE type() {return AI;};
		// choose partial half-move
		virtual MOVE getMove(BOARD board);
		// set ai level
		virtual void setLevel(int level) {max_step = level;};
		// set threads number
		virtual void setThrNum(int num) {thr_num = num;};
	protected:
		// choose the best partial half-move
		virtual int choose(BOARD board, COLOR _color, MOVE *res, int step = 0, int last = -MINMAX_END, bool smflag = true);
	
	friend void *ai_prl_first_choose(void *ptr);
	};
	
	// moves synchronization between threads
	struct MOVES_SYNC {
	public:
		Ai_Player *plr;
		BOARD *board;
		int next_move_num;
		CHOOSEN_MOVE_ARRAY *moves_queue;
		pthread_mutex_t *queue_mutex;
		int mark;
		pthread_mutex_t *mark_mutex;
	};
	
#endif

