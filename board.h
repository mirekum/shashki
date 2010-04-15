#ifndef _BOARD_H_
	#define _BOARD_H_
	
	#include <iostream>
	#include <stdlib.h>
	
	// player colors
	enum PCOLOR {
		PBLACK = -1,
		PNONE   = 0,
		PWHITE  = 1
	};
	
	// figure types
	enum FIGURE {
		BLACK_KING = -2,
		BLACK      = -1,
		NONE       =  0,
		WHITE      =  1,
		WHITE_KING =  2
	};
	
	// check figure type
	inline bool IS_WHITE(FIGURE type) {return type > 0 ? true : false;};
	inline bool IS_BLACK(FIGURE type) {return type < 0 ? true : false;};
	inline bool IS_DRT(FIGURE type) {return abs(type) == 1 ? true : false;};
	inline bool IS_KNG(FIGURE type) {return abs(type) == 2 ? true : false;};
	inline bool IS_EMP(FIGURE type) {return type == NONE ? true : false;};
	
	// FIGURE -> PCOLOR
	PCOLOR COLOR(FIGURE type);
	
	// win states
	enum GAMESTATE {
		ISWIN_GAME,  // game continues
		ISWIN_WHITE, // white won
		ISWIN_BLACK, // black won
		ISWIN_DRAW   // draw
	};
	
	// a cell of the board
	class CELL {
		public: int x, y;
		explicit CELL(int _x = 0, int _y = 0): x(_x), y(_y) {};
	};
	
	// a move from the one cell to the other one
	class MOVE {
		public: CELL from, to;
		MOVE() {};
		MOVE(CELL _from, CELL _to) {from = _from; to = _to;};
	};
	
	// move flags (eating enemy figure, king transformation)
	class CANMOVE {
		public: FIGURE eat, king;
		public: CELL eat_c;
		CANMOVE(): eat(NONE), king(NONE) {};
	};
	
	// board for playing draughts
	class BOARD {
	public:
		const static unsigned int size = 8;
	protected:
		unsigned int b, w, bk, wk; // numbers of figures and kinks
		FIGURE cells[size][size];  // [x][y]; x - col, y - row
		bool ufirst;               // flag, indicating first partial half-move
		bool ueaten;               // flag, indicating eating at last partial half-move
		PCOLOR utype;              // player type for current half-move
		CELL ublocked;             // blocked for current half-move figure
	public:
		BOARD();
		friend std::ostream& operator<< (std::ostream &cout, BOARD &board);
		void start_move(PCOLOR type); // starts the half-move
		GAMESTATE is_win();
	protected:
		// checks the physical possibility of the move from one cell to the other one
		bool can_move(MOVE _move, CANMOVE *flags = NULL, PCOLOR _type = PNONE);
		bool can_move(CELL from, CELL to, CANMOVE *flags = NULL, PCOLOR _type = PNONE);
		bool can_move(int x1, int y1, int x2, int y2, CANMOVE *flags = NULL, PCOLOR _type = PNONE);
		// checks the possibility of move in square
		unsigned int get_square_moves(CELL figure, int dep, PCOLOR type = PNONE, CELL *res = NULL, CANMOVE *flags = NULL);
		// checks the possibility of eating
		bool can_eat(CELL figure);
		// checks the possibility of the first partial half-move or a not first partial half-move
		bool can_move(CELL figure);
	public:
		// set cell value
		bool scell(int x, int y, FIGURE type);
		bool scell(CELL figure, FIGURE type);
		bool scell(int x1, int y1, int x2, int y2);
		bool scell(CELL figure1, CELL figure2);
		// get cell value
		FIGURE gcell(int x, int y);
		FIGURE gcell(CELL figure);
	public:
		// checks the possibility of continuing the half-move by current player
		bool can_move();
		// gets array of the possible partial half-moves for the cell
		unsigned int moves(CELL figure, CELL *arr = NULL);
		// execs the partial half-move
		bool move(MOVE _move);
		bool move(CELL from, CELL to);
		bool move(int x1, int y1, int x2, int y2);
		// getters
		int first() {return ufirst;}
		int white() {return w;}
		int black() {return b;}
		int white_king() {return wk;}
		int black_king() {return bk;}
	};
	
#endif
