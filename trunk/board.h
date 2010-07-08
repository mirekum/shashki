#ifndef _BOARD_H_
	#define _BOARD_H_
	
	#include <iostream>
	#include <stdlib.h>
	
	// colors
	enum COLOR {
		BLACK = -1,
		NONE  =  0,
		WHITE =  1
	};
	
	// figure types
	enum FIGURE {
		BLACK_KING = -2,
		BLACK_PAWN = -1,
		EMPTY      =  0,
		WHITE_PAWN =  1,
		WHITE_KING =  2
	};
	
	// check figure type
	inline bool IS_WHITE(FIGURE type) {return type > 0 ? true : false;};
	inline bool IS_WHITE(COLOR type) {return type > 0 ? true : false;};
	inline bool IS_BLACK(FIGURE type) {return type < 0 ? true : false;};
	inline bool IS_BLACK(COLOR type) {return type < 0 ? true : false;};
	inline bool IS_EMPTY(FIGURE type) {return !type ? true : false;};
	inline bool IS_EMPTY(COLOR type) {return !type ? true : false;};
	inline bool IS_DRT(FIGURE type) {return abs(type) == 1 ? true : false;};
	inline bool IS_KNG(FIGURE type) {return abs(type) == 2 ? true : false;};
	
	// FIGURE -> COLOR
	COLOR getColor(FIGURE type);
	
	// game states
	enum GAMESTATE {
		END_NONE,  // game continues
		END_WHITE, // white won
		END_BLACK, // black won
		END_DRAW   // draw
	};
	
	// a cell of the board
	class CELL {
		public: int x, y;
		explicit CELL(int _x = 0, int _y = 0): x(_x), y(_y) {};
		friend std::ostream& operator<< (std::ostream &cout, CELL &cell);
		friend bool operator== (CELL a, CELL b);
		friend bool operator!= (CELL a, CELL b);
	};
	
	// a move from the one cell to the other one
	class MOVE {
		public: CELL from, to;
		MOVE() {};
		MOVE(CELL _from, CELL _to) {from = _from; to = _to;};
		friend std::ostream& operator<< (std::ostream &cout, MOVE &move);
		friend bool operator== (MOVE m1, MOVE m2);
		friend bool operator!= (MOVE m1, MOVE m2);
	};
	
	// move flags (eating enemy figure, king transformation)
	class CANMOVE {
		public: FIGURE eat;
		public: COLOR king;
		public: CELL eat_c;
		CANMOVE(): eat(EMPTY), king(NONE) {};
	};
	
	// board for playing draughts
	class BOARD {
	public:
		const static unsigned int size = 8;
	protected:
		unsigned int b, w, bk, wk; // numbers of figures and kings
		FIGURE cells[size][size];  // [x][y]; x - col, y - row
		bool ufirst;               // flag, indicating first partial half-move
		bool ueaten;               // flag, indicating eating at last partial half-move
		COLOR utype;               // player type for current half-move
		CELL ublocked;             // blocked for current half-move figure
	public:
		BOARD();
		// print the board on the screen
		friend std::ostream& operator<< (std::ostream &cout, BOARD &board);
		// starts the half-move
		void startMove(COLOR type);
		// check if game is continuing or finished
		GAMESTATE isWin();
		// set cell value
		bool scell(int x, int y, FIGURE type);
		bool scell(CELL figure, FIGURE type);
		bool scell(int x1, int y1, int x2, int y2);
		bool scell(CELL figure1, CELL figure2);
		// get cell value
		FIGURE gcell(int x, int y);
		FIGURE gcell(CELL figure);
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
		int whiteKing() {return wk;}
		int blackKing() {return bk;}
		// checks the possibility of continuing the half-move by current player
		bool canMove();
	protected:
		// checks the physical possibility of the move from one cell to the other one
		bool canMove(MOVE _move, CANMOVE *flags = NULL, COLOR _type = NONE);
		bool canMove(CELL from, CELL to, CANMOVE *flags = NULL, COLOR _type = NONE);
		bool canMove(int x1, int y1, int x2, int y2, CANMOVE *flags = NULL, COLOR _type = NONE);
		// checks the possibility of move in square
		unsigned int getSquareMoves(CELL figure, int dep, COLOR type = NONE, CELL *res = NULL, CANMOVE *flags = NULL);
		// checks the possibility of eating
		bool canEat(CELL figure);
		bool canEat(int x, int y);
		// checks the possibility of the first partial half-move or a not first partial half-move
		bool canMove(CELL figure);
};
	
#endif
