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
	infowrap->setGeometry(430, 10, 350, 250);
	infowrap->setFrameStyle(QFrame::Box | QFrame::Plain);
	infowrap->setLineWidth(3);
	infowrap->show();
	
}

