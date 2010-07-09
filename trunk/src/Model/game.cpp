#include <iostream>
#include <cstdio>
#include "Model/board.h"
#include "Players/player.h"
#include "Players/human.h"
#include "Players/ai.h"
#include "Players/network.h"
#include "Model/game.h"

/* methods of the class for playing draughts */

GAME::GAME(GAMER w, GAMER b) {
	move_num = 0;
	wp = createPlayer(w);
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

GAME::~GAME() {
	delete wp;
	delete bp;
}

PLAYER* GAME::createPlayer(GAMER plr) {
	switch (plr) {
		case HUMAN:
			return new HUMAN_PLAYER();
		case AI:
			return new AI_PLAYER();
		case NETWORK:
			return new NETWORK_PLAYER();
		default:
			exit(1);
	}
	return NULL;
}

void GAME::execMove(PLAYER *plr, COLOR type) {
	move_num++;
	board.startMove(type);
	int i=0;
	plr->giveLastMoves(lastMove);
	// get moves
	do {
		std::cout << board << std::endl;
		std::cout << "Move #" << move_num << std::endl;
		// request partial half-move and exec it
		lastMove[i] = plr->getMove(board);
		board.move(lastMove[i]);
		std::cout << "[жмакни ENTER]" << std::endl;
	//	getchar();
		i++;
		
	}
	// check if there are partial half-moves
	while (board.canMove());
	
}

void GAME::process () {
	GAMESTATE res_flag;
	do {
		std::cout << "*** ХОД БЕЛЫХ ***" << std::endl;
		execMove(wp, WHITE);
		if (res_flag = board.isWin()) goto res;
		
		std::cout << "*** ХОД ЧЁРНЫХ ***" << std::endl;
		execMove(bp, BLACK);
		if (res_flag = board.isWin()) goto res;
		
		std::cout << std::endl;
	} while(1);
	
	res:
	wp->giveLastMoves(lastMove);
	bp->giveLastMoves(lastMove);
	return result(res_flag);
}

void GAME::result (GAMESTATE res) {
	std::cout << board << std::endl;
	switch(res) {
		case END_WHITE:
			std::cout << "\n\n********** БЕЛЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		case END_BLACK:
			std::cout << "\n\n********** ЧЁРНЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		case END_DRAW:
			std::cout << "\n\n***** НИЧЬЯ *****\n\n" << std::endl;
		break;
	}
}

