#include <iostream>
#include "board.h"
#include "player.h"
#include "human.h"
#include "ai.h"
#include "game.h"

/* methods of the class for playing draughts */

// class constructor
GAME::GAME (int w, int b) {
	// white player creating
	wp = createPlayer(w);
	// black player creating
	bp = createPlayer(b);
	// start the game process
	if (wp != NULL && bp != NULL) {
		wp->setType(WHITE);
		bp->setType(BLACK);
		process();
	} else {
		std::cout << "Error: undefined type of player(s)!" << std::endl;
	}
}

// creates player
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

// the game process
void GAME::process () {
	do {
		int res_flag; // флаг результата игры
		
		/* white moves */
		std::cout << "*** ХОД БЕЛЫХ ***" << std::endl;
		board.start_move(WHITE);
		do {
			std::cout << board << std::endl;
			// request partial half-move and exec it
			board.move(wp->move(board));
			std::cout << "[жмакни ENTER]" << std::endl;
			getchar();
		}
		// check if there are partial half-moves
		while (board.can_move());
		// check the winning
		if (res_flag = board.is_win()) return result(res_flag);
		
		/* black moves */
		std::cout << "*** ХОД ЧЁРНЫХ ***" << std::endl;
		board.start_move(BLACK);
		do {
			std::cout << board << std::endl;
			// request partial half-move and exec it
			board.move(bp->move(board));
			std::cout << "[жмакни ENTER]" << std::endl;
			getchar();
		}
		// check if there are partial half-moves
		while (board.can_move());
		// check the winning
		if (res_flag = board.is_win()) return result(res_flag);
		
		/* the end */
		std::cout << std::endl;
	} while(1);
}

// reports the results
void GAME::result (int res) {
	std::cout << board << std::endl;
	switch(res) {
		// white won
		case ISWIN_WHITE:
			std::cout << "\n\n********** БЕЛЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		// black won
		case ISWIN_BLACK:
			std::cout << "\n\n********** ЧЁРНЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		// the draw
		case ISWIN_DRAW:
			std::cout << "\n\n***** НИЧЬЯ *****\n\n" << std::endl;
		break;
	}
}

