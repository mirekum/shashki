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

Board_Widget::Board_Widget(QWidget * parent): QWidget(parent) {
	installEventFilter(this);
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

bool Board_Widget::eventFilter(QObject *target, QEvent *event) {         
	if (event->type() == QEvent::MouseButtonPress && read_flag) {
		QMouseEvent *mouseEvent = (QMouseEvent*)event;
		int x = (mouseEvent->pos().x() - 44) / 44, y = (mouseEvent->pos().y() - 44) / 44;
		if (ready == 0) {
			FIGURE f = board->gcell(x, y);
			result.from.x = x;
			result.from.y = y;
			if (0
				|| (currentColor == WHITE && !IS_WHITE(f))
				|| (currentColor == BLACK && !IS_BLACK(f))
			) return true;
			ready = 1;
			return true;
		}
		else if (ready == 1) {
			result.to.x = x;
			result.to.y = y;
			if (!board->canMove(result)) {
				ready = 0;
				return true;
			}
			ready = 2;
			return true;
		}
		return true;
	}
	return false;
};

void Board_Widget::startMove(COLOR color) {
	read_flag = true;
	ready = 0;
	currentColor = color;
}

MOVE Board_Widget::getMove() {
	read_flag = false;
	return result;
}

bool Board_Widget::isReady() {
	return ready == 2;
}

// request move from human
void View_Board::execMove(BOARD board) {
	canvas->startMove(color);
	do {
		if (canvas->isReady()) {
			result = canvas->getMove();
			break;
		}
		sleep(1);
	} while (true);
	emit moveExecuted();
}

// updated model
void View_Board::updateBoard() {
	canvas->update();
}

