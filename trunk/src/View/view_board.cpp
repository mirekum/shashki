#include "View/view_board.h"

View_Board::View_Board(View_Main &main_ui) {
	window = main_ui.getWindow();
}

// view initialization
void View_Board::init(Game *_game) {
	// model
	game = _game;
	board = &game->getBoard();
	
	// signal to update model
	connect(game, SIGNAL(updateBoard()), SLOT(updateBoard()));
	
	// draw board wrapper
	boardwrap = new QFrame(window);
	boardwrap->setGeometry(10, 10, 396, 396);
	boardwrap->setFrameStyle(QFrame::Box | QFrame::Plain);
	boardwrap->setLineWidth(3);
	boardwrap->show();
	// draw figures wrapper
	figures = new QFrame(boardwrap);
	figures->setGeometry(44, 44, 352, 352);
	figures->show();
	// draw figures
	drawCanvas();
	drawFigures();
}

void View_Board::drawCanvas() {
	QPainter paint;
	paint(boardwrap);
	paint.drawRect(QRect(10, 10, 44, 44));
	paint.end();
	qDebug() << "View_Board::drawCanvas";
}

void View_Board::drawFigures() {
	qDebug() << "View_Board::drawFigures";
}

// request move from human
void View_Board::execMove(BOARD board) {
	qDebug() << "View_Board::execMove";
	sleep(10);
	emit moveExecuted();
}

// updated model
void View_Board::updateBoard() {
	// draw figures
	drawCanvas();
	drawFigures();
}

