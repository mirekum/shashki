#ifndef _GAME_H_
	#define _GAME_H_
	
	#include "Model/board.h"
	#include "Players/player.h"
	
	struct InitGameData {
		Player *wp, *bp;
	};
	
	class Game {
	protected:
		BOARD board;
		Player *wp, *bp;
		int moveNum;
		MOVE lastMove[Player::maxFiguresNumber];
	public:
		Game();
		~Game();
		BOARD& getBoard();
	};
	
#endif

