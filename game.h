#ifndef _GAME_H_
	#define _GAME_H_
	
	#include <iostream>
	#include "board.h"
	#include "player.h"
	
	// class for playing draughts
	class GAME {
	protected:
		// the board for game
		BOARD board;
		// white player
		PLAYER *wp;
		// black player
		PLAYER *bp;
	public:
		// class constructor
		GAME(PGAMER w, PGAMER b);
		// class destructor
		~GAME();
	protected:
		// creates player
		PLAYER* createPlayer(PGAMER plr);
		// the game process
		void process();
		// reports the results
		void result(GAMESTATE res);
	};
	
#endif

