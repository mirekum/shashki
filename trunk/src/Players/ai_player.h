#ifndef _AI_H_
	#define _AI_H_
	
	#include <vector>
	#include <pthread.h>
	#include <string.h>
	#include "Players/player.h"
	
	enum AI_PLAYER_LEVEL {LVL_L, LVL_M, LVL_D};
	
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
	protected:
		// minimax limit
		const static int MINMAX_END = 2000000;
		// level (search tree depth)
		unsigned int max_step;
		// statistiс rating function
		virtual double srf(BOARD board);
		// threads number
		unsigned int thr_num;
		// randomization
		bool rndFlag;
		// time control
		bool timeCtr;
	public:
		// initialization
		Ai_Player(AI_PLAYER_LEVEL level = LVL_M) {
			// player level
			setLevel(level);
			// multi-threading
			thr_num = 1;
			// randomization
			srand(time(0));
			rndFlag = true;
		}
		// get player type
		virtual PLAYER_TYPE type() {return AI;};
		// choose partial half-move
		virtual void execMove(BOARD board);
		// set ai level
		void setLevel(AI_PLAYER_LEVEL level) {
			// time control
			timeCtr = true;
			// player level
			switch (level) {
				case LVL_L:
					max_step = 8;
				break;
				case LVL_M:
					max_step = 9;
				break;
				case LVL_D:
					max_step = 10;
				break;
			}
		};
		// set ai depth and turn off time control
		void setDepth(int depth) {
			timeCtr = false;
			max_step = depth;
		};
		// set threads number
		void setThrNum(int num) {
			thr_num = num;
		};
		// getters
		int getLevel() {return max_step;};
		int getThrNum() {return thr_num;};
		// randomization control
		void randomize(bool var) {rndFlag = var;}
		// AI players Fabric
		static Player *createAiPlayer(char *str, AI_PLAYER_LEVEL level);
		static Player *createAiPlayer(char *str, int depth);
	protected:
		// choose the best partial half-move
		virtual double choose(BOARD board, COLOR _color, int step = 0, double alpha = -MINMAX_END, double beta = MINMAX_END, bool smflag = true, time_t endTime = -1);
		// time control
		int getTimeForMove();
	friend void *ai_plr_first_choose(void *ptr);
	};
	
	// NegaScout
	class Ai_Player_NegaScout: public Ai_Player {
	public:
		// initialization
		Ai_Player_NegaScout(AI_PLAYER_LEVEL level = LVL_M): Ai_Player(level) {}
	};
	
	// AlphaBeta
	class Ai_Player_AlphaBeta: public Ai_Player {
	public:
		// initialization
		Ai_Player_AlphaBeta(AI_PLAYER_LEVEL level = LVL_M): Ai_Player(level) {}
		// choose the best partial half-move
		virtual double choose(BOARD board, COLOR _color, int step = 0, double alpha = -MINMAX_END, double beta = MINMAX_END, bool smflag = true, time_t endTime = -1);
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
		time_t endTime;
	};
	
#endif

