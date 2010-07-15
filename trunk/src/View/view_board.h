#ifndef _VIEW_BOARD_H_
	#define _VIEW_BOARD_H_
	
	#include "Model/game.h"
	#include "View/view.h"
	#include "View/view_main.h"
	
	class View_Board: public View, public Player {
		Q_OBJECT
	protected:
		Game *game;
		BOARD *board;
		QWidget *window;
		QFrame *boardwrap, *figureswrap;
		QLabel *figures[8][8];
	public:
		View_Board(View_Main &main_ui);
		// view initialization
		void init(Game *_game);
		// get player type
		virtual PLAYER_TYPE type() {return HUMAN;};
	public slots:
		// get move from human
		virtual MOVE getMove(BOARD board);
	};
	
#endif

