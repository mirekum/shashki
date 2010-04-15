#ifndef _GAME_H_
	#define _GAME_H_
	
	#include "board.h"
	#include "player.h"
	
	// class for playing draughts
	class GAME {
	protected:
		BOARD board;
		PLAYER *wp, *bp;
		int move_num;
	public:
		GAME(PGAMER w, PGAMER b);
		~GAME();
		static PLAYER* createPlayer(PGAMER plr);
	protected:
		void process();
		void exec_move(PLAYER *plr, PCOLOR type);
		void result(GAMESTATE res);
	};
	
#endif

