#ifndef _BOARD_H_
	#define _BOARD_H_
	
	// figures on the board
	#define WHITE      +1 // white draught
	#define WHITE_KING +2 // white king
	#define BLACK      -1 // black draught
	#define BLACK_KING -2 // black king
	
	#define ISWIN_WHITE 1 // white won
	#define ISWIN_BLACK 2 // black won
	#define ISWIN_DRAW  3 // draw
	#define ISWIN_GAME  0 // game continues
	
	// a cell of the board
	class CELL {
	public:
		int x, y;
		// class constructors
		CELL(): x(0), y(0) {};
		CELL(int _x, int _y): x(_x), y(_y) {};
	};
	
	// a move from the one cell to the other
	class MOVE {
	public:
		CELL from, to;
		// class constructors
		MOVE() {};
		MOVE(CELL _from, CELL _to) {from = _from; to = _to;};
	};
	
	// move flags (eating, king transformation)
	class CANMOVE {
	public:
		int eat, king;
		// class constructors
		CANMOVE(): eat(0), king(0) {};
		CANMOVE(int _eat, int _king): eat(_eat), king(_king) {};
	};
	
	// class of the board for playing draughts
	class BOARD {
	public:
		// size of the board
		const static int size = 8;
	protected:
		// number of white and black figures
		int b, w;
		// number of white and black kings
		int bk, wk;
		// array of the board cells; 0 - empty, >0 - white, <0 - black
		char cells[size][size]; // [x][y]; x - col, y - row
		// flag, indicating first partial half-move
		bool ufirst;
		// flag, indicating eating at last partial half-move
		bool ueaten;
		// player color for current half-move
		int utype;
		// blocked for current half-move figure
		CELL ublocked;
	public:
		// class constructor
		BOARD();
		// starts the half-move
		void start_move(int type);
		// execs the partial half-move
		int move(MOVE _move);
		int move(CELL /* from */ a, CELL /* to */ z);
		int move(int x1, int y1, int x2, int y2);
		// checks the possibility of the partial half-move
		int can_move(MOVE move, CANMOVE *flags = NULL, int _type = 0);
		int can_move(CELL /* from */ a, CELL /* to */ z, CANMOVE *flags = NULL, int _type = 0);
		int can_move(int x1, int y1, int x2, int y2, CANMOVE *flags = NULL, int _type = 0);
		// checks the possibility of continuing the half-move
		int can_move();
		// gets array of the possible partial half-moves for the cell
		int moves(CELL cell, CELL *arr = NULL);
		// checks the end of the game
		int is_win();
		// print the board on the screen
		friend std::ostream& operator<< (std::ostream &cout, BOARD &board);
		// flag, indicating first partial half-move
		int first() {return ufirst;}
		// number of white figures
		int white() {return w;}
		// number of black figures
		int black() {return b;}
		// number of white kings
		int white_king() {return wk;}
		// number of black kings
		int black_king() {return bk;}
	protected:
		// small assistant functions
		int can_move_S_sq(CELL a, int dep, int type = 0, CELL *res = NULL);
		int can_scnd(CELL a);
		int can_frst(CELL a);
	};
	
#endif
