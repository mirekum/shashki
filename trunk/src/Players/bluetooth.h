#ifndef _BLUETOOTH_H_
	#define _BLUETOOTH_H_
	
	#include "Players/player.h"
	
	class Bluetooth_Player: public Player {
	public:
		// get player type
		virtual PLAYER_TYPE type() {return BLUETOOTH;};
		// choose partial half-move
		virtual MOVE getMove(BOARD board);
	};
	
#endif

