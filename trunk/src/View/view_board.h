#ifndef _VIEW_BOARD_H_
	#define _VIEW_BOARD_H_
	
	#include "Model/game.h"
	#include "View/view.h"
	#include "View/view_main.h"
	
	class Board_Widget: public QWidget {
		Q_OBJECT
	protected:
		Game *game;
		BOARD *board;
		int ready;
		bool read_flag;
		GAMESTATE end_flag;
		MOVE result;
		COLOR currentColor;
		QTextEdit*textHistory;
	public:
		Board_Widget(QWidget * parent = 0);
		void init(Game *_game);
		void startMove(COLOR color);
		MOVE getMove();
		bool isReady();
		bool eventFilter(QObject *target, QEvent *event);
		virtual void paintEvent(QPaintEvent *event);
		void status(GAMESTATE res_flag);
	};
	
	class View_Board: public Player, public View {
		Q_OBJECT
	protected:
		Game *game;
		BOARD *board;
		QWidget *window;
		Board_Widget *canvas;
	public:
		View_Board(View_Main &main_ui);
		// view initialization
		void init(Game *_game);
		// view hiding
		void hide();
		// get player type
		virtual PLAYER_TYPE type() {return HUMAN;};
		// request move from human
		virtual void execMove(BOARD board);
		// drawing functions
		void drawCanvas();
		void drawFigures();
	public slots:
		void updateBoard();
		void finishGame(GAMESTATE res_flag);
	};
	
#endif

