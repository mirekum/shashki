#include "Model/game.h"
#include "Players/human.h"
#include "Players/ai.h"
#include "Players/network.h"

/* methods of the class for playing draughts */

GAME::GAME(PLAYER_TYPE w, PLAYER_TYPE b) {
	wp = createPlayer(w);
	bp = createPlayer(b);
	plr = NULL;
	gameInput = NULL;
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
	delete plr;
}

PLAYER* GAME::createPlayer(PLAYER_TYPE _type) {
	switch (_type) {
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

void GAME::start(VIEW_INPUT &_gameInput) {
	gameInput = &_gameInput;
}

void GAME::startMove(COLOR color) {
	moveNum = 0;
	switch (color) {
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
	board.startMove(color);
	plr->giveLastMoves(lastMove);
}

void GAME::execMove() {
	if (plr == NULL) exit(1);
	switch (plr->getType()) {
		case HUMAN:
			lastMove[moveNum] = gameInput->humanGetmove(board);
		break;
		default:
			lastMove[moveNum] = plr->getMove(board);
		break;
	}
	board.move(lastMove[moveNum++]);
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

