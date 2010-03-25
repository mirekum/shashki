#ifndef _HUMAN_H_
	#define _HUMAN_H_
	
	#include <iostream>
	#include "player.h"
	
	// class of the human player
	class HUMAN_PLAYER: public PLAYER {
	public:
		// chooses partial half-move
		virtual MOVE get_move(BOARD board);
	};
	
#endif

