#include "Model/game.h"

Game::Game() {
	wp = NULL;
	bp = NULL;
	moveNum = 0;
	globalMoveNum = 2;

}

void Game::init(Player *_wp, Player *_bp) {
	if (!_wp || !_bp) exit(1);
	// players
	wp = _wp;
	bp = _bp;
}

void Game::start() {
	qDebug()<<"start";
	setCurrentPlayer(WHITE);
	// first move
	move();
}

void Game::setCurrentPlayer(COLOR color) {
	qDebug()<<"setCurrentPlayer";
	current = color == WHITE ? wp : bp;
	current->setColor(color);
	current->giveLastMoves(lastMove);
	board.startMove(color);
	connect(current, SIGNAL(moveExecuted()), this, SLOT(recieveMove()));
	moveNum = 0;
	//emit currentPlayer(color);
	qDebug()<<"emit currentPlayer(color);";
}

void Game::move() {
	// request move from current player

	emit updateBoard();
	qDebug()<<"move start";
	current->execMove(board);
	qDebug()<<"move end";
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
void Game::goByHistoryState(int state) {
	disconnect(current, SIGNAL(moveExecuted()), this, SLOT(recieveMove()));
	board.reset();
	int ch = 0;
	globalMoveNum = 2;
	board.startMove(WHITE);
	QList<History> tmp_history;
	COLOR last = WHITE;
	foreach (History tmp, history) {
		if (ch == state){
			if (last == tmp.color) {
				qDebug()<<"last == tmp.color";
				setCurrentPlayer(tmp.color);
			}
			else {
				qDebug()<<"last != tmp.color";
				
			}
			break;
		}
		tmp_history<<tmp;
		board.move(tmp.move);
		ch++;
		if (!board.canMove()) {
			// change current player
			board.startMove(tmp.color == WHITE ? BLACK : WHITE);
			globalMoveNum++;
			last = tmp.color == WHITE ? BLACK : WHITE;
		}

	}
	history = tmp_history;
	qDebug()<<"emit updateBoard();";
	emit updateBoard();
	qDebug()<<"------------------";
	move();	
}
void Game::recieveMove() {
	GAMESTATE res_flag;
	MOVE mv = current->getMove();
	if (!board.move(mv)) {
		// wrong move - request move again
		qDebug()<<"error move() ";
		move();
		return;
	}
	qDebug()<<"in histori";
	History mvh;
	mvh.move = mv;
	mvh.moveNum=globalMoveNum;
	mvh.color = current->getColor();
	history<<mvh;
	lastMove[moveNum++] = mv;
	qDebug()<<"emit updateBoard();";
	emit updateBoard();
	qDebug()<<"------------------";
	// check finish
	if (res_flag = board.isWin()) {
		finish(res_flag);
		return;
	}
	// continue game
	if (!board.canMove()) {
		// change current player
		disconnect(current, SIGNAL(moveExecuted()), this, SLOT(recieveMove()));
		setCurrentPlayer(current->getColor() == WHITE ? BLACK : WHITE);
		globalMoveNum++;
	}
	move();
}

