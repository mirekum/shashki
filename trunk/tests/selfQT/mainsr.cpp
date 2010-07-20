#include <QtGui/QApplication>
#include "network_player.h"
#include <stdio.h>
#include <QtNetwork>
	#include <iostream>
#include <QtGui>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
 
	Network_Player serv;

	serv.setSelfIp("127.0.0.0");
	serv.setColor(BLACK);
	if(serv.createServer()==0){

	MOVE lastMove[Player::maxFiguresNumber];
	lastMove[4].from.x=1;
	std::cout << "inter" << std::endl;
	int f;
	std::cin >>f;
	if(f==0)
	serv.giveLastMoves(lastMove);
	printf("STOP");

	}

//	QList<QString> list;
//	list=serv.getActivInterfase();
//	list=serv.getList();
//	foreach (QString one, list)
///	printf((one+"\n").toStdString().c_str());
	QLabel lbl("Hello, World !");
	lbl.show();
	return app.exec();




}
