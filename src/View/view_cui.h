#ifndef _VIEW_CUI_H_
	#define _VIEW_CUI_H_
	
	#include <iostream>
	#include "View/view.h"
	#include "Model/game.h"
	
	class VIEW_CUI: public VIEW {
	protected:
		// create game instance (H-H, H-A, H-N, etc)
		virtual GAME* createGame();
		// exec game process
		virtual int gameProcess();
		// show results of the game
		virtual void gameResults(GAMESTATE res_flag);
	public:
		VIEW_CUI(int _argc, char** _argv) {argc = _argc; argv = _argv;}
		// input data class
		class Input: public VIEW_INPUT {
		public:
			// get move from human player
			virtual MOVE humanGetmove(BOARD board);
		};
	};
	
	// print the board on the screen
	std::ostream& operator<< (std::ostream &cout, BOARD &board);
	
#endif

