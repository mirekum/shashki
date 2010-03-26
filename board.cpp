#include <iostream>
#include "board.h"

// FIGURE -> PCOLOR
PCOLOR COLOR(FIGURE type) {
	switch (type) {
		case WHITE:
		case WHITE_KING:
			return PWHITE;
		case BLACK:
		case BLACK_KING:
			return PBLACK;
		default:
			return PNONE;
	}
}

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
	utype = type;
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
			if (get_square_moves(CELL(i, j), 1) || get_square_moves(CELL(i, j), 2)) {
				if (IS_WHITE(cells[i][j])) tw++;
				if (IS_BLACK(cells[i][j])) tb++;
			}
		}
	}
	// some debug info
	std::cout << "[белые: " << tw << "(" << wk << ")" << "/" << w << " | чёрные: " << tb << "(" << bk << ")" << "/" << b << "]" << std::endl;
	// check winning and draw
	if ( tw && !tb) return ISWIN_WHITE;
	if (!tw &&  tb) return ISWIN_BLACK;
	if (!tw && !tb) return ISWIN_DRAW;
	// game continuing
	return ISWIN_GAME;
}

// checks the physical possibility of the move from one cell to the other one
bool BOARD::can_move(CELL from, CELL to, CANMOVE *flags, PCOLOR _type) {
	// check coordinate limits
	if (from.x < 0 || from.y < 0 || from.x >= size || from.y >= size) return false;
	if (to.x < 0   || to.y < 0   || to.x >= size   || to.y >= size) return false;
	// initial figure color
	FIGURE type = cells[from.x][from.y];
	// moves by empty cells, by enemy figures and to occupied cells are denied
	if (!type) return false;
	if (_type && COLOR(type) != _type) return false;
	if (cells[to.x][to.y]) return false;
	// check king transformation
	if (flags != NULL && IS_DRT(type)) {
		// whites
		if (IS_WHITE(type) && to.y == 0) {
			flags->king = WHITE;
			flags->king_c = to;
		}
		// blacks
		else if (IS_BLACK(type) && to.y == size - 1) {
			flags->king = BLACK;
			flags->king_c = to;
		}
	}
	// draughts
	if (IS_DRT(type)) {
		FIGURE eaten;
		int x, y;
		// whites
		if (IS_WHITE(type)) {
			// eating moves
			if (0
				|| (((from.x - to.x) ==  2 && (from.y - to.y) ==  2) && (eaten = cells[x = from.x-1][y = from.y-1]) < 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) ==  2) && (eaten = cells[x = from.x+1][y = from.y-1]) < 0)
				|| (((from.x - to.x) ==  2 && (from.y - to.y) == -2) && (eaten = cells[x = from.x-1][y = from.y+1]) < 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) == -2) && (eaten = cells[x = from.x+1][y = from.y+1]) < 0)
			) {
				if (flags != NULL) {flags->eat = eaten; flags->eat_c = CELL(x, y);}
				return true;
			}
			// common move - if we haven't eat, we can move forward
			if (abs(to.x - from.x) == 1 && (from.y - to.y) == 1) {
				if (from.x - 2 > 0 && from.y - 2 > 0 && cells[from.x-1][from.y-1] < 0 && cells[from.x-2][from.y-2] == 0) return false;
				if (from.x + 2 < 0 && from.y - 2 > 0 && cells[from.x+1][from.y-1] < 0 && cells[from.x+2][from.y-2] == 0) return false;
				return true;
			}
		}
		// blacks
		if (IS_BLACK(type)) {
			// eating moves
			if (0
				|| (((from.x - to.x) ==  2 && (from.y - to.y) ==  2) && (eaten = cells[x = from.x-1][y = from.y-1]) > 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) ==  2) && (eaten = cells[x = from.x+1][y = from.y-1]) > 0)
				|| (((from.x - to.x) ==  2 && (from.y - to.y) == -2) && (eaten = cells[x = from.x-1][y = from.y+1]) > 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) == -2) && (eaten = cells[x = from.x+1][y = from.y+1]) > 0)
			) {
				if (flags != NULL) {flags->eat = eaten; flags->eat_c = CELL(x, y);}
				return true;
			}
			// common move - if we haven't eat, we can move back
			if (abs(to.x - from.x) == 1 && (to.y - from.y) == 1) {
				if (from.x - 2 > 0 && from.y + 2 < 0 && cells[from.x-1][from.y+1] > 0 && cells[from.x-2][from.y+2] == 0) return false;
				if (from.x + 2 < 0 && from.y + 2 < 0 && cells[from.x+1][from.y+1] > 0 && cells[from.x+2][from.y+2] == 0) return false;
				return true;
			}
		}
	}
	// kings
	if (IS_KNG(type)) {
		unsigned int enemy_count = 0;
		// loop to left top corner
		for (int i = from.x - 1, j = from.y - 1; i >= to.x && j >= to.y; i--, j--) {
			if ((IS_WHITE(type) && IS_WHITE(cells[i][j])) || (IS_BLACK(type) && IS_BLACK(cells[i][j]))) return false;
			if (enemy_count) {
				if (i == to.x && j == to.y) {
					if (flags != NULL) {flags->eat = cells[i+1][j+1]; flags->eat_c = CELL(i+1, j+1);}
					return true;
				}
				return false;
			}
			if ((IS_WHITE(type) && IS_BLACK(cells[i][j])) || (IS_BLACK(type) && IS_WHITE(cells[i][j]))) enemy_count++;
		}
		// loop to right top corner
		for (int i = from.x + 1, j = from.y - 1; i <= to.x && j >= to.y; i++, j--) {
			if ((IS_WHITE(type) && IS_WHITE(cells[i][j])) || (IS_BLACK(type) && IS_BLACK(cells[i][j]))) return false;
			if (enemy_count) {
				if (i == to.x && j == to.y) {
					if (flags != NULL) {flags->eat = cells[i-1][j+1]; flags->eat_c = CELL(i-1, j+1);}
					return true;
				}
				return false;
			}
			if ((IS_WHITE(type) && IS_BLACK(cells[i][j])) || (IS_BLACK(type) && IS_WHITE(cells[i][j]))) enemy_count++;
		}
		// loop to left bottom corner
		for (int i = from.x - 1, j = from.y + 1; i >= to.x && j <= to.y; i--, j++) {
			if ((IS_WHITE(type) && IS_WHITE(cells[i][j])) || (IS_BLACK(type) && IS_BLACK(cells[i][j]))) return false;
			if (enemy_count) {
				if (i == to.x && j == to.y) {
					if (flags != NULL) {flags->eat = cells[i+1][j-1]; flags->eat_c = CELL(i+1, j-1);}
					return true;
				}
				return false;
			}
			if ((IS_WHITE(type) && IS_BLACK(cells[i][j])) || (IS_BLACK(type) && IS_WHITE(cells[i][j]))) enemy_count++;
		}
		// loop to right bottom corner
		for (int i = from.x + 1, j = from.y + 1; i <= to.x, j <= to.y; i++, j++) {
			if ((IS_WHITE(type) && IS_WHITE(cells[i][j])) || (IS_BLACK(type) && IS_BLACK(cells[i][j]))) return false;
			if (enemy_count) {
				if (i == to.x && j == to.y) {
					if (flags != NULL) {flags->eat = cells[i-1][j-1]; flags->eat_c = CELL(i-1, j-1);}
					return true;
				}
				return false;
			}
			if ((IS_WHITE(type) && IS_BLACK(cells[i][j])) || (IS_BLACK(type) && IS_WHITE(cells[i][j]))) enemy_count++;
		}
		// no eating
		if (!enemy_count) return true;
	}
	// move is denied
	return false;
}
bool BOARD::can_move(MOVE _move, CANMOVE *flags, PCOLOR _type) {return can_move(_move.from, _move.to, flags, _type);}bool BOARD::can_move(int x1, int y1, int x2, int y2, CANMOVE *flags, PCOLOR _type) {return can_move(CELL(x1, y1), CELL(x2, y2), flags, _type);};

