#include "Players/network_player.h"
#include <QtNetwork>

#define portConect 27015
#define portConectrelise 47475
#define portConectreliseinput 45455

#define ERROR_SOCKET 1
#define ERROR_BIND 2
#define ERROR_ACCEPT 3
#define ERROR_CONEKT 4
#define ERROR_CRIATE_SERVER 5


/* methods of class of the network player */
Network_Player::Network_Player(){
	m_pTcpSocket=NULL;
	QUdpSocket*udpSocket = new QUdpSocket(this);
	udpSocket->bind(portConectrelise);
	connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
	QUdpSocket*udpSocketinput = new QUdpSocket(this);
	udpSocket->bind(portConectreliseinput);
	connect(udpSocketinput, SIGNAL(readyRead()),this, SLOT(processPendingDatagramsinput()));
	gameInProgres=false;
	m_ptcpServer=NULL;
	m_nNextBlockSize=0;
	selfIp="0.0.0.0";
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
		return ERROR_CRIATE_SERVER;
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
	while (udpSocket->hasPendingDatagrams()){
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());

		const char*colorin=datagram.data();
		const char*sendIp=&colorin[1];
		qDebug()<<colorin[0]<<"otlad"<<sendIp;
		QHostAddress hostaddress;
		if(((colorin[0]=='B')&&(color==WHITE))||((colorin[0]=='W')&&(color==BLACK))){
		hostaddress.setAddress(sendIp);qDebug()<<colorin<<"otlad";
		}
		if((hostaddress!=QHostAddress:: Null)&&(!listServer.contains(sendIp)&&(selfIp!=sendIp))){
			listServer<<sendIp;
			searchUpdate();
			qDebug()<<"input"<<sendIp;	
		}
	}
}
void Network_Player::processPendingDatagrams(){
	QUdpSocket* udpSocket = (QUdpSocket*)sender();
	while (udpSocket->hasPendingDatagrams()){
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());
		
		qDebug()<<datagram.data();
		const char*colorin=datagram.data();
		const char*sendIp=&colorin[1];
		qDebug()<<colorin[0]<<"otlad"<<sendIp;
		QHostAddress hostaddress;
		if(((colorin[0]=='B')&&(color==WHITE))||((colorin[0]=='W')&&(color==BLACK))){
		hostaddress.setAddress(sendIp);qDebug()<<colorin<<"otlad";
		}
		if((hostaddress!=QHostAddress:: Null)&&(!listServer.contains(sendIp)&&(selfIp!=sendIp))){
			listServer<<sendIp;
			searchUpdate();
			qDebug()<<"input"<<sendIp;	
		}	
		if((hostaddress!=QHostAddress:: Null)&&(selfIp!=sendIp)){
			QUdpSocket udpSocketReturn;
			QByteArray datagramReturn = selfIp.toStdString().c_str() ;
			udpSocketReturn.writeDatagram(datagram.data(), datagram.size(),hostaddress, portConectreliseinput);
			qDebug()<<"Unser"<<datagramReturn.data()<<sendIp;
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
	}
}	
char Network_Player::createClient( QString strHost){
	m_pTcpSocket = new QTcpSocket(this);
	m_nNextBlockSize=0;
	m_pTcpSocket->connectToHost(strHost, portConect);
	connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));

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
					}
					if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
						qDebug()<<"reed";
						break;
					}
					in >>gameInProgres;
					qDebug()<<gameInProgres<<"iterator";
					if(gameInProgres==true){
						qDebug()<<gameInProgres<<"iterator";
						startgame();
					}
					else{
						m_pTcpSocket->close();
					}
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
					}
					if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
						qDebug()<<"reed";
						break;
					}
					in >>result.from.x;
					in >>result.from.y;
					in >>result.to.x;
					in >>result.to.y;
					gethod=false;
					qDebug()<<result.from.x;
					m_nNextBlockSize = 0;
					moveExecuted();
				}
		}
	}

}
QList<QString> Network_Player::getActivInterfase(){ 
	QList<QString> listInterfase;
	QString temp;
	QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
	foreach (QHostAddress IPtemp,QNetworkInterface::allAddresses ()){
		temp=IPtemp.toString();
		if(temp.count(":")==0){
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
			if(m_pTcpSocket==NULL)qDebug()<<"NULL";
			m_pTcpSocket->write(arrBlock);
			lastMove[i].from.x=0;
			lastMove[i].from.y=0;
			lastMove[i].to.x=0;
			lastMove[i].to.y=0;
		}
		i++;
	}

}
void Network_Player::execMove(BOARD board){
}
MOVE Network_Player::getMove() {
	return result;
	result.from.x=0;
	result.from.y=0;
	result.to.x=0;
	result.to.y=0;
	gethod=true;
};
void Network_Player::setSelfIp(QString Ip){
	selfIp=Ip;
}
Network_Player::~Network_Player(){
};
