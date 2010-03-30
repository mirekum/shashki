#include <iostream>
#include "board.h"
#include "player.h"
#include "human.h"
#include "ai.h"
#include "game.h"

/* methods of the class for playing draughts */

// class constructor
GAME::GAME (PGAMER w, PGAMER b) {
	// white player creating
	wp = createPlayer(w);
	// black player creating
	bp = createPlayer(b);
	// start the game process
	if (wp != NULL && bp != NULL) {
		wp->setType(PWHITE);
		bp->setType(PBLACK);
		process();
	} else {
		std::cout << "Error: undefined type of player(s)!" << std::endl;
	}
	// number of moves
	int move_num = 0;
}

// class destructor
GAME::~GAME() {
	delete wp;
	delete bp;
}

// creates player
PLAYER* GAME::createPlayer(PGAMER plr) {
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

// player move
void GAME::exec_move(PLAYER *plr, PCOLOR type) {
	move_num++;
	board.start_move(type);
	// get moves
	do {
		std::cout << board << std::endl;
		std::cout << "Move #" << move_num << std::endl;
		// request partial half-move and exec it
		board.move(plr->get_move(board));
		std::cout << "[жмакни ENTER]" << std::endl;
		getchar();
	}
	// check if there are partial half-moves
	while (board.can_move());
}

// the game process
void GAME::process () {
	do {
		GAMESTATE res_flag; // флаг результата игры
		
		/* white moves */
		std::cout << "*** ХОД БЕЛЫХ ***" << std::endl;
		exec_move(wp, PWHITE);
		// check the winning
		if (res_flag = board.is_win()) return result(res_flag);
		
		/* black moves */
		std::cout << "*** ХОД ЧЁРНЫХ ***" << std::endl;
		exec_move(bp, PBLACK);
		// check the winning
		if (res_flag = board.is_win()) return result(res_flag);
		
		/* continue game */
		std::cout << std::endl;
	} while(1);
}

// reports the results
void GAME::result (GAMESTATE res) {
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

