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
		MOVE lastMove[PLAYER::maxFiguresNumber];
	public:
		GAME(GAMER w, GAMER b);
		~GAME();
		static PLAYER* createPlayer(GAMER plr);
	protected:
		void process();
		void execMove(PLAYER *plr, COLOR type);
		void result(GAMESTATE res);
	};
	
#endif

