#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include "Model/board.h"
	
	enum PLAYER_TYPE {HUMAN, AI, NETWORK, BLUETOOTH};
	
	struct PLAYER_SETTINGS {
		int aiLevel;
	};
	
	class Player {
	public:
		const static unsigned int maxFiguresNumber = BOARD::size*2;
	protected:
		// player color
		COLOR color;
	public:
		Player () {color = NONE;}
		// sets player color (white or black)
		void setColor(COLOR _color) {color = _color;};
		// get player type
		virtual PLAYER_TYPE type() = 0;
		// choose partial half-move
		virtual MOVE getMove(BOARD board) = 0;
		// set player level (for AI players)
		virtual void setLevel(int level) {};
		// give last moves array to player
		virtual void giveLastMoves(MOVE lastMove[]) {};
	};
	
#endif

