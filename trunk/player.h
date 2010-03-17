#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#define HUMAN 10
	#define AI    20
	#define AI2   30
	
	// class of the player for draughts
	class PLAYER {
	protected:
		// player color
		int type;
	public:
		// class constructor
		PLAYER () {type = 0;}
		// sets player color
		void setType(int _type) {type = _type;};
		// chooses partial half-move
		virtual MOVE move(BOARD board) = 0;
	};
	
#endif

