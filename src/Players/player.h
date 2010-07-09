#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include <iostream>
	#include "Model/board.h"
	
	enum GAMER {HUMAN, AI, NETWORK};
	
	class PLAYER {
	public:
		const static unsigned int maxFiguresNumber = BOARD::size*2;
	protected:
		// player color
		COLOR type;
		// chosen move
		MOVE result;
	public:
		PLAYER () {type = NONE;}
		// sets player color
		void setType(COLOR _type) {type = _type;};
		// choose partial half-move
		virtual MOVE getMove(BOARD board) = 0;
		// set ai level (for ai players only)
		virtual void setLevel(int level) {};
		virtual void giveLastMoves(MOVE lastMove[maxFiguresNumber]) {};
		// gamer name
		static const char *getPlrText(GAMER p) {
			switch (p) {
				case HUMAN:
					return "Human";
				case AI:
					return "AI";
				case NETWORK:
					return "Network";
			}
			// TODO: error handling
			return "";
		}
	};
	
#endif
