#include <iostream>
#include "board.h"

// FIGURE -> COLOR
COLOR getColor(FIGURE type) {
	switch (type) {
		case WHITE_PAWN:
		case WHITE_KING:
			return WHITE;
		case BLACK_PAWN:
		case BLACK_KING:
			return BLACK;
		default:
			return NONE;
	}
}

/* methods of class of the board for playing draughts */

// class constructor
// set firstly figures positions and the board state
BOARD::BOARD() {
	// zeroize the board
	b = w = bk = wk = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			scell(i, j, EMPTY);
	// set firstly figures positions
	for (int i = 0; i < size; i += 2) {
		scell(i+1, 0, BLACK_PAWN);
		scell(i,   1, BLACK_PAWN);
		scell(i+1, 2, BLACK_PAWN);
		b += 3;
		scell(i,   5, WHITE_PAWN);
		scell(i+1, 6, WHITE_PAWN);
		scell(i,   7, WHITE_PAWN);
		w += 3;
	}
}

// set cell value
bool BOARD::scell(int x, int y, FIGURE type) {
	if (x < 0 || y < 0 || x >= size || y >= size) {
		return false;
	}
	cells[x][y] = type;
	return true;
}
bool BOARD::scell(CELL figure, FIGURE type) {return scell(figure.x, figure.y, type);}
bool BOARD::scell(int x1, int y1, int x2, int y2) {return scell(x1, y1, gcell(x2, y2));}
bool BOARD::scell(CELL figure1, CELL figure2) {return scell(figure1, gcell(figure2));}

// get cell value
FIGURE BOARD::gcell(int x, int y) {
	if (x < 0 || y < 0 || x >= size || y >= size) {
		return EMPTY;
	}
	return cells[x][y];
}
FIGURE BOARD::gcell(CELL figure) {return gcell(figure.x, figure.y);}

