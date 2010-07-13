#include "View/view_main.h"

View_Main::View_Main() {
	window = new QWidget();
}

View_Main::~View_Main() {
	delete window;
}

// show main app window
void View_Main::show() {
	window->setWindowFlags(Qt::Window);
	window->setWindowTitle("Draughts (shashki)");
	window->show();
}

