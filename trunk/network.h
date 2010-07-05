#ifndef _NETWORK_H_
	#define _NETWORK_H_
	
	#include <iostream>
	#include "player.h"
	
	class NETWORK_PLAYER: public PLAYER {
	public:
		// chooses partial half-move
		virtual MOVE getMove(BOARD board);
	};
	
#endif

