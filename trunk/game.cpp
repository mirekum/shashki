#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "board.h"
#include "player.h"
#include "human.h"
#include "ai.h"
#include "game.h"

using namespace std;

/* методы класса "Игра в шашки" */

// конструктор класса
GAME::GAME (int w, int b) {
	/* подготовка к игре */
	// игрок белыми
	wp = createPlayer(w);
	wp->setType(WHITE);
	// игрок чёрными
	bp = createPlayer(b);
	bp->setType(BLACK);
	/* игровой цикл */
	if (wp != NULL && bp != NULL)
		process();
	else
		cout << "Error: undefined type of player(s)!" << endl;
}

PLAYER* GAME::createPlayer(int plr) {
	switch (plr) {
		case HUMAN:
			return new HUMAN_PLAYER();
		case AI:
			return new AI_PLAYER();
		case AI2:
			return new AI_PLAYER2();
		default:
			return NULL;
	}
}

// игровой цикл
void GAME::process () {
	do {
		int res_flag; // флаг результата игры
		
		// ход белых
		cout << "*** ХОД БЕЛЫХ ***" << endl;
		board.start_move(WHITE);
		do {
			cout << board << endl;
			// запрашиваем неполный полуход и ходим
			board.move(wp->move(board));
			cout << "[жмакни ENTER]" << endl;
			getchar();
		}
		// проверяем, есть ли ещё неполные полуходы
		while (board.can_move(WHITE));
		// проверка на выигрыш
		if (res_flag = board.is_win()) return result(res_flag);
		
		// ход чёрных
		cout << "*** ХОД ЧЁРНЫХ ***" << endl;
		board.start_move(BLACK);
		do {
			cout << board << endl;
			// запрашиваем неполный полуход и ходим
			board.move(bp->move(board));
			cout << "[жмакни ENTER]" << endl;
			getchar();
		}
		// проверяем, есть ли ещё неполные полуходы
		while (board.can_move(BLACK));
		// проверка на выигрыш
		if (res_flag = board.is_win()) return result(res_flag);
		
		// возврат
		cout << endl;
	} while(1);
}

// сообщаем о результатах
void GAME::result (int res) {
	cout << board << endl;
	switch(res) {
		// выиграли белые
		case ISWIN_WHITE:
			cout << "\n\n********** БЕЛЫЕ ВЫИГРАЛИ **********\n\n" << endl;
		break;
		// выиграли чёрные
		case ISWIN_BLACK:
			cout << "\n\n********** ЧЁРНЫЕ ВЫИГРАЛИ **********\n\n" << endl;
		break;
		// ничья
		case ISWIN_DRAW:
			cout << "\n\n***** НИЧЬЯ *****\n\n" << endl;
		break;
	}
}

