#include <QtGui/QApplication>
#include "network_player.h"
#include <stdio.h>
#include <QtNetwork>
	#include <iostream>
#include <QtGui>
int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

   
	
	printf("ehhe");
	std::string inetServAdr="10.51.3.62";
	Network_Player clie;
	BOARD bord;
	clie.createClient("127.0.0.0");
	MOVE result;
	clie.setColor(WHITE);
	clie.relise();
	QLabel lbl("Hello, World !");
 	lbl.show();
 	return app.exec();
}
