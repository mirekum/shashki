#include <iostream>
#include "board.h"
#include "player.h"
#include "human.h"
#include "ai.h"
#include "game.h"

/* методы класса "Игра в шашки" */

// конструктор класса
GAME::GAME (int w, int b) {
	// игрок белыми
	wp = createPlayer(w);
	// игрок чёрными
	bp = createPlayer(b);
	// игровой цикл
	if (wp != NULL && bp != NULL) {
		wp->setType(WHITE);
		bp->setType(BLACK);
		process();
	} else {
		std::cout << "Error: undefined type of player(s)!" << std::endl;
	}
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
		std::cout << "*** ХОД БЕЛЫХ ***" << std::endl;
		board.start_move(WHITE);
		do {
			std::cout << board << std::endl;
			// запрашиваем неполный полуход и ходим
			board.move(wp->move(board));
			std::cout << "[жмакни ENTER]" << std::endl;
			getchar();
		}
		// проверяем, есть ли ещё неполные полуходы
		while (board.can_move());
		// проверка на выигрыш
		if (res_flag = board.is_win()) return result(res_flag);
		
		// ход чёрных
		std::cout << "*** ХОД ЧЁРНЫХ ***" << std::endl;
		board.start_move(BLACK);
		do {
			std::cout << board << std::endl;
			// запрашиваем неполный полуход и ходим
			board.move(bp->move(board));
			std::cout << "[жмакни ENTER]" << std::endl;
			getchar();
		}
		// проверяем, есть ли ещё неполные полуходы
		while (board.can_move());
		// проверка на выигрыш
		if (res_flag = board.is_win()) return result(res_flag);
		
		// возврат
		std::cout << std::endl;
	} while(1);
}

// сообщаем о результатах
void GAME::result (int res) {
	std::cout << board << std::endl;
	switch(res) {
		// выиграли белые
		case ISWIN_WHITE:
			std::cout << "\n\n********** БЕЛЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		// выиграли чёрные
		case ISWIN_BLACK:
			std::cout << "\n\n********** ЧЁРНЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		// ничья
		case ISWIN_DRAW:
			std::cout << "\n\n***** НИЧЬЯ *****\n\n" << std::endl;
		break;
	}
}

