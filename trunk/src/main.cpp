#include "control.h"

// entry point
int main(int argc, char** argv) {
	Control app(argc, argv);
	qDebug() << "Control app(argc, argv)";
	return app.exec();
}

