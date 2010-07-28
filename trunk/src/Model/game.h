#ifndef _GAME_H_
	#define _GAME_H_
	
	#include <QtCore>
	#include "Model/board.h"
	#include "Players/player.h"
	
	class getMoveThread: public QThread {
	protected:
		Player *current;
		BOARD *board;
	public:
		void setData(Player *_current, BOARD &_board) {
			current = _current;
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
		QList<MOVE> history;
	public:
		Game();
		void init(Player *wp, Player *bp);
		void start();
		// getters
		BOARD& getBoard() {return board;}
		QList<MOVE> getHistory();
	protected:
		void setCurrentPlayer(COLOR color);
		void move();
		void finish(GAMESTATE res_flag);
	signals:
		void currentPlayer(COLOR);
		void updateBoard();
		void finishGame(GAMESTATE);
	protected slots:
		void recieveMove();
	};
	
#endif

