#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include <iostream>
	#include "board.h"
	
	// gamers
	enum PGAMER {HUMAN, AI_SEQ, AI_SEQ2, AI_PRL, AI_PRL2, AI_PRL3};
	
	class PLAYER {
	protected:
		// player color
		PCOLOR type;
	public:
		PLAYER () {type = PNONE;}
		void setType(PCOLOR _type) {type = _type;}; // sets player color
		virtual MOVE get_move(BOARD board) = 0; // choose partial half-move
		virtual void setLevel(int level) {}; // for ai players
		static const char *getPlrText(PGAMER p) {
			switch (p) {
				case HUMAN:
					return "human";
				case AI_SEQ:
					return "sequence ai";
				case AI_SEQ2:
					return "sequence ai ver#2";
				case AI_PRL:
					return "parallel ai (2 threads)";
				case AI_PRL2:
					return "parallel ai (4 threads)";
				case AI_PRL3:
					return "parallel ai (1 thread)";
			}
			
			return "";
		}
	};
	
#endif

