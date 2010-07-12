#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include "Model/board.h"
	
	enum PLAYER_TYPE {UNDEFINED_PLAYER_TYPE, HUMAN, AI, NETWORK};
	
	class PLAYER {
	public:
		const static unsigned int maxFiguresNumber = BOARD::size*2;
	protected:
		// player color
		COLOR color;
		// player type
		PLAYER_TYPE type;
	public:
		PLAYER () {color = NONE; type = UNDEFINED_PLAYER_TYPE;}
		// sets player color
		void setType(COLOR _color) {color = _color;};
		// choose partial half-move (for non-human players)
		virtual MOVE getMove(BOARD board) {};
		// set ai level (for ai players)
		virtual void setLevel(int level) {};
		// send last moves (for network players)
		virtual void giveLastMoves(MOVE lastMove[maxFiguresNumber]) {};
		// player type
		PLAYER_TYPE getType() {return type;};
		// player type name
		static const char *getPlrText(PLAYER_TYPE _type) {
			switch (_type) {
				case HUMAN:
					return "Human";
				case AI:
					return "AI";
				case NETWORK:
					return "Network";
				default:
					exit(1);
			}
			return NULL;
		}
	};
	
#endif

