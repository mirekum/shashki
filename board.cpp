#include <iostream>
#include <stdlib.h>
#include "board.h"

/* methods of class of the board for playing draughts */

// class constructor
// set firstly figures positions and the board state
BOARD::BOARD () {
	// zeroize the board
	b = w = bk = wk = 0;
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j++)
			cells[i][j] = 0;
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

// small assistant functions
int BOARD::can_move_S_sq(CELL a, int dep, int type, CELL *res) {
	int k = 0;
	if (dep <= 0) return 0;
	if (can_move(a, CELL(a.x+dep, a.y+dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x+dep, a.y+dep); else k++;
	if (can_move(a, CELL(a.x-dep, a.y+dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x-dep, a.y+dep); else k++;
	if (can_move(a, CELL(a.x+dep, a.y-dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x+dep, a.y-dep); else k++;
	if (can_move(a, CELL(a.x-dep, a.y-dep), NULL, type)) if (res != NULL) res[k++] = CELL(a.x-dep, a.y-dep); else k++;
	return k;
}
int BOARD::can_scnd(CELL a) {
	if (ufirst) return 1;
	// проверяем, что наша фигура - заблокированая, и в предыдущем ходу она покушала
	return (!(a.x == ublocked.x && a.y == ublocked.y && ueaten)) ? 0 : 1;
}
int BOARD::can_frst(CELL a) {
	if (!ufirst) return 1;
	// если есть фигуры, которые могут есть, ходить можно только ими
	int flag = 0;
	// обходим доску в поисках фигур нашего цвета, которые могут есть
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j++) {
			/***** TODO: kings *****/
			if (cells[i][j] == utype && can_move_S_sq(CELL(i, j), 2, utype)) {
				flag = 1;
				// если найденная фигура - это наша фигура, всё нормально
				if (a.x == i && a.y == j) return 1;
			}
		}
	}
	// если есть фигуры, которые могут есть, а наша фигура к ним не относится, - ходить нельзя
	// если нет фигур, которые могут ходить, ходить можно
	return flag == 1 ? 0 : 1;
}

// получение набора возможных ходов
// a - исходная фигура
// ходы помещаются по адресу res, если он не NULL
// возвращаемое значение - кол-во возможных ходов
int BOARD::moves(CELL a, CELL *res) {
	int k = 0; // количество возможных ходов
	/* учтём факты, а может ли фигура ходить вообще */
	// первый неполный полуход
	if (ufirst && !can_frst(a)) return 0;
	// не первый неполный полуход
	if (!ufirst && !can_scnd(a)) return 0;
	/* пересмотрим все возможные ходы */
	// шашки
	if (abs(utype) == 1) {
		// начнём с ходов-поеданий
		k += can_move_S_sq(a, 2, utype, res);
		// совершать обычные ходы можно только при первом неполном полуходе, если нечего есть
		if (ufirst && !k) k += can_move_S_sq(a, 1, utype, res);
	}
	// дамки
	else {
		/***** TODO: kings *****/
	}
	/* результат */
	return k;
}

// выполнение неполного полухода
// a - исходная фигура
// z - место, в которое необходимо совершить ход
// возвращаемое значение - 0 (так ходить нельзя) или 1 (ход выполнен)
int BOARD::move(CELL /* from */ a, CELL /* to */ z) {
	CANMOVE flags;
	/* может ли фигура ходить вообще */
	// первый неполный полуход
	if (ufirst) {
		if (!can_frst(a)) return 0;
		// если фигура может есть - она должна есть
		/***** TODO: kings *****/
		if (can_move_S_sq(a, 2, utype) && (1
			&& (z.x != a.x+2 || z.y != a.y+2)
			&& (z.x != a.x-2 || z.y != a.y+2)
			&& (z.x != a.x+2 || z.y != a.y-2)
			&& (z.x != a.x-2 || z.y != a.y-2)
		)) return 0;
	}
	// не первый неполный полуход
	if (!ufirst) {
		if (!can_scnd(a)) return 0;
		// если фигура есть не может - ходить нельзя (конец полухода)
		/***** TODO: kings *****/
		if (!can_move_S_sq(a, 2, utype)) return 0;
	}
	/* может ли фигура ходить в заданную точку */
	if (!can_move(a, z, &flags, utype)) return 0;
	/* выполняем ход */
	// перемещаем фигуру
	cells[z.x][z.y] = cells[a.x][a.y];
	cells[a.x][a.y] = 0;
	// блокируем фигуру
	ublocked = z;
	ufirst = false;
	// если была съедена фигура
	if (flags.eat) {
		/***** TODO: kings *****/
		     if ((a.x - z.x) ==  2 && (a.y - z.y) ==  2) cells[a.x - 1][a.y - 1] = 0;
		else if ((a.x - z.x) == -2 && (a.y - z.y) ==  2) cells[a.x + 1][a.y - 1] = 0;
		else if ((a.x - z.x) ==  2 && (a.y - z.y) == -2) cells[a.x - 1][a.y + 1] = 0;
		else if ((a.x - z.x) == -2 && (a.y - z.y) == -2) cells[a.x + 1][a.y + 1] = 0;
		if (flags.eat > 0) w--;
		if (flags.eat < 0) b--;
		// факт съедения
		ueaten = true;
	}
	// если шашка стала дамкой
	if (flags.king) {
		/***** TODO: kings *****/
		
	}
	// ход выполнен
	return 1;
}
int BOARD::move(MOVE _move) {return move(_move.from, _move.to);}
int BOARD::move(int x1, int y1, int x2, int y2) {return move(CELL(x1, y1), CELL(x2, y2));};

// возможность неполного полухода
// a - исходная фигура
// z - место, в которое необходимо совершить ход
// flags - флаги хода
// _type - цвет фигуры (не имеет значения: 0, белые: >0, чёрные: <0)
// возвращаемое значение - 0 (так ходить нельзя) или 1 (ход выполнен)
int BOARD::can_move(CELL /* from */ a, CELL /* to */ z, CANMOVE *flags, int _type) {
	// проверяем пределы координат
	if (a.x < 0 || a.y < 0 || a.x >= size || a.y >= size) return 0;
	if (z.x < 0 || z.y < 0 || z.x >= size || z.y >= size) return 0;
	// цвет исходной шашки
	int type = cells[a.x][a.y];
	// ходить пустыми клетками мы, к сожалению, не можем
	if (!type) return 0;
	// ходить чужими шашками мы не можем
	if (_type && type != _type) return 0;
	// ходить на занятые клетки мы тоже не можем
	if (cells[z.x][z.y]) return 0;
	// учтём превращение в дамки
	if (flags != NULL) {
		// для белых
		if (type > 0 && z.y == 0) flags->king = WHITE;
		// для чёрных
		else if (type < 0 && z.y == size - 1) flags->king = BLACK;
	}
	// для белых
	if (type > 0) {
		// шашки
		if (abs(type) == 1) {
			int c = 0;
			// ходы-поедания
			if (0
				|| (((a.x - z.x) ==  2 && (a.y - z.y) ==  2) && (c = cells[a.x - 1][a.y - 1]) < 0)
				|| (((a.x - z.x) == -2 && (a.y - z.y) ==  2) && (c = cells[a.x + 1][a.y - 1]) < 0)
				|| (((a.x - z.x) ==  2 && (a.y - z.y) == -2) && (c = cells[a.x - 1][a.y + 1]) < 0)
				|| (((a.x - z.x) == -2 && (a.y - z.y) == -2) && (c = cells[a.x + 1][a.y + 1]) < 0)
			) {
				if (flags != NULL) flags->eat = c;
				return 1;
			}
			// простой ход белых - если не нужно есть, мы можем походить на свободную клётку вперёд влево или вперёд вправо
			if (abs(z.x - a.x) == 1 && (a.y - z.y) == 1) {
				if (a.x - 2 > 0 && a.y - 2 > 0 && cells[a.x - 1][a.y - 1] < 0 && cells[a.x - 2][a.y - 2] == 0) return 0;
				if (a.x + 2 < 0 && a.y - 2 > 0 && cells[a.x + 1][a.y - 1] < 0 && cells[a.x + 2][a.y - 2] == 0) return 0;
				return 1;
			}
		}
		// дамки
		else {
			/***** TODO: kings *****/
		}
	}
	// для чёрных
	else if (type < 0) {
		// шашки
		if (abs(type) == 1) {
			int c = 0;
			// ходы-поедания
			if (0
				|| (((a.x - z.x) ==  2 && (a.y - z.y) ==  2) && (c = cells[a.x - 1][a.y - 1]) > 0)
				|| (((a.x - z.x) == -2 && (a.y - z.y) ==  2) && (c = cells[a.x + 1][a.y - 1]) > 0)
				|| (((a.x - z.x) ==  2 && (a.y - z.y) == -2) && (c = cells[a.x - 1][a.y + 1]) > 0)
				|| (((a.x - z.x) == -2 && (a.y - z.y) == -2) && (c = cells[a.x + 1][a.y + 1]) > 0)
			) {
				if (flags != NULL) flags->eat = c;
				return 1;
			}
			// простой ход чёрных - если не нужно есть, мы можем походить на свободную клётку назад влево или назад вправо
			if (abs(z.x - a.x) == 1 && (z.y - a.y) == 1) {
				if (a.x - 2 > 0 && a.y + 2 < 0 && cells[a.x - 1][a.y + 1] > 0 && cells[a.x - 2][a.y + 2] == 0) return 0;
				if (a.x + 2 < 0 && a.y + 2 < 0 && cells[a.x + 1][a.y + 1] > 0 && cells[a.x + 2][a.y + 2] == 0) return 0;
				return 1;
			}
		}
		// дамки
		else {
			/***** TODO: kings *****/
		}
	}
	// в остальных случаях ход запрещён
	return 0;
}
int BOARD::can_move(MOVE _move, CANMOVE *flags, int _type) {return can_move(_move.from, _move.to, flags, _type);}
int BOARD::can_move(int x1, int y1, int x2, int y2, CANMOVE *flags, int _type) {return can_move(CELL(x1, y1), CELL(x2, y2), flags, _type);};

// возможность продолжения полухода
// (возможность выполнения неполного полухода в текущий момент времени данным игроком)
int BOARD::can_move() {
	// первый неполный полуход - возможность есть
	if (ufirst) return 1;
	// не первый неполный полуход - ходить можно заблокированной фигурой
	return moves(ublocked) ? 1 : 0;
}

// начало полухода
void BOARD::start_move(int type) {
	// цвет игрока на текущий полуход
	utype = type;
	// обнуляем флаг, указывающий на первый неполный полуход
	ufirst = true;
	// обнуляем флаг, указывающий на факт съедения в прошлом неполном полуходе
	ueaten = false;
}

// проверка конца игры (одна из сторон выиграла)
int BOARD::is_win() {
	int tb = 0, tw = 0; // кол-во незапертых шашек
	// проверяем наличие шашек на доске
	if (!b) return ISWIN_WHITE;
	if (!w) return ISWIN_BLACK;
	// проверяем возможность хода шашек
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (can_move_S_sq(CELL(i, j), 1) || can_move_S_sq(CELL(i, j), 2)) {
				if (cells[i][j] > 0) tw++;
				if (cells[i][j] < 0) tb++;
			}
		}
	}
	std::cout << "[белые: " << tw << "/" << w << " | чёрные: " << tb << "/" << b << "]" << std::endl;
	// проверяем выигрыши и ничью
	if ( tw && !tb) return ISWIN_WHITE;
	if (!tw &&  tb) return ISWIN_BLACK;
	if (!tw && !tb) return ISWIN_DRAW;
	// игра не закончилась
	return ISWIN_GAME;
}

// вывод доски на экран
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
				std::cout << "X ";
			else if (board.cells[x][y] == BLACK_KING)
				std::cout << "O ";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << "-------------------";
	return std::cout;
}
