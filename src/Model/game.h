#ifndef _GAME_H_
	#define _GAME_H_
	
	#include <QtCore>
	#include "Model/board.h"
	#include "Players/player.h"
	
	class Game: public QObject {
	protected:
		BOARD board;
		Player *wp, *bp;
		int moveNum;
		MOVE lastMove[Player::maxFiguresNumber];
	public:
		Game();
		void init(Player *wp, Player *bp);
		BOARD& getBoard();
	};
	
#endif

