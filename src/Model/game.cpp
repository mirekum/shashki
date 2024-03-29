#include "Model/game.h"

Game::Game() {
	//qDebug() << "Game::Game()";
	
	wp = NULL;
	bp = NULL;
	thread = NULL;
}

Game::~Game() {
	//qDebug() << "Game::~Game()";
}

void Game::init(Player *_wp, Player *_bp) {
	//qDebug() << "Game::init(Player *_wp, Player *_bp)";
	
	if (!_wp || !_bp) exit(1);
	
	// players
	wp = _wp;
	bp = _bp;
}

void Game::start() {
	//qDebug() << "Game::start()";
	
	setCurrentPlayer(WHITE);
	
	// first move
	move();
}

void Game::setCurrentPlayer(COLOR color) {
	current = color == WHITE ? wp : bp;
	current->setColor(color);
	board.startMove(color);
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
	//qDebug() << "Game::finish(GAMESTATE res_flag)";
	
	emit finishGame(res_flag);
}

void Game::recieveMove() {
	GAMESTATE res_flag;
	//sleep(1);
	MOVE mv = current->getMove();
	delete thread;
	// check move
	if (!board.move(mv)) {
		// wrong move - request move again
		//qDebug() << "(!) wrong move: " << mv.from.x+1 << "," << mv.from.y+1 << " >> " << mv.to.x+1 << "," << mv.to.y+1;
		move();
		return;
	}
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
	}
	// next move, please!
	move();
}

