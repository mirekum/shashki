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
	
	// signal to finish game
	connect(game, SIGNAL(finishGame(GAMESTATE)), SLOT(finishGame(GAMESTATE)));
	
	// draw board wrapper
	canvas = new Board_Widget(window);
	canvas->init(game);
	canvas->setGeometry(10, 10, 450, 400);
	canvas->show();
}

// view hiding
void View_Board::hide() {
	canvas->hide();
}

void Board_Widget::init(Game *_game) {
	game = _game;
	board = &game->getBoard();
	end_flag = END_NONE;
	connect(list_history, SIGNAL(itemDoubleClicked (QListWidgetItem * )), this, SLOT(rollHistory(QListWidgetItem * )));
}

void Board_Widget::status(GAMESTATE res_flag) {
	end_flag = res_flag;
}

Board_Widget::Board_Widget(QWidget * parent): QWidget(parent) {
	list_history = new QListWidget(parent);
	list_history->setGeometry(480, 10, 300, 400);
	list_history->show();
	installEventFilter(this);
}
void Board_Widget::rollHistory(QListWidgetItem * state ) {
	//int* state = & list_history->currentRow;
	int st = list_history->row(state);
	qDebug()<<"go"<<st<<"in histry";
	game->goByHistoryState(st);
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
	paint.drawText(60 + 44*0, 30, "A");
	paint.drawText(60 + 44*1, 30, "B");
	paint.drawText(60 + 44*2, 30, "C");
	paint.drawText(60 + 44*3, 30, "D");
	paint.drawText(60 + 44*4, 30, "E");
	paint.drawText(60 + 44*5, 30, "F");
	paint.drawText(60 + 44*6, 30, "G");
	paint.drawText(60 + 44*7, 30, "H");
	paint.drawText(15, 75 + 44*0, "1");
	paint.drawText(15, 75 + 44*1, "2");
	paint.drawText(15, 75 + 44*2, "3");
	paint.drawText(15, 75 + 44*3, "4");
	paint.drawText(15, 75 + 44*4, "5");
	paint.drawText(15, 75 + 44*5, "6");
	paint.drawText(15, 75 + 44*6, "7");
	paint.drawText(15, 75 + 44*7, "8");
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
	QList<History> history;
	history = game->getHistory();
	list_history->clear();
	char tmpChar = 'A';
	foreach (History tmp, history) {
		QString tmpStr;
		QString tmpNum;
		if (tmp.color == WHITE) {
			tmpNum.setNum(tmp.moveNum/2);
			tmpStr = tmpStr+tmpNum;
			tmpStr = tmpStr+"W  ";

		}
		else {
			tmpNum.setNum(tmp.moveNum/2);
			tmpStr = tmpStr+tmpNum;
			tmpStr = tmpStr+"B  ";

		}
		tmpChar = 'A';
		tmpStr = tmpStr;
		tmpChar = tmpChar+tmp.move.from.x;
		tmpStr = tmpStr+tmpChar;
		tmpChar = 'A';
		tmpNum.setNum(tmp.move.from.y);
		tmpStr = tmpStr+tmpNum+" ";
		tmpChar = tmpChar+tmp.move.to.x;
		tmpStr = tmpStr+tmpChar;
		tmpNum.setNum(tmp.move.to.y);
		tmpStr = tmpStr+tmpNum;
		list_history->addItem(tmpStr);
	}
	
	// move indication
	if (!end_flag) {
		paint.setBrush(QBrush(Qt::yellow));
		paint.setPen(QPen(Qt::white, 2));
		if (board->getCurrentColor() != WHITE) {
			paint.drawEllipse(QRect(410, 60, 20, 20));
		} else {
			paint.drawEllipse(QRect(410, 360, 20, 20));
		}
	}
}

bool Board_Widget::eventFilter(QObject *target, QEvent *event) {         
	if (event->type() == QEvent::MouseButtonPress && read_flag) {
		QMouseEvent *mouseEvent = (QMouseEvent*)event;
		int x = (mouseEvent->pos().x() - 44) / 44, y = (mouseEvent->pos().y() - 44) / 44;
		FIGURE f = board->gcell(x, y);
		if (ready == 0) {
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
				result.from.x = x;
				result.from.y = y;
				if (0
					|| (currentColor == WHITE && !IS_WHITE(f))
					|| (currentColor == BLACK && !IS_BLACK(f))
				) {
					ready = 0;
					return true;
				}
				ready = 1;
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
		usleep(300);
	} while (true);
	emit moveExecuted();
}

void View_Board::updateBoard() {
	canvas->update();
}

void View_Board::finishGame(GAMESTATE res_flag) {
	canvas->status(res_flag);
	canvas->update();
}
