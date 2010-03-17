#ifndef _HUMAN_H_
	#define _HUMAN_H_
	#include "player.h"
	
	// класс "Игрок-человек"
	class HUMAN_PLAYER: public PLAYER {
	public:
		// выполнение хода
		virtual MOVE move(BOARD board);
	};
	
#endif