// checks the possibility of move into square corners
unsigned int BOARD::get_square_moves(CELL figure, int dep, PCOLOR type, CELL *res, CANMOVE *flags) {
	unsigned int k = 0;
	if (dep <= 0) return 0;
	if (can_move(figure, CELL(figure.x+dep, figure.y+dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x+dep, figure.y+dep); else k++;
	if (can_move(figure, CELL(figure.x-dep, figure.y+dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x-dep, figure.y+dep); else k++;
	if (can_move(figure, CELL(figure.x+dep, figure.y-dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x+dep, figure.y-dep); else k++;
	if (can_move(figure, CELL(figure.x-dep, figure.y-dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x-dep, figure.y-dep); else k++;
	return k;
}

// checks the possibility of eating
bool BOARD::can_eat(CELL figure) {
	FIGURE type = cells[figure.x][figure.y];
	// draught
	if (IS_DRT(type)) {
		return (get_square_moves(figure, 2, COLOR(type))) ? true : false;
	}
	// king
	if (IS_KNG(type)) {
		CANMOVE flags;
		for (int k = 2; k <= size/2; k++) {
			get_square_moves(figure, k, COLOR(type), NULL, &flags);
			if (flags.eat) return true;
		}
		return false;
	}
	// nothing
	return false;
}

// checks the possibility of the first partial half-move or a not first partial half-move
bool BOARD::can_move(CELL figure) {
	// first partial half-move
	if (ufirst) {
		// if there are figures which can eat, we can move only them
		bool flag = false;
		// go round the board finding our figures which can eat
		for (int i = 0; i < size; i ++) {
			for (int j = 0; j < size; j++) {
				if (COLOR(cells[i][j]) == utype && can_eat(CELL(i, j))) {
					flag = true;
					// found figure is our figure
					if (i == figure.x && j == figure.y) return true;
				}
			}
		}
		// result
		// если есть фигуры, которые могут есть, а наша фигура к ним не относится, - ходить нельзя
		// если нет фигур, которые могут ходить, ходить можно
		return flag ? false : true;
	}
	// not first partial half-move
	else {
		return (!(figure.x == ublocked.x && figure.y == ublocked.y && ueaten)) ? false : true;
	}
	// nothing
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
	FIGURE type = cells[figure.x][figure.y]; // figure type
	/* can the figure move? */
	if (!can_move(figure)) return 0;
	/* go round all posible partial half-moves */
	// draughts
	if (IS_DRT(type)) {
		// eating moves
		k += get_square_moves(figure, 2, utype, res);
		// common moves
		if (ufirst && !k) k += get_square_moves(figure, 1, utype, res);
	}
	// kings
	if (IS_KNG(type)) {
		CANMOVE flags;
		// eating moves
		for (int q = 2; q <= size/2; q++) {
			if (can_move(figure, CELL(figure.x+q, figure.y+q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y+q); else k++;
			if (can_move(figure, CELL(figure.x-q, figure.y+q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y+q); else k++;
			if (can_move(figure, CELL(figure.x+q, figure.y-q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y-q); else k++;
			if (can_move(figure, CELL(figure.x-q, figure.y-q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y-q); else k++;
		}
		// common moves
		if (ufirst && !k) {
			for (int q = 1; q <= size/2; q++) {
				if (can_move(figure, CELL(figure.x+q, figure.y+q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y+q); else k++;
				if (can_move(figure, CELL(figure.x-q, figure.y+q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y+q); else k++;
				if (can_move(figure, CELL(figure.x+q, figure.y-q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y-q); else k++;
				if (can_move(figure, CELL(figure.x-q, figure.y-q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y-q); else k++;
			}
		}
	}
	/* result */
	return k;
}

// execs the partial half-move
bool BOARD::move(CELL from, CELL to) {
	CANMOVE flags;
	/* can the figure move into target? */
	if (!can_move(from, to, &flags, utype)) return false;
	/* can the figure move? */
	// first partial half-move
	if (ufirst) {
		if (!can_move(from)) return false;
		// if the figure can eat - it must eat
		if (can_eat(from) && !flags.eat) return false;
	}
	// not first partial half-move
	if (!ufirst) {
		if (!can_move(from)) return false;
		// if the figure can't eat - the end
		if (!can_eat(from)) return false;
	}
	/* exec move */
	// move the figure
	cells[to.x][to.y] = cells[from.x][from.y];
	cells[from.x][from.y] = NONE;
	// block the figure
	ublocked = to;
	ufirst = false;
	// if we've eaten the enemy figure
	if (flags.eat) {
		// zeroize the eaten figure
		cells[flags.eat_c.x][flags.eat_c.y] = NONE;
		// change numbers of the figures
		if (IS_WHITE(flags.eat)) {
			if (IS_KNG(flags.eat)) wk--;
			w--;
		}
		if (IS_BLACK(flags.eat)) {
			if (IS_KNG(flags.eat)) bk--;
			b--;
		}
		// set flag, indicating eating
		ueaten = true;
	}
	// if the draugth has to be transformed to the king
	if (flags.king) {
		// transform the figure to the king
		cells[flags.king_c.x][flags.king_c.y] = IS_WHITE(flags.king) ? WHITE_KING : (IS_BLACK(flags.king) ? BLACK_KING : NONE);
		// change numbers of the kings
		if (IS_WHITE(flags.king)) wk++;
		if (IS_BLACK(flags.king)) bk++;
	}
	// move has been executed
	return true;
}
bool BOARD::move(MOVE _move) {return move(_move.from, _move.to);}
bool BOARD::move(int x1, int y1, int x2, int y2) {return move(CELL(x1, y1), CELL(x2, y2));};

