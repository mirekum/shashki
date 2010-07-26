#include "Players/network_player.h"
#include <QtNetwork>

#define portConect 27015
#define portConectrelise 47475
#define portConectreliseinput 45455

#define Host_Not_Found_Error 1
#define Connection_Refused_Error 2
#define Remote_Host_Closed_Error 3
#define Error_Criate_Server 4


/* methods of class of the network player */
Network_Player::Network_Player(){
	m_pTcpSocket=NULL;
	udpSocketrelise = new QUdpSocket(this);
	udpSocketrelise->bind(portConectrelise);
	connect(udpSocketrelise, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

	udpSocketinput = new QUdpSocket(this);
	udpSocketinput->bind(portConectreliseinput);
	connect(udpSocketinput, SIGNAL(readyRead()),this, SLOT(processPendingDatagramsinput()));
	gameInProgres=false;
	m_ptcpServer=NULL;
	m_nNextBlockSize=0;
	selfIp="127.0.0.1";
	gethod=true;
}
void Network_Player::startgame(){
	gameInProgres=true;	
	conectComplite();
}
char Network_Player::createServer(){
	m_ptcpServer = new QTcpServer(this); 
	QHostAddress adrr (selfIp);
	if (!m_ptcpServer->listen(adrr/*(selfIp)*/, portConect)) {
		m_ptcpServer->close();
		m_ptcpServer=NULL;
		return Error_Criate_Server;
	}
	connect(m_ptcpServer, SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
	return 0;
};
void Network_Player::relise(){
	QUdpSocket udpSocket;
	QString tipe;
	if(color==BLACK){
		tipe="B";
	}
	if(color==WHITE){
		tipe="W";
	}
	qDebug()<<tipe+selfIp.toStdString().c_str();
	QByteArray datagram = (tipe+selfIp).toStdString().c_str() ;
	udpSocket.writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast, portConectrelise);
	listServer.clear();
}
void Network_Player::processPendingDatagramsinput(){
	QUdpSocket* udpSocket = (QUdpSocket*)sender();
	QHostAddress IPtempDefine("127.0.0.1");
	while (udpSocket->hasPendingDatagrams()){
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());

		const char*colorin=datagram.data();
		const char*sendIp=&colorin[1];
		qDebug()<<colorin[0]<<"otlad read onli"<<sendIp;
		QHostAddress hostaddress;
		if(((colorin[0]=='B')&&(color==WHITE))||((colorin[0]=='W')&&(color==BLACK))){
		hostaddress.setAddress(sendIp);qDebug()<<colorin<<"otlad read onli";
		}
		if((hostaddress!=QHostAddress:: Null)&&(!listServer.contains(sendIp)&&(selfIp!=sendIp))&&(hostaddress!=IPtempDefine)){
			listServer<<sendIp;
			searchUpdate();
			qDebug()<<"input readonli"<<sendIp;	
		}
	}
}
void Network_Player::processPendingDatagrams(){
	QUdpSocket* udpSocket = (QUdpSocket*)sender();
	QHostAddress IPtempDefine("127.0.0.1");
	while (udpSocket->hasPendingDatagrams()){
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());
		qDebug()<<datagram.data();
		const char*colorin=datagram.data();
		const char*sendIp=&colorin[1];
		qDebug()<<colorin[0]<<"otlad rw"<<sendIp;
		QHostAddress hostaddress;
		if(((colorin[0]=='B')&&(color==WHITE))||((colorin[0]=='W')&&(color==BLACK))){
		hostaddress.setAddress(sendIp);qDebug()<<colorin<<"otladrw";
		}
		if((hostaddress!=QHostAddress:: Null)&&(!listServer.contains(sendIp)&&(selfIp!=sendIp))&&(hostaddress!=IPtempDefine)){
			listServer<<sendIp;
			searchUpdate();
			qDebug()<<"input rw"<<sendIp;	
		}	
		if((hostaddress!=QHostAddress:: Null)&&(selfIp!=sendIp)&&(hostaddress!=IPtempDefine)){
			QUdpSocket udpSocketReturn;
			QString tipe;
			if(color==BLACK){
				tipe="B";
			}
			if(color==WHITE){
				tipe="W";
			}
			QByteArray datagramReturn = (tipe+selfIp).toStdString().c_str() ;
			udpSocketReturn.writeDatagram(datagramReturn.data(), datagramReturn.size(),QHostAddress::Broadcast,portConectreliseinput);
			qDebug()<<"Unser rw"<<datagramReturn.data()<<sendIp;
		}
	}
}
QList<QString> Network_Player::getList(){
	return listServer;
}
void Network_Player::slotNewConnection(){
	if(gameInProgres==false){
		m_pTcpSocket = m_ptcpServer->nextPendingConnection();
		connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
		connect(m_pTcpSocket, SIGNAL(readyRead()),SLOT(slotReadyRead()));
		slotConnected();
		QByteArray  arrBlock;
		QDataStream out(&arrBlock, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);
		int i=100;
		out << quint16(0)<<true;
		qDebug()<<true;
		out.device()->seek(0);
		out << quint16(arrBlock.size() - sizeof(quint16));
		if(m_pTcpSocket==NULL)qDebug()<<"NULL";
		m_pTcpSocket->write(arrBlock);
		connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));
		startgame();

	}
	else{
		QTcpSocket*temp_pTcpSocket = m_ptcpServer->nextPendingConnection();
		QByteArray  arrBlock;
		QDataStream out(&arrBlock, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);
		out << quint16(0)<<false;
		out.device()->seek(0);
		out << quint16(arrBlock.size() - sizeof(quint16));
		if(temp_pTcpSocket==NULL)qDebug()<<"NULL";
		temp_pTcpSocket->write(arrBlock);
		temp_pTcpSocket->close();
		delete temp_pTcpSocket;
	}
}	
void Network_Player::slotError(QAbstractSocket::SocketError err){
	if(err==QAbstractSocket::HostNotFoundError){
		m_pTcpSocket->close();
		//delete m_pTcpSocket;
		//m_pTcpSocket=NULL;
		error(Host_Not_Found_Error);
		qDebug()<<"HostNotFoundError";
	}	
	else if(err == QAbstractSocket::ConnectionRefusedError){
		m_pTcpSocket->close();
		//delete m_pTcpSocket;
		//m_pTcpSocket=NULL;
		error(Connection_Refused_Error);
		qDebug()<<"ConnectionRefusedError";
	}
	else if(err == QAbstractSocket::RemoteHostClosedError){
		m_pTcpSocket->close();
		//delete m_pTcpSocket;
		//m_pTcpSocket=NULL;
		error(Remote_Host_Closed_Error);
		qDebug()<<"RemoteHostClosedError";
	}
}
char Network_Player::createClient( QString strHost){
	if(m_pTcpSocket!=NULL){
		m_pTcpSocket->close();
		delete m_pTcpSocket;
		m_pTcpSocket=NULL;
	};
	qDebug()<<"conect tuu hast:" <<strHost;
	m_pTcpSocket = new QTcpSocket(this);
	m_nNextBlockSize=0;
	m_pTcpSocket->connectToHost(strHost, portConect);
	connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));

}
void Network_Player::slotConnected(){
	qDebug()<<"Received the connected() signal";

/*	MOVE lastMove[maxFiguresNumber];
	lastMove[4].from.x=1;
	giveLastMoves(lastMove);
*/
}

