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
		BLACK_KING = -2, // black king
		BLACK      = -1, // black draught
		NONE       =  0, // no figure
		WHITE      =  1, // white draught
		WHITE_KING =  2  // white king
	};
	
	// is figure color white?
	inline bool IS_WHITE(FIGURE type) {return type > 0 ? true : false;};
	// is figure color black?
	inline bool IS_BLACK(FIGURE type) {return type < 0 ? true : false;};
	// is figure is a draught?
	inline bool IS_DRT(FIGURE type) {return abs(type) == 1 ? true : false;};
	// is figure is a king ?
	inline bool IS_KNG(FIGURE type) {return abs(type) == 2 ? true : false;};
	// is cell empty?
	inline bool IS_EMP(FIGURE type) {return type == NONE ? true : false;};
	
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
		public: CELL eat_c, king_c;
		CANMOVE(): eat(NONE), king(NONE) {};
	};
	
	// class of the board for playing draughts
	class BOARD {
	public:
		// size of the board
		const static unsigned int size = 8;
	protected:
	public:
		// number of white and black figures
		unsigned int b, w;
		// number of white and black kings
		unsigned int bk, wk;
		// array of the board cells
		FIGURE cells[size][size]; // [x][y]; x - col, y - row
		// flag, indicating first partial half-move
		bool ufirst;
		// flag, indicating eating at last partial half-move
		bool ueaten;
		// figure type for current half-move
		FIGURE utype;
		// blocked for current half-move figure
		CELL ublocked;
	public:
		// class constructor
		BOARD();
		// print the board on the screen
		friend std::ostream& operator<< (std::ostream &cout, BOARD &board);
		// starts the half-move
		void start_move(PCOLOR type);
		// checks the end of the game
		GAMESTATE is_win();
	protected:
		// checks the physical possibility of the move from one cell to the other one
		bool can_move(MOVE _move, CANMOVE *flags = NULL, FIGURE _type = NONE);
		bool can_move(CELL from, CELL to, CANMOVE *flags = NULL, FIGURE _type = NONE);
		bool can_move(int x1, int y1, int x2, int y2, CANMOVE *flags = NULL, FIGURE _type = NONE);
		// checks the possibility of move in square
		unsigned int get_square_moves(CELL figure, int dep, FIGURE type = NONE, CELL *res = NULL, CANMOVE *flags = NULL);
		// checks the possibility of eating
		bool can_eat(CELL figure);
		// checks the possibility of the first partial half-move or a not first partial half-move
		bool can_move(CELL figure);
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
