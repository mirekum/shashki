#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

#include "board.h"

using namespace std;

/* методы класса "Доска для игры в шашки" */

// конструктор класса
BOARD::BOARD () {
	// обнуляем всю доску
	b = w = 0;
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j++)
			cells[i][j] = 0;
	// задаём начальное расположение шашек
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

// получение набора возможных ходов
int BOARD::moves(BOARD_CELL a, BOARD_CELL *res) {
	int k = 0; // количество возможных ходов
	/* учём факты, а может ли шашка ходить вообще */
	// если это не первый неполный полуход - проверяем, что наша шашка - заблокированая,
	// и в предыдущем ходу она покушала (факт съедения важен для второго неполного полухода)
	if (!ufirst && !(a.x == ublocked.x && a.y == ublocked.y && ueaten)) return 0;
	// рассмотрим первый неполный полуход
	if (ufirst) {
		// если есть шашки, которые могут есть, ходить можно только ими
		int flag = 0; // нет шашек, которые могут есть
		for (int i = 0; i < size; i ++) {
			for (int j = 0; j < size; j++) {
				if (cells[i][j] == utype && (0
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+2, j+2), utype)
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-2, j+2), utype)
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+2, j-2), utype)
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-2, j-2), utype)
				)) {
					flag = 1; // нашли шашку, которая может есть
					if (a.x == i && a.y == j) {
						// если найденная шашка - это наша шашка, всё нормально
						flag = 0;
						goto lbl1;
					}
				}
			}
		}
		lbl1:
		if (flag) {
			// если есть шашки, которые могут есть, а наша шашка к ним не относится, - ходить нельзя
			return 0;
		}
	}
	/* пересмотрим все возможные ходы */
	// начнём с ходов-поеданий
	if (can_move(a, BOARD_CELL(a.x+2, a.y+2), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x+2, a.y+2); else k++;
	if (can_move(a, BOARD_CELL(a.x-2, a.y+2), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x-2, a.y+2); else k++;
	if (can_move(a, BOARD_CELL(a.x+2, a.y-2), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x+2, a.y-2); else k++;
	if (can_move(a, BOARD_CELL(a.x-2, a.y-2), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x-2, a.y-2); else k++;
	// совершать обычные ходы можно только при первом неполном полуходе, если нечего есть
	if (ufirst && !k) {
		if (can_move(a, BOARD_CELL(a.x+1, a.y+1), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x+1, a.y+1); else k++;
		if (can_move(a, BOARD_CELL(a.x-1, a.y+1), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x-1, a.y+1); else k++;
		if (can_move(a, BOARD_CELL(a.x+1, a.y-1), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x+1, a.y-1); else k++;
		if (can_move(a, BOARD_CELL(a.x-1, a.y-1), utype)) if (res != NULL) res[k++] = BOARD_CELL(a.x-1, a.y-1); else k++;
	}
	// результат
	return k;
}

// выполнение неполного полухода
int BOARD::move(BOARD_CELL /* from */ a, BOARD_CELL /* to */ z) {
	int tmp;
	// если это не первый неполный полуход - проверяем, что наша шашка - заблокированая,
	// и в предыдущем ходу она покушала (факт съедения важен для второго неполного полухода)
	if (!ufirst && !(a.x == ublocked.x && a.y == ublocked.y && ueaten)) return CANMOVE_NO;
	// проверка возможности данного неполного полухода (с заданным цветом)
	if (!(tmp = can_move(a, z, utype))) return CANMOVE_NO;
	// рассмотрим первый неполный полуход
	if (ufirst) {
		// если есть шашки, которые могут есть, ходить можно только ими
		int flag = 0; // нет шашек, которые могут есть
		for (int i = 0; i < size; i ++) {
			for (int j = 0; j < size; j++) {
				if ((0
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+2, j+2), utype)
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-2, j+2), utype)
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+2, j-2), utype)
					|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-2, j-2), utype)
				)) {
					flag = 1; // нашли шашку, которая может есть
					if (a.x == i && a.y == j) {
						// если найденная шашка - это наша шашка, всё нормально
						flag = 0;
						goto lbl1;
					}
				}
			}
		}
		lbl1:
		if (flag) {
			// если есть шашки, которые могут есть, а наша шашка к ним не относится, - ходить нельзя
			return CANMOVE_NO;
		}
		// если шашка может есть - она должна есть
		if ((0
			|| can_move(a, BOARD_CELL(a.x+2, a.y+2), utype)
			|| can_move(a, BOARD_CELL(a.x-2, a.y+2), utype)
			|| can_move(a, BOARD_CELL(a.x+2, a.y-2), utype)
			|| can_move(a, BOARD_CELL(a.x-2, a.y-2), utype)
		) && (1
			&& (z.x != a.x+2 || z.y != a.y+2)
			&& (z.x != a.x-2 || z.y != a.y+2)
			&& (z.x != a.x+2 || z.y != a.y-2)
			&& (z.x != a.x-2 || z.y != a.y-2)
		)) {
			return CANMOVE_NO;
		}
	}
	// рассмотрим не первый неполный полуход
	else {
		// если шашка есть не может - ходить нельзя (конец полухода)
		if (!(0
			|| can_move(a, BOARD_CELL(a.x+2, a.y+2), utype)
			|| can_move(a, BOARD_CELL(a.x-2, a.y+2), utype)
			|| can_move(a, BOARD_CELL(a.x+2, a.y-2), utype)
			|| can_move(a, BOARD_CELL(a.x-2, a.y-2), utype)
		)) {
			return CANMOVE_NO;
		}
	}
	// выполняем ход
	cells[z.x][z.y] = cells[a.x][a.y];
	cells[a.x][a.y] = 0;
	// блокируем шашку
	ublocked = z;
	ufirst = false;
	// если была съедена шашка
	if (tmp == CANMOVE_EAT_W || tmp == CANMOVE_EAT_B) {
		     if ((a.x - z.x) ==  2 && (a.y - z.y) ==  2) cells[a.x - 1][a.y - 1] = 0;
		else if ((a.x - z.x) == -2 && (a.y - z.y) ==  2) cells[a.x + 1][a.y - 1] = 0;
		else if ((a.x - z.x) ==  2 && (a.y - z.y) == -2) cells[a.x - 1][a.y + 1] = 0;
		else if ((a.x - z.x) == -2 && (a.y - z.y) == -2) cells[a.x + 1][a.y + 1] = 0;
		if (tmp == CANMOVE_EAT_W) w--;
		if (tmp == CANMOVE_EAT_B) b--;
		// факт съедения
		ueaten = true;
	}
	// ход выполнен
	return tmp;
}
int BOARD::move(BOARD_MOVE _move) {return move(_move.from, _move.to);}
int BOARD::move(int x1, int y1, int x2, int y2) {return move(BOARD_CELL(x1, y1), BOARD_CELL(x2, y2));};

