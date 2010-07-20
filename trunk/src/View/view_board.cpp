#include "View/view_board.h"

View_Board::View_Board(View_Main &main_ui) {
	window = main_ui.getWindow();
}

// view initialization
void View_Board::init(Game *_game) {
	// model
	game = _game;
	board = &game->getBoard();
	// draw board wrapper
	boardwrap = new QFrame(window);
	boardwrap->setGeometry(10, 10, 396, 396);
	boardwrap->setFrameStyle(QFrame::Box | QFrame::Plain);
	boardwrap->setLineWidth(3);
	boardwrap->show();
	// draw coordinate lines
	QLabel *coordO = new QLabel("", boardwrap);
	coordO->setGeometry(0, 0, 44, 44);
	coordO->setFrameStyle(QFrame::Box | QFrame::Plain);
	coordO->setLineWidth(1);
	coordO->show();
	QLabel *coordX[8];
	for (int i = 0, x; i < 8; i++) {
		x = i + 1;
		coordX[i] = new QLabel(boardwrap);
		coordX[i]->setGeometry(x * 44, 0, 44, 44);
		coordX[i]->setFrameStyle(QFrame::Box | QFrame::Plain);
		coordX[i]->setLineWidth(1);
		coordX[i]->show();
	}
	QLabel *coordY[8];
	for (int j = 0, y; j < 8; j++) {
		y = j + 1;
		coordY[j] = new QLabel(boardwrap);
		coordY[j]->setGeometry(0, y * 44, 44, 44);
		coordY[j]->setFrameStyle(QFrame::Box | QFrame::Plain);
		coordY[j]->setLineWidth(1);
		coordY[j]->show();
	}
	// draw figures wrapper
	figureswrap = new QFrame(boardwrap);
	figureswrap->setGeometry(44, 44, 352, 352);
	figureswrap->show();
	// draw figures
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			switch (board->gcell(i, j)) {
				case WHITE_PAWN:
					figures[i][j] = new QLabel("x", figureswrap);
				break;
				case BLACK_PAWN:
					figures[i][j] = new QLabel("o", figureswrap);
				break;
				case WHITE_KING:
					figures[i][j] = new QLabel("W", figureswrap);
				break;
				case BLACK_KING:
					figures[i][j] = new QLabel("B", figureswrap);
				break;
				default:
					figures[i][j] = new QLabel("", figureswrap);
				break;
			}
			figures[i][j]->setGeometry(i * 44, j * 44, 44, 44);
			figures[i][j]->setFrameStyle(QFrame::Box | QFrame::Plain);
			figures[i][j]->setLineWidth(1);
			figures[i][j]->show();
		}
	}
}

// get move from human
void View_Board::getMove(BOARD board) {
	
}

