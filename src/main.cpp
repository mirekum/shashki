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
	// create views
	View_Main main_ui;
	View_StartGame start_ui(main_ui);
	View_Board board_ui(main_ui, game);
	// create application controller
	Control appCtrl(main_ui, game);
	// show main app window
	main_ui.show();
	// show first screen
	start_ui.show();
	// run application
	return app.exec();
}

