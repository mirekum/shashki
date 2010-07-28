#include "Model/game.h"

Game::Game() {
	wp = NULL;
	bp = NULL;
	thread = NULL;
	moveNum = 0;
	globalMoveNum = 1;
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
	board.startMove(color);
	moveNum = 0;
	emit currentPlayer(color);
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
	if (wp->type() == NETWORK) wp->giveLastMoves(lastMove);
	if (bp->type() == NETWORK) bp->giveLastMoves(lastMove);
	emit finishGame(res_flag);
}
QList<History> Game::getHistory() {
	return history;

}
int Game::getMove() {
	return moveNum;
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
	qDebug()<<"in histori";
	History mvh;
	mvh.move = mv;
	mvh.moveNum=globalMoveNum;
	if(current->getColor() == WHITE) {
		mvh.color = false;
	}
	else{
		mvh.color = true;
	}
	history<<mvh;
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
		setCurrentPlayer(current->getColor() == WHITE ? BLACK : WHITE);
		globalMoveNum++;
	}
	move();
}

