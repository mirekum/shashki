#ifndef _GAME_H_
	#define _GAME_H_
	
	#include <QtCore>
	#include "Model/board.h"
	#include "Players/player.h"
	
	class getMoveThread: public QThread {
	protected:
		Player *plr;
		BOARD *board;
	public:
		void setData(Player *_plr, BOARD &_board) {
			plr = _plr;
			board = &_board;
		}
	protected:
		void run();
	};
	
	class Game: public QObject {
		Q_OBJECT
	protected:
		BOARD board;
		Player *wp, *bp;
		int moveNum;
		MOVE lastMove[Player::maxFiguresNumber];
		Player *current;
		getMoveThread *thread;
	public:
		Game();
		void init(Player *wp, Player *bp);
		void start();
		BOARD& getBoard();
	protected:
		void setCurrentPlayer(COLOR color);
		void move();
		void finish(GAMESTATE res_flag);
	signals:
		void currentPlayer(COLOR);
	protected slots:
		void recieveMove(MOVE mv);
	};
	
#endif
