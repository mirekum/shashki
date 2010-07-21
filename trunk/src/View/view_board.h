#ifndef _VIEW_BOARD_H_
	#define _VIEW_BOARD_H_
	
	#include "Model/game.h"
	#include "View/view.h"
	#include "View/view_main.h"
	
	class Board_Widget: public QWidget {
		Q_OBJECT
		public:
			paintEvent
	};
	
	class View_Board: public Player, public View {
		Q_OBJECT
	protected:
		Game *game;
		BOARD *board;
		QWidget *window;
		QFrame *boardwrap, *figures;
	public:
		View_Board(View_Main &main_ui);
		// view initialization
		void init(Game *_game);
		// get player type
		virtual PLAYER_TYPE type() {return HUMAN;};
		// request move from human
		virtual void execMove(BOARD board);
		// drawing functions
		void drawCanvas();
		void drawFigures();
	public slots:
		// updated model
		void updateBoard();
	};
	
#endif

