#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include <iostream>
	#include "board.h"
	
	// player gamers
	enum PGAMER {HUMAN, AI, AI2};
	
	// class of the player for draughts
	class PLAYER {
	protected:
		// player color
		PCOLOR type;
	public:
		// class constructor
		PLAYER () {type = PNONE;}
		// sets player color
		void setType(PCOLOR _type) {type = _type;};
		// chooses partial half-move
		virtual MOVE get_move(BOARD board) = 0;
	};
	
#endif