// print the board on the screen
std::ostream& operator<< (std::ostream &cout, BOARD &board) {
	std::cout << "------ Доска ------" << std::endl;
	std::cout << "   0 1 2 3 4 5 6 7 " << std::endl << std::endl;
	for (int y = 0; y < board.size; y++) {
		std::cout << y << "  ";
		for (int x = 0; x < board.size; x++) {
			if (board.cells[x][y] == WHITE_PAWN)
				std::cout << "x ";
			else if (board.cells[x][y] == BLACK_PAWN)
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
void BOARD::startMove(COLOR type) {
	utype = type;
	ufirst = true;
	ueaten = false;
}

// checks the end of the game
GAMESTATE BOARD::isWin() {
	int tb = 0, tw = 0; // number of the figures, which can move
	// check number of the figures
	if (!b) return END_WHITE;
	if (!w) return END_BLACK;
	// check move possibility of the figures
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (getSquareMoves(CELL(i, j), 1) || getSquareMoves(CELL(i, j), 2)) {
				if (IS_WHITE(gcell(i, j))) tw++;
				if (IS_BLACK(gcell(i, j))) tb++;
			}
		}
	}
	// check winning and draw
	if ( tw && !tb) return END_WHITE;
	if (!tw &&  tb) return END_BLACK;
	if (!tw && !tb) return END_DRAW;
	// game continuing
	return END_NONE;
}

// checks the physical possibility of the move from one cell to the other one
bool BOARD::canMove(CELL from, CELL to, CANMOVE *flags, COLOR _type) {
	if (from.x < 0 || from.y < 0 || from.x >= size || from.y >= size) return false;
	if (to.x < 0   || to.y < 0   || to.x >= size   || to.y >= size)   return false;
	FIGURE type = gcell(from);
	// moves by empty cells, by enemy figures and to occupied cells are denied
	if (!type) return false;
	if (_type && getColor(type) != _type) return false;
	if (gcell(to)) return false;
	// check king transformation
	if (flags != NULL && IS_DRT(type)) {
		if (IS_WHITE(type) && to.y == 0) flags->king = WHITE;
		else if (IS_BLACK(type) && to.y == size - 1) flags->king = BLACK;
		else flags->king = NONE;
	}
	// draughts
	if (IS_DRT(type)) {
		FIGURE eaten;
		int x, y;
		if (IS_WHITE(type)) {
			// check eating moves
			if (0
				|| (((from.x - to.x) ==  2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x-1, y = from.y-1)) < 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x+1, y = from.y-1)) < 0)
				|| (((from.x - to.x) ==  2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x-1, y = from.y+1)) < 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x+1, y = from.y+1)) < 0)
			) {
				if (flags != NULL) {flags->eat = eaten; flags->eat_c = CELL(x, y);}
				return true;
			}
			// check common move - if we haven't eat, we can move forward
			if (abs(to.x - from.x) == 1 && (from.y - to.y) == 1) {
				if (from.x - 2 > 0 && from.y - 2 > 0 && gcell(from.x-1, from.y-1) < 0 && gcell(from.x-2, from.y-2) == 0) return false;
				if (from.x + 2 < size && from.y - 2 > 0 && gcell(from.x+1, from.y-1) < 0 && gcell(from.x+2, from.y-2) == 0) return false;
				return true;
			}
		}
		if (IS_BLACK(type)) {
			// check eating moves
			if (0
				|| (((from.x - to.x) ==  2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x-1, y = from.y-1)) > 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x+1, y = from.y-1)) > 0)
				|| (((from.x - to.x) ==  2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x-1, y = from.y+1)) > 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x+1, y = from.y+1)) > 0)
			) {
				if (flags != NULL) {flags->eat = eaten; flags->eat_c = CELL(x, y);}
				return true;
			}
			// check common move - if we haven't eat, we can move back
			if (abs(to.x - from.x) == 1 && (to.y - from.y) == 1) {
				if (from.x - 2 > 0 && from.y + 2 < 0 && gcell(from.x-1, from.y+1) > 0 && gcell(from.x-2, from.y+2) == 0) return false;
				if (from.x + 2 < size && from.y + 2 < 0 && gcell(from.x+1, from.y+1) > 0 && gcell(from.x+2, from.y+2) == 0) return false;
				return true;
			}
		}
	}
	// kings
	if (IS_KNG(type)) {
		bool can_eat = false;
		/* check eating moves */
		// loop to left top corner
		for (int i = from.x - 1, j = from.y - 1, met_enemy = 0; i >= 0 && j >= 0; i--, j--) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break; // not eating move
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true; // eating move detected!
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i+1, j+1); flags->eat_c = CELL(i+1, j+1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		// loop to right top corner
		for (int i = from.x + 1, j = from.y - 1, met_enemy = 0; i < size && j >= 0; i++, j--) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break; // not eating move
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true; // eating move detected!
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i-1, j+1); flags->eat_c = CELL(i-1, j+1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		// loop to left bottom corner
		for (int i = from.x - 1, j = from.y + 1, met_enemy = 0; i >= 0 && j < size; i--, j++) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break; // not eating move
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true; // eating move detected!
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i+1, j-1); flags->eat_c = CELL(i+1, j-1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		// loop to right bottom corner
		for (int i = from.x + 1, j = from.y + 1, met_enemy = 0; i < size && j < size; i++, j++) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break; // not eating move
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true; // eating move detected!
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i-1, j-1); flags->eat_c = CELL(i-1, j-1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		// we could eat, but we haven't done it
		if (can_eat) return false; // fail!
		/* check common moves */
		// loop to left top corner
		if (to.x < from.x && to.y < from.y) {
			for (int i = from.x - 1, j = from.y - 1; i >= to.x && j >= to.y; i--, j--) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}
		// loop to right top corner
		if (to.x > from.x && to.y < from.y) {
			for (int i = from.x + 1, j = from.y - 1; i <= to.x && j >= to.y; i++, j--) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}
		// loop to left bottom corner
		if (to.x < from.x && to.y > from.y) {
			for (int i = from.x - 1, j = from.y + 1; i >= to.x && j <= to.y; i--, j++) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}
		// loop to right bottom corner
		if (to.x > from.x && to.y > from.y) {
			for (int i = from.x + 1, j = from.y + 1; i <= to.x && j <= to.y; i++, j++) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}
		
		return true;
	}
	
	return false;
}
bool BOARD::canMove(MOVE _move, CANMOVE *flags, COLOR _type) {return canMove(_move.from, _move.to, flags, _type);}bool BOARD::canMove(int x1, int y1, int x2, int y2, CANMOVE *flags, COLOR _type) {return canMove(CELL(x1, y1), CELL(x2, y2), flags, _type);};

