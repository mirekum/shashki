#include "View/view_info.h"

View_Info::View_Info(View_Main &main_ui) {
	window = main_ui.getWindow();
}

// view initialization
void View_Info::init(Game *_game) {
	// model
	game = _game;
	// draw info wrapper
	infowrap = new QFrame(window);
	infowrap->setGeometry(480, 10, 300, 250);
	infowrap->setFrameStyle(QFrame::Box | QFrame::Plain);
	infowrap->setLineWidth(1);
	infowrap->show();
}

// view hiding
void View_Info::hide() {
	infowrap->hide();
}

