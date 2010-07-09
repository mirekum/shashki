#ifndef _VIEW_H_
	#define _VIEW_H_
	
	#include "Model/game.h"
	
	class VIEW {
	protected:
		// game instance
		GAME *game;
	public:
		// show application
		int exec() {
			game = createGame();
			return gameProcess();
		}
	protected:
		// create game instance (H-H, H-A, H-N, etc)
		virtual GAME* createGame() = 0;
		// exec game process
		virtual int gameProcess() = 0;
		// show results of the game
		virtual void gameResults(GAMESTATE res_flag) = 0;
	public:
		// exit from aplication
		~VIEW() {
			delete game;
		}
	};
	
#endif

