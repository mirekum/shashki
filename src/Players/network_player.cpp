#include "Players/network_player.h"
#include <QtNetwork>

static const int PORT_CONNECT = 27015;
static const int PORT_CONNECT_ANNOUNCE = 47475;

enum ERROR{
	HOST_NOT_FOUND_ERROR = 1, 
	CONNECTION_REFUSED_ERROR = 2,
	REMOTE_HOST_CLOSED_ERROR = 3,
	CREATE_SERVER_ERROR = 4,
	};


/* methods of class of the network player */
Network_Player::Network_Player() {
	TcpSocket = NULL;
	udpSocketrelise = new QUdpSocket(this);
	udpSocketrelise->bind(PORT_CONNECT_ANNOUNCE);
	connect(udpSocketrelise, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
	gameInProgress=false;
	tcpServer=NULL;
	NextBlockSize=0;
	selfIp="127.0.0.1";
	curMove=true;
}
void Network_Player::startGame() {
	gameInProgress=true;	
	connectComplete();
}
int Network_Player::createServer() {
	tcpServer = new QTcpServer(this); 
	QHostAddress adrr (selfIp);
	if (!tcpServer->listen(adrr/*(selfIp)*/, PORT_CONNECT)) {
		tcpServer->close();
		tcpServer=NULL;
		return CREATE_SERVER_ERROR;
	}
	connect(tcpServer, SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
	return 0;
};
void Network_Player::sendAnnouncement() {
	QUdpSocket udpSocketReturn;
	QString Return;
	if (color == BLACK) {
		Return =Return+"B";
	}
	else if (color == WHITE) {
		Return =Return+"W";
	}
	Return =Return+"Y"+selfIp;
	QByteArray datagramReturn = Return.toStdString().c_str() ;
	udpSocketReturn.writeDatagram(datagramReturn.data(),datagramReturn.size(),QHostAddress::Broadcast,PORT_CONNECT_ANNOUNCE);
	ServerList.clear();
}
void Network_Player::processPendingDatagrams() {
	QUdpSocket* udpSocket = (QUdpSocket*)sender();
	QHostAddress IPtempDefine("127.0.0.1");
	while (udpSocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());
		char* tmp=datagram.data();
		const char* colorin = & tmp[0];
		const char* answer = & tmp[1];
		const char*sendIp = & tmp[2];
		qDebug()<<colorin<<"INPUT DATA";
		QHostAddress hostaddress;
		if (((colorin[0] == 'B')&&(color == WHITE))||((colorin[0] == 'W')&&(color == BLACK))) {
			hostaddress.setAddress(sendIp);
			if ((hostaddress != QHostAddress:: Null)&&(selfIp != sendIp)
							&&(hostaddress != IPtempDefine)&&(answer[0] == 'Y')) {
				QUdpSocket udpSocketReturn;
				QString Return;
				if(color==BLACK){
					Return =Return+"B";
				}
				else if(color==WHITE){
					Return =Return+"W";
				}
				Return =Return+"N"+selfIp;
				QByteArray datagramReturn = Return.toStdString().c_str() ;
				udpSocketReturn.writeDatagram(datagramReturn.data(),datagramReturn.size(),QHostAddress::Broadcast,PORT_CONNECT_ANNOUNCE);
			}
			if ((hostaddress != QHostAddress:: Null)&&(!ServerList.contains(sendIp)
							&&(selfIp != sendIp))&&(hostaddress != IPtempDefine)) {
			ServerList<<sendIp;
			searchUpdate();
			qDebug()<<"ADD IN LIST SERVER"<<sendIp;	
			}	
		}
	}
}

QList<QString> Network_Player::getEnemyIpAddresses() {
	return ServerList;
}

void Network_Player::slotNewConnection() {
	if (gameInProgress == false) {
		TcpSocket = tcpServer->nextPendingConnection();
		connect(TcpSocket, SIGNAL(disconnected()), TcpSocket, SLOT(deleteLater()));
		connect(TcpSocket, SIGNAL(readyRead()),SLOT(slotReadyRead()));
		slotConnected();
		QByteArray  arrBlock;
		QDataStream out(&arrBlock, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);
		int i=100;
		out << quint16(0)<<true;
		qDebug()<<true;
		out.device()->seek(0);
		out << quint16(arrBlock.size() - sizeof(quint16));
		TcpSocket->write(arrBlock);
		connect(TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));
		startGame();

	}
	else{
		QTcpSocket*temp_TcpSocket = tcpServer->nextPendingConnection();
		QByteArray  arrBlock;
		QDataStream out(&arrBlock, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);
		out << quint16(0)<<false;
		out.device()->seek(0);
		out << quint16(arrBlock.size() - sizeof(quint16));
		temp_TcpSocket->write(arrBlock);
		temp_TcpSocket->close();
		delete temp_TcpSocket;
	}
}	
void Network_Player::slotError(QAbstractSocket::SocketError err) {
	ERROR er;	
	if ( err == QAbstractSocket::HostNotFoundError) {
		er=HOST_NOT_FOUND_ERROR;
		TcpSocket->close();
		error(er);
		qDebug()<<"HostNotFoundError";
	}	
	else if (err == QAbstractSocket::ConnectionRefusedError) {
		er=CONNECTION_REFUSED_ERROR;
		TcpSocket->close();
		error(er);
		qDebug()<<"ConnectionRefusedError";
	}
	else if (err == QAbstractSocket::RemoteHostClosedError) {
		er=REMOTE_HOST_CLOSED_ERROR;
		TcpSocket->close();
		error(er);
		qDebug()<<"RemoteHostClosedError";
	}
}
void Network_Player::createClient( QString Host) {
	if (TcpSocket!=NULL) {
		TcpSocket->close();
		delete TcpSocket;
		TcpSocket=NULL;
	};
	qDebug()<<"conect too hast:" <<Host;
	TcpSocket = new QTcpSocket(this);
	NextBlockSize=0;
	TcpSocket->connectToHost(Host, PORT_CONNECT);
	connect(TcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(TcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));

}
void Network_Player::slotConnected() {
	qDebug()<<"Received the connected() signal";
}

