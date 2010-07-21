#include <QtGui/QApplication>
#include "network_player.h"
#include <stdio.h>
#include <QtNetwork>
	#include <iostream>
#include <QtGui>
int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

   
	
	qDebug()<<"ehhe";
	std::string inetServAdr="10.51.3.62";
	Network_Player clie;
	BOARD bord;
	clie.createClient("10.14.56.142");
	MOVE result;
	clie.setColor(WHITE);
	clie.relise();
	QLabel lbl("Hello, World !");
 	lbl.show();
 	return app.exec();
}
