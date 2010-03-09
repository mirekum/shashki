#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ncurses.h>

#include "board.h"
#include "player.h"
#include "ai.h"
#include "game.h"

using namespace std;

/* методы класса "Игрок-человек" */

// выполнение хода
BOARD_MOVE AI_PLAYER::move(BOARD board) {
	// неполный полуход
	BOARD_MOVE res;
	// выбираем лучший неполный полуход
	choose(board, type, &res);
	// результат
	return res;
}

// выбор наилучшего хода
int AI_PLAYER::choose(BOARD board, int _type, BOARD_MOVE *res, int step, int last, bool smflag) {
	// не последний ход
	if (step < max_step) {
		bool minimax = (step % 2 == 0 ? 1 : 0); // минимум или максимум необходимо считать (1 - max, 0 - min)
		int max = -MINMAX_END, min = MINMAX_END; // максимум и минимум по СОФ
		// двойной цикл по шашкам
		for (int i = 0; i < board.getSize(); i++) {
			for (int j = 0; j < board.getSize(); j++) {
				int m;
				BOARD_CELL d(i, j), arr[16];
				// если это первый неполный полуход - начинаем полуход
				if (smflag) board.start_move(_type);
				// возможные ходы текущей шашки
				m = board.moves(d, arr);
				// цикл по возможным ходам текущей шашки
				for (int k = 0; k < m; k++) {
					int s; // текущая величина соф
					// копия доски
					BOARD board_copy = board;
					// если это первый неполный полуход - начинаем полуход
					if (smflag) board.start_move(_type);
					// выполняем текущий возможный ход
					board_copy.move(d, arr[k]);
					// если полуход не окончен
					if (board_copy.moves(arr[k])) {
						// продолжаем полуход
						s = choose(board_copy, _type, NULL, step, (minimax ? max : min), false);
					}
					// если полуход окончен
					else {
						// начинаем полуход противника
						s = choose(board_copy, _type == WHITE ? BLACK : WHITE, NULL, step + 1, (minimax ? max : min), true);
					}
					// считаем максимум по СОФ
					if (minimax) {
						// подсчёт максимума
						if (s >= max) {
							if (res != NULL) {
								res->from = d;
								res->to = arr[k];
							}
							max = s;
						}
						// альфа-бета усечение
						if (ab && s > last && last > -MINMAX_END && last < MINMAX_END) {
							return s;
						}
					}
					// считаем минимум по СОФ
					else {
						// подсчёт минимума
						if (s <= min) {
							if (res != NULL) {
								res->from = d;
								res->to = arr[k];
							}
							min = s;
						}
						// альфа-бета усечение
						if (ab && s < last && last > -MINMAX_END && last < MINMAX_END) {
							return s;
						}
					}
					// для отладки
					if (step <= 0 && 0) {
						cout << "> [" << step << "/" << max_step << ", " << s << ", " << last << "] " <<
							"(" << d.x << ", " << d.y << ") -> (" << arr[k].x << ", " << arr[k].y << ")" << endl;
					}
				}
				
			}
		}
		// перебор ветви закончен
		return (minimax ? max : min);
	}
	// последний ход
	else {
		return srf(board);
	}
	// сюда мы попасть не должны
	return 0;
}

// СОФ
int AI_PLAYER::srf(BOARD board) {
	// для белых
	if (type > 0) {
		return board.white() - board.black();
	}
	// для чёрных
	else if (type < 0) {
		return board.black() - board.white();
	}
	// для неопределённого значения
	return 0;
}

