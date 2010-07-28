#include "View/view_finishgame.h"

View_FinishGame::View_FinishGame(View_Main &main_ui) {
	window = main_ui.getWindow();
}

void View_FinishGame::show(GAMESTATE res_flag) {
	// draw info wrapper
	box = new QLabel(window);
	box->setGeometry(480, 10, 300, 200);
	box->setFrameStyle(QFrame::Box | QFrame::Plain);
	box->setLineWidth(3);
	switch (res_flag) {
		case END_WHITE:
			box->setText("White has won! (1:0)");
		break;
		case END_BLACK:
			box->setText("Black has won! (0:1)");
		break;
		case END_DRAW:
			box->setText("Draw! (0:0)");
		break;
	}
	box->show();
}

