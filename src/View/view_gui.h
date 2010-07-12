#ifndef _VIEW_GUI_H_
	#define _VIEW_GUI_H_
	
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
	public:
		// input data class
		class Input: public VIEW_INPUT {
		public:
			// get move from human player
			virtual MOVE humanGetmove();
		};
	};
	
#endif