void Network_Player::slotReadyRead() {
	if (curMove) {
		if (gameInProgress == false) {
			qDebug()<<"vait read signal";
			QDataStream in(TcpSocket);
			in.setVersion(QDataStream::Qt_4_0);
				for (;;) {
					if (!NextBlockSize) {
						if (TcpSocket->bytesAvailable() < sizeof(quint16)) {
							break;
						}
						in >> NextBlockSize;
					}
					if (TcpSocket->bytesAvailable() < NextBlockSize) {
						qDebug()<<"reed signal";
						break;
					}
					in >>gameInProgress;
					qDebug()<<gameInProgress<<"-signal";
					if (gameInProgress == true) {
						qDebug()<<gameInProgress<<"signal";
						startGame();
					}
					else{
						TcpSocket->close();
					}
					NextBlockSize = 0;
				}
		}
		else{	
			qDebug()<<"vait read";
			QDataStream in(TcpSocket);
			in.setVersion(QDataStream::Qt_4_0);
				for (;;) {
					if (!NextBlockSize) {
						if (TcpSocket->bytesAvailable() < sizeof(quint16)) {
							qDebug()<<"read lern";
							break;
						}
						in >> NextBlockSize;
						qDebug()<<NextBlockSize;
					}
					if (TcpSocket->bytesAvailable() < NextBlockSize) {
						qDebug()<<"reed";
						break;
					}
					result.from.x=0;
					result.from.y=0;
					result.to.x=0;
					result.to.y=0;
					in >>result.from.x>>result.from.y>>result.to.x>>result.to.y;
					curMove=false;
					qDebug()<<result.from.x;
					qDebug()<<result.from.y;
					qDebug()<<result.to.x;
					qDebug()<<result.to.y;
					NextBlockSize = 0;
					return;
				}
		}
	}
}
QList<QString> Network_Player::getSelfIpAddresses() { 
	QList<QString> listInterfase;
	QString temp;
	QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
	QHostAddress IPtempDefine("127.0.0.1");
	foreach (QHostAddress IPtemp,QNetworkInterface::allAddresses ()){
		temp=IPtemp.toString();
		if ((temp.count(":")==0)&&(IPtemp!=IPtempDefine)) {
			listInterfase<<temp;
		}
	}
	return listInterfase;
}
void Network_Player::giveLastMoves(MOVE lastMove[maxFiguresNumber]) {
	int i=0;
	while (i<maxFiguresNumber) {
		if ((lastMove[i].from.x!=0)||(lastMove[i].from.y!=0)||(lastMove[i].to.x!=0)||(lastMove[i].to.y!=0)) {
			QByteArray  arrBlock;
			QDataStream out(&arrBlock, QIODevice::WriteOnly);
			out.setVersion(QDataStream::Qt_4_0);
			out << quint16(0) <<lastMove[i].from.x << lastMove[i].from.y << lastMove[i].to.x <<lastMove[i].to.y;
			out.device()->seek(0);
			out << quint16(arrBlock.size() - sizeof(quint16));
			qDebug()<<quint16(arrBlock.size() - sizeof(quint16));
			TcpSocket->write(arrBlock);
			qDebug()<<"out";
			qDebug()<<lastMove[i].from.x<<lastMove[i].from.y<<lastMove[i].to.x<<lastMove[i].to.y;
			lastMove[i].from.x=0;
			lastMove[i].from.y=0;
			lastMove[i].to.x=0;
			lastMove[i].to.y=0;
		}
		i++;
	}
}
void Network_Player::execMove(BOARD board) {
	sleep(1);	
	slotReadyRead();
	do {
		if (curMove == false) {
			break;
		}
		usleep(300);
	} while (true);
	moveExecuted();
	curMove=true;
}
MOVE Network_Player::getMove() {
	return result;
}
bool Network_Player::isIp(QString Ip) {
	QHostAddress hostaddress;
	hostaddress.setAddress(Ip);
	if (hostaddress != QHostAddress::Null) return 0;
	return 1;
}
bool Network_Player::setSelfIp(QString Ip){
	QHostAddress hostaddress;
	hostaddress.setAddress(Ip);
	if (hostaddress != QHostAddress:: Null) {
		selfIp=Ip;
		return true;
	}
	return false;
}
Network_Player::~Network_Player() {
	qDebug()<<"delited";
}
