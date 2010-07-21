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
	canvas = new Board_Widget(window);
	canvas->init(game);
	canvas->setGeometry(10, 10, 396, 396);
	canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
	canvas->setLineWidth(3);
	canvas->show();
}

void Board_Widget::init(Game *_game) {
	game = _game;
	board = &game->getBoard();
}

void Board_Widget::paintEvent() {
	QPainter paint(this);
	paint.setBrush(QBrush(Qt::blue));
	paint.drawRect(QRect(10, 10, 44, 44));
	qDebug() << "Board_Widget::paintEvent";
}

// request move from human
void View_Board::execMove(BOARD board) {
	qDebug() << "View_Board::execMove";
	sleep(10);
	emit moveExecuted();
}

// updated model
void View_Board::updateBoard() {
	canvas->update();
}

