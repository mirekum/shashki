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
	canvas->setGeometry(10, 10, 400, 400);
	canvas->show();
}

void Board_Widget::init(Game *_game) {
	game = _game;
	board = &game->getBoard();
}

void Board_Widget::paintEvent(QPaintEvent *event) {
	QPainter paint(this);
	// draw coordinate lines
	paint.setPen(QPen(Qt::white, 1));
	paint.setBrush(QBrush(QColor(0x55, 0x55, 0x55)));
	for (int i = 1; i <= 8; i++) {
		paint.drawRect(QRect(i * 44, 0, 44, 44));
	}
	for (int j = 1; j <= 8; j++) {
		paint.drawRect(QRect(0, j * 44, 44, 44));
	}
	// draw cells
	paint.setPen(QPen(Qt::white, 1));
	for (int i = 0, x0 = 44; i < 8; i++) {
		for (int j = 0, y0 = 44; j < 8; j++) {
			paint.setBrush(QBrush(( (i + j) % 2 ? QColor(0x77, 0xdd, 0x77) : QColor(0xba, 0xdb, 0xad) )));
			paint.drawRect(QRect(x0 + i * 44, y0 + j * 44, 44, 44));
		}
	}
	// draw figures
	for (int i = 0, x0 = 44; i < 8; i++) {
		for (int j = 0, y0 = 44; j < 8; j++) {
			FIGURE f = board->gcell(i, j);
			if (IS_EMPTY(f)) continue;
			paint.setBrush(QBrush(IS_WHITE(f) ? Qt::white : Qt::black));
			paint.setPen(QPen(IS_WHITE(f) ? Qt::black : Qt::white, 1));
			paint.drawEllipse(QRect(x0 + i * 44 + 4, y0 + j * 44 + 4, 36, 36));
			if (IS_KNG(f)) {
				paint.setPen(QPen(IS_WHITE(f) ? Qt::black : Qt::white, 3));
				paint.drawEllipse(QRect(x0 + i * 44 + 10, y0 + j * 44 + 10, 24, 24));
			}
		}
	}
}

// request move from human
void View_Board::execMove(BOARD board) {
	qDebug() << "View_Board::execMove";
	
	emit moveExecuted();
}

// updated model
void View_Board::updateBoard() {
	canvas->update();
}

