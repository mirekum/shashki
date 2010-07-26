#include "View/view_main.h"

View_Main::View_Main() {
	// main window
	window = new QMainWindow();
	window->setWindowFlags(Qt::Window);
	window->setWindowTitle("Draughts (shashki)");
	// main menu
	QAction *newgame = new QAction("New game", window);
	connect(newgame, SIGNAL(triggered()), this, SLOT(menuNewgame()));
	QAction *exit = new QAction("Exit", window);
	connect(exit, SIGNAL(triggered()), this, SLOT(menuExit()));
	window->menuBar()->addAction(newgame);
	window->menuBar()->addAction(exit);
}

void View_Main::menuNewgame() {
	qDebug() << "View_Main::menuNewgame";
}

void View_Main::menuExit() {
	qDebug() << "View_Main::menuExit";
}

View_Main::~View_Main() {
	delete window;
}

// show main app window
void View_Main::show() {
	window->show();
}

