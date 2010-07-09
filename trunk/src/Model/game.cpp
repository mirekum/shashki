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
	wp = createPlayer(w);
	bp = createPlayer(b);
	plr = NULL;
	// set player colors
	if (wp != NULL && bp != NULL) {
		wp->setType(WHITE);
		bp->setType(BLACK);
	} else {
		exit(1);
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

void GAME::startMove(COLOR type) {
	moveNum = 0;
	switch (type) {
		case WHITE:
			plr = wp;
		break;
		case BLACK:
			plr = bp;
		break;
		default:
			exit(1);
		break;
	}
	board.startMove(type);
	plr->giveLastMoves(lastMove);
}

void GAME::execMove() {
	if (plr == NULL) exit(1);
	board.move(lastMove[moveNum++] = plr->getMove(board));
}

bool GAME::canMove() {
	return board.canMove();
}

GAMESTATE GAME::checkResult() {
	return board.isWin();
}

BOARD& GAME::getBoard() {
	return board;
}

void GAME::finish() {
	wp->giveLastMoves(lastMove);
	bp->giveLastMoves(lastMove);
}

