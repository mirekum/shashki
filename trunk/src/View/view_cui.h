#ifndef _VIEW_CUI_H_
	#define _VIEW_CUI_H_
	
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
	};
	
#endif