void Network_Player::slotReadyRead(){
	if(gethod){
		if(gameInProgres==false){
			qDebug()<<"vait read signal";
			QDataStream in(m_pTcpSocket);
			in.setVersion(QDataStream::Qt_4_0);
				for (;;) {
					if (!m_nNextBlockSize) {
						if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
							qDebug()<<"read signal";
							break;
						}
						in >> m_nNextBlockSize;
					}
					if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
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
						m_pTcpSocket->close();
					}
					m_nNextBlockSize = 0;
				}
		}
		else{	
			qDebug()<<"vait read";
			QDataStream in(m_pTcpSocket);
			in.setVersion(QDataStream::Qt_4_0);
				for (;;) {
					if (!m_nNextBlockSize) {
						if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
							qDebug()<<"read lern";
							break;
						}
						in >> m_nNextBlockSize;
						qDebug()<<m_nNextBlockSize;
					}
					if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
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
					m_nNextBlockSize = 0;
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
			if(m_pTcpSocket==NULL)qDebug()<<"NULL";
			m_pTcpSocket->write(arrBlock);
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
//	
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
/*
	if(m_ptcpServer!=NULL){
		m_pTcpSocket->close();
		delete m_ptcpServer;
		m_ptcpServer=NULL;
	}
	if(m_pTcpSocket!=NULL){
		m_pTcpSocket->close();
		delete m_pTcpSocket;
		m_pTcpSocket=NULL;
	}
*/
	qDebug()<<"delited";
}
