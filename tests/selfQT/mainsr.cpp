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
	int f;
//	std::cin >>f;
	serv.setSelfIp("10.14.56.142");
	serv.setColor(BLACK);
	if(serv.createServer()==0){

//	MOVE lastMove[Player::maxFiguresNumber];
//	lastMove[4].from.x=1;
//	std::cout << "inter" << std::endl;
//	std::cin >>f;
//	if(f==0)
//	serv.giveLastMoves(lastMove);
	qDebug()<<"STOP";

	}

	QList<QString> list;
	list=serv.getActivInterfase();
//	list=serv.getList();
	foreach (QString one, list)
	qDebug()<<one;
	QLabel lbl("Hello, World !");
	lbl.show();
	return app.exec();




}
