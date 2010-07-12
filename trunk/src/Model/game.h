#ifndef _GAME_H_
	#define _GAME_H_
	
	#include "Model/board.h"
	#include "Players/player.h"
	#include "View/view_input.h"
	
	class GAME {
	protected:
		BOARD board;
		PLAYER *wp, *bp, *plr;
		int moveNum;
		MOVE lastMove[PLAYER::maxFiguresNumber];
		VIEW_INPUT *gameInput;
	public:
		explicit GAME(PLAYER_TYPE w, PLAYER_TYPE b);
		static PLAYER* createPlayer(PLAYER_TYPE _type);
		~GAME();
		void start(VIEW_INPUT &_gameInput);
		void startMove(COLOR type);
		void execMove();
		bool canMove();
		void finish();
		GAMESTATE checkResult();
		BOARD& getBoard();
	};
	
#endif