// возможность неполного полухода
int BOARD::can_move(BOARD_CELL /* from */ a, BOARD_CELL /* to */ z, int _type) {
	// проверяем пределы координат
	if (a.x < 0 || a.y < 0 || a.x >= size || a.y >= size) return CANMOVE_NO;
	if (z.x < 0 || z.y < 0 || z.x >= size || z.y >= size) return CANMOVE_NO;
	// цвет исходной шашки
	int type = cells[a.x][a.y];
	// ходить пустыми клетками мы, к сожалению, не можем
	if (!type) return CANMOVE_NO;
	// ходить чужими шашками мы не можем
	if (_type && type != _type) return CANMOVE_NO;
	// ходить на занятые клетки мы тоже не можем
	if (cells[z.x][z.y]) return CANMOVE_NO;
	// для белых
	if (type > 0) {
		// ходы-поедания (назад можно есть)
		if (((a.x - z.x) ==  2 && (a.y - z.y) ==  2) && cells[a.x - 1][a.y - 1] < 0) return CANMOVE_EAT_B;
		if (((a.x - z.x) == -2 && (a.y - z.y) ==  2) && cells[a.x + 1][a.y - 1] < 0) return CANMOVE_EAT_B;
		if (((a.x - z.x) ==  2 && (a.y - z.y) == -2) && cells[a.x - 1][a.y + 1] < 0) return CANMOVE_EAT_B;
		if (((a.x - z.x) == -2 && (a.y - z.y) == -2) && cells[a.x + 1][a.y + 1] < 0) return CANMOVE_EAT_B;
		// простой ход белых - если не нужно есть, мы можем походить на свободную клётку вперёд влево или вперёд вправо
		if (abs(z.x - a.x) == 1 && (a.y - z.y) == 1) {
			if (a.x - 2 > 0 && a.y - 2 > 0 && cells[a.x - 1][a.y - 1] < 0 && cells[a.x - 2][a.y - 2] == 0) return CANMOVE_NO;
			if (a.x - 2 > 0 && a.y + 2 < 0 && cells[a.x - 1][a.y + 1] < 0 && cells[a.x - 2][a.y + 2] == 0) return CANMOVE_NO;
			if (a.x + 2 < 0 && a.y - 2 > 0 && cells[a.x + 1][a.y - 1] < 0 && cells[a.x + 2][a.y - 2] == 0) return CANMOVE_NO;
			if (a.x + 2 < 0 && a.y + 2 < 0 && cells[a.x + 1][a.y + 1] < 0 && cells[a.x + 2][a.y + 2] == 0) return CANMOVE_NO;
			return CANMOVE_YES;
		}
	}
	// для чёрных
	else if (type < 0) {
		// ходы-поедания (назад можно есть)
		if (((a.x - z.x) ==  2 && (a.y - z.y) ==  2) && cells[a.x - 1][a.y - 1] > 0) return CANMOVE_EAT_W;
		if (((a.x - z.x) == -2 && (a.y - z.y) ==  2) && cells[a.x + 1][a.y - 1] > 0) return CANMOVE_EAT_W;
		if (((a.x - z.x) ==  2 && (a.y - z.y) == -2) && cells[a.x - 1][a.y + 1] > 0) return CANMOVE_EAT_W;
		if (((a.x - z.x) == -2 && (a.y - z.y) == -2) && cells[a.x + 1][a.y + 1] > 0) return CANMOVE_EAT_W;
		// простой ход чёрных - если не нужно есть, мы можем походить на свободную клётку назад влево или назад вправо
		if (abs(z.x - a.x) == 1 && (z.y - a.y) == 1) {
			if (a.x - 2 > 0 && a.y - 2 > 0 && cells[a.x - 1][a.y - 1] > 0 && cells[a.x - 2][a.y - 2] == 0) return CANMOVE_NO;
			if (a.x - 2 > 0 && a.y + 2 < 0 && cells[a.x - 1][a.y + 1] > 0 && cells[a.x - 2][a.y + 2] == 0) return CANMOVE_NO;
			if (a.x + 2 < 0 && a.y - 2 > 0 && cells[a.x + 1][a.y - 1] > 0 && cells[a.x + 2][a.y - 2] == 0) return CANMOVE_NO;
			if (a.x + 2 < 0 && a.y + 2 < 0 && cells[a.x + 1][a.y + 1] > 0 && cells[a.x + 2][a.y + 2] == 0) return CANMOVE_NO;
			return CANMOVE_YES;
		}
	}
	// в остальных случаях ход запрещён
	return CANMOVE_NO;
}
int BOARD::can_move(BOARD_MOVE _move, int _type) {return can_move(_move.from, _move.to, _type);}
int BOARD::can_move(int x1, int y1, int x2, int y2, int _type) {return can_move(BOARD_CELL(x1, y1), BOARD_CELL(x2, y2), _type);};