// checks the possibility of move into square corners
unsigned int BOARD::getSquareMoves(CELL figure, int dep, COLOR type, CELL *res, CANMOVE *flags) {
	unsigned int k = 0;
	if (dep <= 0) return 0;
	if (canMove(figure, CELL(figure.x+dep, figure.y+dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x+dep, figure.y+dep); else k++;
	if (canMove(figure, CELL(figure.x-dep, figure.y+dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x-dep, figure.y+dep); else k++;
	if (canMove(figure, CELL(figure.x+dep, figure.y-dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x+dep, figure.y-dep); else k++;
	if (canMove(figure, CELL(figure.x-dep, figure.y-dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x-dep, figure.y-dep); else k++;
	return k;
}

// checks the possibility of eating
bool BOARD::canEat(CELL figure) {
	FIGURE type = gcell(figure);
	if (IS_DRT(type)) {
		return (getSquareMoves(figure, 2, getColor(type))) ? true : false;
	}
	if (IS_KNG(type)) {
		CANMOVE flags;
		for (int k = 2; k <= size/2; k++) {
			getSquareMoves(figure, k, getColor(type), NULL, &flags);
			if (flags.eat) return true;
		}
		return false;
	}
	
	return false;
}
bool BOARD::canEat(int x, int y) {return canEat(CELL(x, y));}

// checks the possibility of the first partial half-move or a not first partial half-move
bool BOARD::canMove(CELL figure) {
	// first partial half-move
	if (ufirst) {
		// if there are figures which can eat, we can move only them
		bool flag = false;
		// go round the board finding our figures which can eat
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (getColor(gcell(i, j)) == utype && canEat(CELL(i, j))) {
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
	
	return false;
}

// checks the possibility of continuing the half-move by current player
bool BOARD::canMove() {
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
	FIGURE type = gcell(figure); // figure type
	/* can the figure move? */
	if (!canMove(figure)) return 0;
	/* go round all posible partial half-moves */
	// draughts
	if (IS_DRT(type)) {
		// eating moves
		k += getSquareMoves(figure, 2, utype, res);
		// common moves
		if (ufirst && !k) k += getSquareMoves(figure, 1, utype, res);
	}
	// kings
	if (IS_KNG(type)) {
		CANMOVE flags;
		// eating moves
		for (int q = 2; q <= size/2; q++) {
			if (canMove(figure, CELL(figure.x+q, figure.y+q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y+q); else k++;
			if (canMove(figure, CELL(figure.x-q, figure.y+q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y+q); else k++;
			if (canMove(figure, CELL(figure.x+q, figure.y-q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y-q); else k++;
			if (canMove(figure, CELL(figure.x-q, figure.y-q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y-q); else k++;
		}
		// common moves
		if (ufirst && !k) {
			for (int q = 1; q <= size/2; q++) {
				if (canMove(figure, CELL(figure.x+q, figure.y+q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y+q); else k++;
				if (canMove(figure, CELL(figure.x-q, figure.y+q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y+q); else k++;
				if (canMove(figure, CELL(figure.x+q, figure.y-q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y-q); else k++;
				if (canMove(figure, CELL(figure.x-q, figure.y-q), &flags, utype))
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
	if (!canMove(from, to, &flags, utype)) return false;
	/* can the figure move? */
	// first partial half-move
	if (ufirst) {
		if (!canMove(from)) return false;
		// if the figure can eat - it must eat
		if (canEat(from) && !flags.eat) return false;
	}
	// not first partial half-move
	if (!ufirst) {
		if (!canMove(from)) return false;
		// if the figure can't eat - the end
		if (!canEat(from)) return false;
	}
	/* exec move */
	// move the figure
	scell(to, from);
	scell(from, EMPTY);
	// block the figure
	ublocked = to;
	ufirst = false;
	// if we've eaten the enemy figure
	if (flags.eat) {
		scell(flags.eat_c, EMPTY); // zeroize the eaten figure
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
	if (flags.king && IS_DRT(gcell(to))) {
		// transform the figure to the king
		if (IS_WHITE(flags.king)) {
			scell(to, WHITE_KING);
			wk++;
		}
		if (IS_BLACK(flags.king)) {
			scell(to, BLACK_KING);
			bk++;
		}
	}
	// move has been executed
	return true;
}
bool BOARD::move(MOVE _move) {return move(_move.from, _move.to);}
bool BOARD::move(int x1, int y1, int x2, int y2) {return move(CELL(x1, y1), CELL(x2, y2));};

