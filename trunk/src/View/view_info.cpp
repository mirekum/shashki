#include "View/view_info.h"

View_Info::View_Info(View_Main &main_ui) {
	window = main_ui.getWindow();
}

// view initialization
void View_Info::init(Game *_game) {
	// model
	game = _game;
	// draw info wrapper
	list_history_widget = new QListWidget(window);
	list_history_widget->setGeometry(480, 40, 300, 370);
	list_history_widget->show();
	label_history = new QLabel(window);
	label_history->setGeometry(480, 10, 300, 30);
	label_history->setFrameStyle(QFrame::Box | QFrame::Plain);
	label_history->setText("HISTORY:");
	label_history->show();
		// signal to update model
	connect(list_history_widget, SIGNAL(itemDoubleClicked (QListWidgetItem * )), this, SLOT(rollHistory(QListWidgetItem * )));
	connect(game, SIGNAL(updateBoard()), SLOT(updateHistory()));
	
}
void View_Info::updateHistory() {
	qDebug()<<"Updait hist info";
	QList<History> history;
	history = game->getHistory();
	list_history_widget->clear();
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
		tmpNum.setNum(tmp.move.from.y+1);
		tmpStr = tmpStr+tmpNum+"--->";
		tmpChar = tmpChar+tmp.move.to.x;
		tmpStr = tmpStr+tmpChar;
		tmpNum.setNum(tmp.move.to.y+1);
		tmpStr = tmpStr+tmpNum;
		list_history_widget->addItem(tmpStr);
	}
}
void View_Info::rollHistory(QListWidgetItem * state ) {
	//int* state = & list_history->currentRow;
	int st = list_history_widget->row(state);
	qDebug()<<"go"<<st<<"in histry";
	game->goByHistoryState(st);
}
// view hiding
void View_Info::hide() {
}

