#ifndef _AI_H_
	#define _AI_H_
	
	#include <vector>
	#include <pthread.h>
	#include <string.h>
	#include "Players/player.h"
	
	enum AI_PLAYER_TYPE {NegaMax_Ai, AlphaBeta_Ai, NegaScout_Ai};
	
	// chosen move
	class CHOOSEN_MOVE {
	public:
		CELL from, to;
		double mark;
		CHOOSEN_MOVE() {mark = 0.0;};
		CHOOSEN_MOVE(CELL _from, CELL _to, double _mark = 0.0) {
			from = _from;
			to = _to;
			mark = _mark;
		};
	};
	
	// array of chosen moves
	typedef std::vector<CHOOSEN_MOVE> CHOOSEN_MOVE_ARRAY;
	
	// first call of choose function
	void *ai_plr_first_choose(void *ptr);
	
	class Ai_Player: public Player {
		Q_OBJECT
	protected:
		// minimax limit
		const static int MINMAX_END = 2000000;
		// level (search tree depth)
		unsigned int max_step;
		// statistiс rating function
		virtual double srf(BOARD board);
		// threads number
		unsigned int thr_num;
	public:
		// initialization
		Ai_Player(int level = 4) {max_step = level; thr_num = 1; srand(time(0));}
		// get player type
		virtual PLAYER_TYPE type() {return AI;};
		// choose partial half-move
		virtual void execMove(BOARD board);
		// set ai level
		void setLevel(int level) {max_step = level;};
		// set threads number
		void setThrNum(int num) {thr_num = num;};
		// getters
		int getLevel() {return max_step;};
		int getThrNum() {return thr_num;};
		// AI players Fabric
		static Player *createAiPlayer(char *str, int level);
	protected:
		// choose the best partial half-move
		virtual double choose(BOARD board, COLOR _color, int step = 0, double alpha = -MINMAX_END, double beta = MINMAX_END, bool smflag = true);
	friend void *ai_plr_first_choose(void *ptr);
	};
	
	class Ai_Player_AlphaBeta: public Ai_Player {
	public:
		// initialization
		Ai_Player_AlphaBeta(int level = 4): Ai_Player(level) {}
		// choose the best partial half-move
		virtual double choose(BOARD board, COLOR _color, int step = 0, double alpha = -MINMAX_END, double beta = MINMAX_END, bool smflag = true);
	};
	
	class Ai_Player_NegaMax: public Ai_Player {
	public:
		// initialization
		Ai_Player_NegaMax(int level = 4): Ai_Player(level) {}
		// choose the best partial half-move
		virtual double choose(BOARD board, COLOR _color, int step = 0, double alpha = -MINMAX_END, double beta = MINMAX_END, bool smflag = true);
	};
	
	// moves synchronization between threads
	struct MOVES_SYNC {
	public:
		Ai_Player *plr;
		BOARD *board;
		int next_move_num;
		CHOOSEN_MOVE_ARRAY *moves_queue;
		pthread_mutex_t *queue_mutex;
		double alpha, beta;
		pthread_mutex_t *mark_mutex;
	};
	
#endif