// возможность продолжения хода
int BOARD::can_move(int _type) {
	// первый неполный полуход - возможность есть
	if (ufirst) return 1;
	// не первый неполный полуход - ходить можно заблокированной шашкой
	return moves(ublocked);
}

// начало полухода
void BOARD::start_move(int _type) {
	// цвет игрока на текущий полуход
	utype = _type;
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
			if (0
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+1, j+1))
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-1, j+1))
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+1, j-1))
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-1, j-1))
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+2, j+2))
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-2, j+2))
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i+2, j-2))
				|| can_move(BOARD_CELL(i, j), BOARD_CELL(i-2, j-2))
			) {
				if (cells[i][j] > 0) tw++;
				if (cells[i][j] < 0) tb++;
			}
		}
	}
	cout << "[белые: " << tw << "/" << w << " | чёрные: " << tb << "/" << b << "]" << endl;
	// проверка выигрышей и ничьи
	if ( tw && !tb) return ISWIN_WHITE;
	if (!tw &&  tb) return ISWIN_BLACK;
	if (!tw && !tb) return ISWIN_DRAW;
	// игра не закончилась
	return ISWIN_GAME;
}

// вывод доски на экран
ostream& operator<< (ostream &cout, BOARD &board) {
	cout << "------ Доска ------" << endl;
	cout << "   0 1 2 3 4 5 6 7 " << endl << endl;
	for (int y = 0; y < board.size; y++) {
		cout << y << "  ";
		for (int x = 0; x < board.size; x++) {
			if (board.cells[x][y] == WHITE)
				cout << "x ";
			else if (board.cells[x][y] == BLACK)
				cout << "o ";
			else if (board.cells[x][y] == WHITE_KING)
				cout << "X ";
			else if (board.cells[x][y] == BLACK_KING)
				cout << "O ";
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << "-------------------";
	return cout;
}
