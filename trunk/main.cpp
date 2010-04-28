#include <QtGui>

// entry point
int main (int argc, char** argv) {
	QApplication shashki(argc, argv);
	
	QWidget gameWindow;
	QPalette gameWindowPal;
	gameWindowPal.setColor(gameWindow.backgroundRole(), Qt::white);
	gameWindow.setPalette(gameWindowPal);
	//gameWindow.setAutoFillBackground(true);
	gameWindow.resize(400, 400);
	gameWindow.show();
	
	return shashki.exec();
}

