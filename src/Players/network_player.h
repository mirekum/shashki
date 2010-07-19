#ifndef _NETWORK_H_
	#define _NETWORK_H_
	
	#include "Players/player.h"
	
	class Network_Player: public Player {
	public:
		// get player type
		virtual PLAYER_TYPE type() {return NETWORK;};
		// choose partial half-move
		virtual MOVE getMove(BOARD board);
	};
	
#endif

