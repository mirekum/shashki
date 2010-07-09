#include <QApplication>
#include "View/view_gui.h"

/* methods of the GUI view class */

// create game instance (H-H, H-A, H-N, etc)
GAME* VIEW_GUI::createGame() {
	return new GAME(HUMAN, AI);
}

// exec game process
int VIEW_GUI::gameProcess() {
	//QApplication app(argc, argv);
	//return app.exec();
	return 0;
}

// show results of the game
void VIEW_GUI::gameResults(GAMESTATE res_flag) {
	
}

