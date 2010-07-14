#include <QtGui>
#include "Model/game.h"
#include "View/view_main.h"
#include "View/view_startgame.h"
#include "View/view_board.h"
#include "control.h"

// entry point
int main(int argc, char** argv) {
	// create QT application
	QApplication app(argc, argv);
	// create model
	Game game;
	// create main view
	View_Main main_ui;
	// create other views
	View_StartGame start_ui(main_ui);
	View_Board board_ui(main_ui);
	// show main app window
	main_ui.show();
	// show first screen
	start_ui.show();
	// run application
	return app.exec();
}

