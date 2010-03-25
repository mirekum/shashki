#include <iostream>
#include <stdlib.h>
#include "board.h"

// is figure color white?
bool IS_WHITE(FIGURE type) {return type > 0 ? true : false;};
// is figure color black?
bool IS_BLACK(FIGURE type) {return type < 0 ? true : false;};
// is figure is a draught?
bool IS_DRT(FIGURE type) {return abs(type) == 1 ? true : false;};
// is figure is a king ?
bool IS_KNG(FIGURE type) {return abs(type) == 2 ? true : false;};
// is cell empty?
bool IS_EMP(FIGURE type) {return type == NONE ? true : false;};

/* methods of class of the board for playing draughts */

// class constructor
// set firstly figures positions and the board state
BOARD::BOARD() {
	// zeroize the board
	b = w = bk = wk = 0;
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j++)
			cells[i][j] = NONE;
	// set firstly figures positions
	for (int i = 0; i < size; i += 2) {
		cells[i+1][0] = BLACK;
		cells[i][1]   = BLACK;
		cells[i+1][2] = BLACK;
		b += 3;
		cells[i][5]   = WHITE;
		cells[i+1][6] = WHITE;
		cells[i][7]   = WHITE;
		w += 3;
	}
}

// print the board on the screen
std::ostream& operator<< (std::ostream &cout, BOARD &board) {
	std::cout << "------ Доска ------" << std::endl;
	std::cout << "   0 1 2 3 4 5 6 7 " << std::endl << std::endl;
	for (int y = 0; y < board.size; y++) {
		std::cout << y << "  ";
		for (int x = 0; x < board.size; x++) {
			if (board.cells[x][y] == WHITE)
				std::cout << "x ";
			else if (board.cells[x][y] == BLACK)
				std::cout << "o ";
			else if (board.cells[x][y] == WHITE_KING)
				std::cout << "W ";
			else if (board.cells[x][y] == BLACK_KING)
				std::cout << "B ";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << "-------------------";
	return std::cout;
}

// starts the half-move
void BOARD::start_move(PCOLOR type) {
	// current player color
	utype = (FIGURE)type;
	// zeroize flags
	ufirst = true;
	ueaten = false;
}

// checks the end of the game
GAMESTATE BOARD::is_win() {
	int tb = 0, tw = 0; // number of the figures, which can move
	// check number of the figures
	if (!b) return ISWIN_WHITE;
	if (!w) return ISWIN_BLACK;
	// check move possibility of the figures
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (can_move_square(CELL(i, j), 1) || can_move_square(CELL(i, j), 2)) {
				if (IS_WHITE(cells[i][j])) tw++;
				if (IS_BLACK(cells[i][j])) tb++;
			}
		}
	}
	// some debug info
	std::cout << "[белые: " << tw << "/" << w << " | чёрные: " << tb << "/" << b << "]" << std::endl;
	// check winning and draw
	if ( tw && !tb) return ISWIN_WHITE;
	if (!tw &&  tb) return ISWIN_BLACK;
	if (!tw && !tb) return ISWIN_DRAW;
	// game continuing
	return ISWIN_GAME;
}

// checks the physical possibility of the move from one cell to the other one
bool BOARD::can_move(CELL from, CELL to, CANMOVE *flags, FIGURE _type) {
	// check coordinate limits
	if (from.x < 0 || from.y < 0 || from.x >= size || from.y >= size) return 0;
	if (to.x < 0   || to.y < 0   || to.x >= size   || to.y >= size) return 0;
	// initial figure color
	int type = cells[from.x][from.y];
	// move by empty cells is denied
	if (!type) return 0;
	// move by enemy figures is denied
	if (_type && type != _type) return 0;
	// move to occupied cells is denied
	if (cells[to.x][to.y]) return 0;
	// check king transformation
	if (flags != NULL) {
		// whites
		if (type == WHITE && to.y == 0) {
			flags->king = WHITE;
			flags->king_c = to;
		}
		// blacks
		else if (type == BLACK && to.y == size - 1) {
			flags->king = BLACK;
			flags->king_c = to;
		}
	}
	/* TODO */
	// move is denied
	return 0;
}
bool BOARD::can_move(MOVE _move, CANMOVE *flags, FIGURE _type) {return can_move(_move.from, _move.to, flags, _type);}bool BOARD::can_move(int x1, int y1, int x2, int y2, CANMOVE *flags, FIGURE _type) {return can_move(CELL(x1, y1), CELL(x2, y2), flags, _type);};

// checks the possibility of move in square
unsigned int BOARD::can_move_square(CELL a, int dep, FIGURE type, CELL *res) {
	unsigned int k = 0;
	if (dep <= 0) return 0;
	if (can_move(a, CELL(a.x+dep, a.y+dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x+dep, a.y+dep); else k++;
	if (can_move(a, CELL(a.x-dep, a.y+dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x-dep, a.y+dep); else k++;
	if (can_move(a, CELL(a.x+dep, a.y-dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x+dep, a.y-dep); else k++;
	if (can_move(a, CELL(a.x-dep, a.y-dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x-dep, a.y-dep); else k++;
	return k;
}

// checks the possibility of the first partial half-move or a not first partial half-move
bool BOARD::can_move(CELL a) {
	// first partial half-move
	if (ufirst) {
		// если есть фигуры, которые могут есть, ходить можно только ими
		bool flag = false;
		// обходим доску в поисках фигур нашего цвета, которые могут есть
		for (int i = 0; i < size; i ++) {
			for (int j = 0; j < size; j++) {
				/***** TODO: kings *****/
				if (cells[i][j] == utype && can_move_square(CELL(i, j), 2, utype)) {
					flag = true;
					// если найденная фигура - это наша фигура, всё нормально
					if (a.x == i && a.y == j) return true;
				}
			}
		}
		// если есть фигуры, которые могут есть, а наша фигура к ним не относится, - ходить нельзя
		// если нет фигур, которые могут ходить, ходить можно
		return flag ? false : true;
	}
	// not first partial half-move
	else {
		return (!(a.x == ublocked.x && a.y == ublocked.y && ueaten)) ? 0 : true;
	}
	return false;
}

// checks the possibility of continuing the half-move by current player
bool BOARD::can_move() {
	// the first half-move - can move
	if (ufirst) return true;
	// a non first half-move - can move by blocked figure only
	return moves(ublocked) ? true : false;
}

// gets array of the possible partial half-moves for the cell
// if res is not NULL, moves will be situated there
// return value - number of possible partial half-moves
unsigned int BOARD::moves(CELL figure, CELL *res) {
	unsigned int k = 0; // number of possible partial half-moves
	/* can the figure move? */
	if (!can_move(figure)) return 0;
	/* go round all posible partial half-moves */
	// draughts
	if (IS_DRT(utype)) {
		// eating moves
		k += can_move_square(figure, 2, utype, res);
		// usual moves (they can be executed at first partial half-move if there are nothing for eating)
		if (ufirst && !k) k += can_move_square(figure, 1, utype, res);
	}
	// kings
	else {
		/***** TODO: kings *****/
	}
	/* result */
	return k;
}

// execs the partial half-move
bool BOARD::move(CELL from, CELL to) {
	/***** TODO *****/
	// move has been executed
	return 1;
}
bool BOARD::move(MOVE _move) {return move(_move.from, _move.to);}
bool BOARD::move(int x1, int y1, int x2, int y2) {return move(CELL(x1, y1), CELL(x2, y2));};

