#ifndef _GAME_H_
	#define _GAME_H_
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
		GAME(int w, int b);
	protected:
		// creates player
		PLAYER* createPlayer(int plr);
		// the game process
		void process();
		// reports the results
		void result(int res);
	};
	
#endif

