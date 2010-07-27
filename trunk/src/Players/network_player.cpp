#include "Players/network_player.h"
#include <QtNetwork>

static const int portConect=27015;
static const int portConectRelise=47475;

enum ERROR{
	HOST_NOT_FOUND_ERROR = 1, 
	CONNECTION_REFUSED_ERROR = 2,
	REMOTE_HOST_CLOSED_ERROR = 3,
	CREATE_SERVER_ERROR = 4,
	};


/* methods of class of the network player */
Network_Player::Network_Player(){
	TcpSocket = NULL;
	udpSocketrelise = new QUdpSocket(this);
	udpSocketrelise->bind(portConectRelise);
	connect(udpSocketrelise, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
	gameInProgres=false;
	tcpServer=NULL;
	NextBlockSize=0;
	selfIp="127.0.0.1";
	gethod=true;
}
void Network_Player::startgame(){
	gameInProgres=true;	
	conectComplite();
}
int Network_Player::createServer(){
	tcpServer = new QTcpServer(this); 
	QHostAddress adrr (selfIp);
	if (!tcpServer->listen(adrr/*(selfIp)*/, portConect)) {
		tcpServer->close();
		tcpServer=NULL;
		return CREATE_SERVER_ERROR;
	}
	connect(tcpServer, SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
	return 0;
};
void Network_Player::relise(){
	QUdpSocket udpSocketReturn;
	QString Return;
	if(color==BLACK){
		Return =Return+"B";
	}
	else if(color==WHITE){
		Return =Return+"W";
	}
	Return =Return+"Y"+selfIp;
	QByteArray datagramReturn = Return.toStdString().c_str() ;
	udpSocketReturn.writeDatagram(datagramReturn.data(),datagramReturn.size(),QHostAddress::Broadcast,portConectRelise);
	listServer.clear();
}
void Network_Player::processPendingDatagrams(){
	QUdpSocket* udpSocket = (QUdpSocket*)sender();
	QHostAddress IPtempDefine("127.0.0.1");
	while (udpSocket->hasPendingDatagrams()){
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());
		char* tmp=datagram.data();
		const char* colorin = & tmp[0];
		const char* answer = & tmp[1];
		const char*sendIp = & tmp[2];
		qDebug()<<colorin<<"INPUT DATA";
		QHostAddress hostaddress;
		if(((colorin[0]=='B')&&(color==WHITE))||((colorin[0]=='W')&&(color==BLACK))){
			hostaddress.setAddress(sendIp);
			if((hostaddress!=QHostAddress:: Null)&&(selfIp!=sendIp)&&(hostaddress!=IPtempDefine)&&(answer[0]=='Y')){
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
				udpSocketReturn.writeDatagram(datagramReturn.data(),datagramReturn.size(),QHostAddress::Broadcast,portConectRelise);
			}
			if((hostaddress!=QHostAddress:: Null)&&(!listServer.contains(sendIp)&&(selfIp!=sendIp))	&&(hostaddress!=IPtempDefine)){
			listServer<<sendIp;
			searchUpdate();
			qDebug()<<"ADD IN LIST SERVER"<<sendIp;	
			}	
		}
	}
}
QList<QString> Network_Player::getList(){
	return listServer;
}
void Network_Player::slotNewConnection(){
	if(gameInProgres==false){
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
		if(TcpSocket==NULL)qDebug()<<"NULL";
		TcpSocket->write(arrBlock);
		connect(TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));
		startgame();

	}
	else{
		QTcpSocket*temp_TcpSocket = tcpServer->nextPendingConnection();
		QByteArray  arrBlock;
		QDataStream out(&arrBlock, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);
		out << quint16(0)<<false;
		out.device()->seek(0);
		out << quint16(arrBlock.size() - sizeof(quint16));
		if(temp_TcpSocket==NULL)qDebug()<<"NULL";
		temp_TcpSocket->write(arrBlock);
		temp_TcpSocket->close();
		delete temp_TcpSocket;
	}
}	
void Network_Player::slotError(QAbstractSocket::SocketError err){
	ERROR er;	
	if(err==QAbstractSocket::HostNotFoundError){
		er=HOST_NOT_FOUND_ERROR;
		TcpSocket->close();
		error(er);
		qDebug()<<"HostNotFoundError";
	}	
	else if(err == QAbstractSocket::ConnectionRefusedError){
		er=CONNECTION_REFUSED_ERROR;
		TcpSocket->close();
		error(er);
		qDebug()<<"ConnectionRefusedError";
	}
	else if(err == QAbstractSocket::RemoteHostClosedError){
		er=REMOTE_HOST_CLOSED_ERROR;
		TcpSocket->close();
		error(er);
		qDebug()<<"RemoteHostClosedError";
	}
}
void Network_Player::createClient( QString strHost){
	if(TcpSocket!=NULL){
		TcpSocket->close();
		delete TcpSocket;
		TcpSocket=NULL;
	};
	qDebug()<<"conect tuu hast:" <<strHost;
	TcpSocket = new QTcpSocket(this);
	NextBlockSize=0;
	TcpSocket->connectToHost(strHost, portConect);
	connect(TcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(TcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));

}
void Network_Player::slotConnected(){
	qDebug()<<"Received the connected() signal";
}

