#ifndef _HUMAN_H_
	#define _HUMAN_H_
	
	#include <iostream>
	#include "Players/player.h"
	
	class HUMAN_PLAYER: public PLAYER {
	public:
		// chooses partial half-move
		virtual MOVE getMove(BOARD board);
	};
	
#endif
