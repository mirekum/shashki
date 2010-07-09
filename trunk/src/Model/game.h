#ifndef _GAME_H_
	#define _GAME_H_
	
	#include "Model/board.h"
	#include "Players/player.h"
	
	class GAME {
	protected:
		BOARD board;
		PLAYER *wp, *bp, *plr;
		int moveNum;
		MOVE lastMove[PLAYER::maxFiguresNumber];
	public:
		GAME(GAMER w, GAMER b);
		~GAME();
		static PLAYER* createPlayer(GAMER plr);
		void startMove(COLOR type);
		void execMove();
		bool canMove();
		GAMESTATE checkResult();
		BOARD& getBoard();
		void finish();
	};
	
#endif

