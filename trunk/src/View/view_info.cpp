#include "View/view_info.h"

View_Info::View_Info(QWidget *parent):QFrame(parent) {
	qDebug() << "View_Info::View_Info(QWidget *parent):QFrame(parent)";
	
	window = parent;
}

// view initialization
void View_Info::init(Game *_game) {
	qDebug() << "View_Info::init(Game *_game) -> BEGIN";
	
	// model
	game = _game;
	
	// draw info wrapper
	setGeometry(480, 10, 300, 250);
	setFrameStyle(QFrame::Box | QFrame::Plain);
	setLineWidth(1);
	
	// show info widget
	show();
	
	qDebug() << "View_Info::init(Game *_game) -> END";
}

