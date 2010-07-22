#include "Model/game.h"

Game::Game() {
	wp = NULL;
	bp = NULL;
	thread = NULL;
	moveNum = 0;
}

void Game::init(Player *_wp, Player *_bp) {
	if (!_wp || !_bp) exit(1);
	// players
	wp = _wp;
	bp = _bp;
}

void Game::start() {
	setCurrentPlayer(WHITE);
	// first move
	move();
}

void Game::setCurrentPlayer(COLOR color) {
	current = color == WHITE ? wp : bp;
	current->setColor(color);
	current->giveLastMoves(lastMove);
	moveNum = 0;
	emit currentPlayer(color);
	board.startMove(color);
}

void Game::move() {
	// request move from current player
	thread = new getMoveThread;
	thread->setData(current, board);
	connect(thread, SIGNAL(finished()), SLOT(recieveMove()));
	thread->start(QThread::NormalPriority);
}

void getMoveThread::run() {
	current->execMove(*board);
}

void Game::finish(GAMESTATE res_flag) {
	qDebug() << "game finished:" << res_flag;
	wp->giveLastMoves(lastMove);
	bp->giveLastMoves(lastMove);
	emit finishGame(res_flag);
}

void Game::recieveMove() {
	GAMESTATE res_flag;
	MOVE mv = current->getMove();
	delete thread;
	// check move
	if (!board.move(mv)) {
		// wrong move - request move again
		move();
		return;
	}
	lastMove[moveNum++] = mv;
	emit updateBoard();
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

