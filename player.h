#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include <iostream>
	#include "board.h"
	
	// gamers
	enum PGAMER {HUMAN, AI_SEQ, AI_SEQ2, AI_PRL};
	
	class PLAYER {
	protected:
		// player color
		PCOLOR type;
	public:
		PLAYER () {type = PNONE;}
		// sets player color
		void setType(PCOLOR _type) {type = _type;};
		// chooses partial half-move
		virtual MOVE get_move(BOARD board) = 0;
	};
	
#endif