void Network_Player::slotReadyRead(){
	if(gethod){
		if(gameInProgres==false){
			qDebug()<<"vait read signal";
			QDataStream in(TcpSocket);
			in.setVersion(QDataStream::Qt_4_0);
				for (;;) {
					if (!NextBlockSize) {
						if (TcpSocket->bytesAvailable() < sizeof(quint16)) {
							qDebug()<<"read signal";
							break;
						}
						in >> NextBlockSize;
					}
					if (TcpSocket->bytesAvailable() < NextBlockSize) {
						qDebug()<<"reed signal";
						break;
					}
					in >>gameInProgres;
					qDebug()<<gameInProgres<<"iterator signal";
					if(gameInProgres==true){
						qDebug()<<gameInProgres<<"iterator signal";
						startgame();
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
					gethod=false;
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
QList<QString> Network_Player::getActivInterfase(){ 
	QList<QString> listInterfase;
	QString temp;
	QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
	QHostAddress IPtempDefine("127.0.0.1");
	foreach (QHostAddress IPtemp,QNetworkInterface::allAddresses ()){
		temp=IPtemp.toString();
		if((temp.count(":")==0)&&(IPtemp!=IPtempDefine)){
			listInterfase<<temp;
		}
	}
	return listInterfase;
}
void Network_Player::giveLastMoves(MOVE lastMove[maxFiguresNumber]) {
	int i=0;
	while(i<maxFiguresNumber){
		if((lastMove[i].from.x!=0)||(lastMove[i].from.y!=0)||(lastMove[i].to.x!=0)||(lastMove[i].to.y!=0)){
			QByteArray  arrBlock;
			QDataStream out(&arrBlock, QIODevice::WriteOnly);
			out.setVersion(QDataStream::Qt_4_0);
			out << quint16(0) <<lastMove[i].from.x << lastMove[i].from.y << lastMove[i].to.x <<lastMove[i].to.y;
			out.device()->seek(0);
			out << quint16(arrBlock.size() - sizeof(quint16));
			qDebug()<<quint16(arrBlock.size() - sizeof(quint16));
			if(TcpSocket==NULL)qDebug()<<"NULL";
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
void Network_Player::execMove(BOARD board){
	sleep(1);	
	slotReadyRead();
	do {
		if (gethod==false) {
			break;
		}
		usleep(300);
	} while (true);
	moveExecuted();
	gethod=true;
}
MOVE Network_Player::getMove() {
	return result;
};
bool Network_Player::itThisIP(QString Ip){
	QHostAddress hostaddress;
	hostaddress.setAddress(Ip);
	if(hostaddress!=QHostAddress:: Null)return 0;
	return 1;
}
char Network_Player::setSelfIp(QString Ip){
	QHostAddress hostaddress;
	hostaddress.setAddress(Ip);
	if(hostaddress!=QHostAddress:: Null){
		selfIp=Ip;
		return 0;
	}
	return 1;
}
Network_Player::~Network_Player(){
	qDebug()<<"delited";
}
