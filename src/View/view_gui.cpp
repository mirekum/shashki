#include <QtGui>
#include "View/view_gui.h"

/* methods of the GUI view class */

// create game instance (H-H, H-A, H-N, etc)
GAME* VIEW_GUI::createGame() {
	// TODO: ask user about which game he wants to play
	return new GAME(HUMAN, AI);
}

// exec game process
int VIEW_GUI::gameProcess() {
	GAMESTATE res_flag;
	VIEW_GUI::Input gameInput;
	board = game->getBoard();
	
	QApplication app(argc, argv);
	
	// main window of application
	window = new QWidget();
	window->setWindowFlags(Qt::Window);
	window->setWindowTitle("Draughts (shashki)");
	window->show();
	
	// board widget
	boardwrap = new QFrame(window);
	boardwrap->move(10, 10);
	boardwrap->resize(396, 396);
	boardwrap->setFrameStyle(QFrame::Box | QFrame::Plain);
	boardwrap->setLineWidth(1);
	boardwrap->show();
	
	// figures on the board
	for (int i = 0; i <= board.size; i++) {
		for (int j = 0; j <= board.size; j++) {
			if (!i) {
				figures[i][j] = new QLabel("|", boardwrap);
			} else if (!j) {
				figures[i][j] = new QLabel("-", boardwrap);
			} else switch (board.gcell(i - 1, j - 1)) {
				case WHITE_PAWN:
					figures[i][j] = new QLabel("x", boardwrap);
				break;
				case BLACK_PAWN:
					figures[i][j] = new QLabel("o", boardwrap);
				break;
				case WHITE_KING:
					figures[i][j] = new QLabel("W", boardwrap);
				break;
				case BLACK_KING:
					figures[i][j] = new QLabel("B", boardwrap);
				break;
				default:
					figures[i][j] = new QLabel("", boardwrap);
				break;
			}
			figures[i][j]->move(i * 44, j * 44);
			figures[i][j]->resize(44, 44);
			figures[i][j]->setFrameStyle(QFrame::Box | QFrame::Plain);
			figures[i][j]->setLineWidth(1);
			figures[i][j]->show();
		}
	}
	
	/*game->start(gameInput);
	
	do {
		// white moves
		game->startMove(WHITE);
		do {
			game->execMove();
		}
		while (game->canMove());
		if (res_flag = game->checkResult()) goto result;
		
		// black moves
		game->startMove(BLACK);
		do {
			game->execMove();
		}
		while (game->canMove());
		if (res_flag = game->checkResult()) goto result;
		
	} while(1);
	
	result:
	game->finish();
	
	gameResults(res_flag);*/
	
	return app.exec();
}

// show results of the game
void VIEW_GUI::gameResults(GAMESTATE res_flag) {
	// TODO: show game's results
	switch(res_flag) {
		case END_WHITE:
			// white has won
		break;
		case END_BLACK:
			// black has won
		break;
		case END_DRAW:
			// draw
		break;
	}
}

// get move from human player
MOVE VIEW_GUI::Input::humanGetmove(BOARD board) {
	MOVE result;
	
	do {
		// ask user which cell does he want to go
		if (board.move(result)) break;
		//else // error, message about repeating the move
	} while (1);
	
	return result;
}

