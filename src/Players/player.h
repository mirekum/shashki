#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include "Model/board.h"
	
	enum PLAYER_TYPE {HUMAN, AI};
	
	class Player {
	protected:
		// player color
		COLOR color;
		// choosen move
		MOVE result;
	public:
		Player() {color = NONE;}
		// sets player color (white or black)
		void setColor(COLOR _color) {color = _color;};
		// get player type
		virtual PLAYER_TYPE type() = 0;
		// choose partial half-move
		virtual void execMove(BOARD board) = 0;
		// get result of partial half-move
		MOVE getMove() {return result;}
		// set player level (for AI players)
		virtual void setLevel(int level) {};
		// getters
		COLOR getColor() {return color;};
	};
	
#endif

