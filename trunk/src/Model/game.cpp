#include "Model/game.h"
#include "Players/ai_player.h"
#include "Players/network_player.h"
#include "Players/bluetooth_player.h"
#include "View/view_board.h"

Game::Game() {
	wp = NULL;
	bp = NULL;
}

void Game::init(Player *_wp, Player *_bp) {
	if (!_wp || !_bp) exit(1);
	// players
	wp = _wp;
	bp = _bp;
	// signals to recieve move from players
	connect(wp, SIGNAL(getMoveResult(MOVE)), SLOT(recieveMove(MOVE)));
	connect(bp, SIGNAL(getMoveResult(MOVE)), SLOT(recieveMove(MOVE)));
}

void Game::start() {
	setCurrentPlayer(WHITE);
	// first move
	move();
}

void Game::setCurrentPlayer(COLOR color) {
	current = color == WHITE ? wp : bp;
	emit currentPlayer(color);
	board.startMove(color);
}

void Game::move() {
	// request move from current player
	// TODO: new thread
	current->getMove(board);
}

void Game::finish(GAMESTATE res_flag) {
	
}

void Game::recieveMove(MOVE mv) {
	GAMESTATE res_flag;
	// check move
	if (!board.move(mv)) {
		// wrong move - request move again
		move();
		return;
	}
	qDebug() << board;
	// check finish
	if (res_flag = board.isWin()) {
		finish(res_flag);
		return;
	}
	// continue game
	if (!board.canMove()) {
		// change current player
		setCurrentPlayer(current == wp ? BLACK : WHITE);
	}
	move();
}

BOARD& Game::getBoard() {
	return board;
}

