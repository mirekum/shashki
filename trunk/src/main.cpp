#include <QtGui>
#include "Model/game.h"
#include "View/view_board.h"
#include "View/view_startgame.h"

// entry point
int main(int argc, char** argv) {
	// create application
	QApplication app(argc, argv);
	// create model
	Game game;
	// create views
	View_Board board_ui;
	View_StartGame start_ui;
	// show first screen (for players creation)
	start_ui.showFirstScreen();
	// run application
	return app.exec();
}

