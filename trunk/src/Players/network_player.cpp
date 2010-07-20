#include "Players/network_player.h"
#include <QtNetwork>

#define portConect 27015
#define portConectrelise 47475

#define ERROR_SOCKET 1
#define ERROR_BIND 2
#define ERROR_ACCEPT 3
#define ERROR_CONEKT 4
#define ERROR_CRIATE_SERVER 5
/* methods of class of the network player */
Network_Player::Network_Player(){
	QUdpSocket*udpSocket = new QUdpSocket(this);
	udpSocket->bind(portConectrelise);
	connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
};
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
	qDebug()<<selfIp.toStdString().c_str();
	QByteArray datagram = selfIp.toStdString().c_str() ;
	udpSocket.writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast, portConectrelise);
}
void Network_Player::processPendingDatagrams(){
	QUdpSocket* udpSocket = (QUdpSocket*)sender();
	while (udpSocket->hasPendingDatagrams()){
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());
		QHostAddress hostaddress;
		hostaddress.setAddress(datagram.data());
		if(hostaddress!=QHostAddress:: Null){
			listServer<<datagram.data();
			qDebug()<<datagram.data();
		}
	}
}
QList<QString> Network_Player::getList(){
	return listServer;
}
void Network_Player::slotNewConnection(){
	slotConnected();
	m_pTcpSocket = m_ptcpServer->nextPendingConnection();
	connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
	connect(m_pTcpSocket, SIGNAL(readyRead()),SLOT(slotReadyRead()));
	conectComplite();
	
}
char Network_Player::createClient( QString strHost){
	m_pTcpSocket = new QTcpSocket(this);
	m_nNextBlockSize=0;
	m_pTcpSocket->connectToHost(strHost, portConect);
	connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	selfIp=strHost;//ubrat
}
void Network_Player::slotConnected(){
	qDebug()<<"Received the connected() signal";
}
void Network_Player::slotReadyRead(){
	qDebug()<<"vait read";
	QDataStream in(m_pTcpSocket);
	in.setVersion(QDataStream::Qt_4_2);
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
			in >>thisMuve.from.x;
			in >>thisMuve.from.y;
			in >>thisMuve.to.x;
			in >>thisMuve.to.y;
		        if(thisMuve.from.x!=0){qDebug()<<"ennd";}
			m_nNextBlockSize = 0;
			giveMuve();
		}
}
QList<QString> Network_Player::getActivInterfase(){ 
	QList<QString> listInterfase;
	QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
	foreach (QHostAddress IPtemp,QNetworkInterface::allAddresses ())listInterfase<<IPtemp.toString();
	return listInterfase;
}
void Network_Player::giveLastMoves(MOVE lastMove[maxFiguresNumber]) {
	int i=0;

	while(i<maxFiguresNumber){
		QByteArray  arrBlock;
		QDataStream out(&arrBlock, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_2);
		out << quint16(0) << lastMove[i].from.x << lastMove[i].from.y << lastMove[i].to.x <<lastMove[i].to.y;
		out.device()->seek(0);
		out << quint16(arrBlock.size() - sizeof(quint16));
		this->m_pTcpSocket->write(arrBlock);
		lastMove[i].from.x=0;
		lastMove[i].from.y=0;
		lastMove[i].to.x=0;
		lastMove[i].to.y=0;
		i++;
	}

};
MOVE Network_Player::getMove(BOARD board) {
	return thisMuve;
};
void Network_Player::setSelfIp(QString Ip){
	selfIp=Ip;
}
Network_Player::~Network_Player(){
};
