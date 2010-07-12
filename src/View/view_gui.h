#ifndef _VIEW_GUI_H_
	#define _VIEW_GUI_H_
	
	#include <QtCore>
	#include <QtGui>
	#include "View/view.h"
	#include "Model/game.h"
	
	class VIEW_GUI: public VIEW {
	protected:
		// create game instance (H-H, H-A, H-N, etc)
		virtual GAME* createGame();
		// exec game process
		virtual int gameProcess();
		// show results of the game
		virtual void gameResults(GAMESTATE res_flag);
		// widgets
		QWidget *window; // main window of application
		QFrame *boardwrap; // board widget
		QMap < int, QMap < int, QLabel* > > figures; // figures on the board
		// links to game objects
		BOARD board;
	public:
		VIEW_GUI(int _argc, char** _argv) {argc = _argc; argv = _argv;}
		// input data class
		class Input: public VIEW_INPUT {
		public:
			// get move from human player
			virtual MOVE humanGetmove(BOARD board);
		};
	};
	
#endif

