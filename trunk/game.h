#ifndef _GAME_H_
	#define _GAME_H_
	
	#include <iostream>
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
	protected:
		PLAYER* createPlayer(PGAMER plr);
		// the game process
		void process();
		// player move
		void exec_move(PLAYER *plr, PCOLOR type);
		// reports the results
		void result(GAMESTATE res);
	};
	
#endif

