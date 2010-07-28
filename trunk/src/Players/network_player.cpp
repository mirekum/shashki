/*
1.UDP
|--->WY"SELFIP1"--->||--->BY"SELFIP1"--->
|<---BN"SELFIP2"<---||<---WN"SELFIP2"<---
|<---BN"SELFIP3"<---||<---WN"SELFIP3"<---
|-------||----------||-------||----------
|<---BN"SELFIPK"<---||<---WN"SELFIPK"<---
2.TCP
|<-connect---||<-connect---
|---->Y----->||---->N----->
|----game----||Hold or new connect
*/
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
	tcp_socket = NULL;
	game_in_progress = false;
	tcp_server = NULL;
	next_block_size = 0;
	self_ip = "127.0.0.1";
	cur_move = true;
}
void Network_Player::startGame() {
	game_in_progress = true;	
	connectComplete();
}
int Network_Player::createServer() {
	tcp_server = new QTcpServer(this); 
	QHostAddress adrr (self_ip);
	if (!tcp_server->listen(adrr/*(selfIp)*/, PORT_CONNECT)) {
		tcp_server->close();
		tcp_server = NULL;
		return CREATE_SERVER_ERROR;
	}
	connect(tcp_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
	return 0;
};
void Network_Player::sendAnnouncement(QString need_answer) {
	QUdpSocket udp_socket;
	QString mess;
	if (color == BLACK) {
		mess = mess+"B";
	}
	else if (color == WHITE) {
		mess = mess+"W";
	}
	mess = mess+need_answer+self_ip;
	QByteArray datagram = mess.toStdString().c_str() ;
	udp_socket.writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, PORT_CONNECT_ANNOUNCE);
	servers_list.clear();
}

void Network_Player::processAnnouncement() {
	QUdpSocket* udp_socket = (QUdpSocket*)sender();
	QHostAddress localhost_address("127.0.0.1");
	while (udp_socket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udp_socket->pendingDatagramSize());
		udp_socket->readDatagram(datagram.data(), datagram.size());
		char* tmp = datagram.data();
		const char recv_color =  tmp[0];
		const char recv_need_answer =  tmp[1];
		const char *recv_ip = & tmp[2];
		qDebug()<<recv_color<<"INPUT DATA";
		QHostAddress recv_address;
		if (((recv_color == 'B') && (color == WHITE)) ||
		    ((recv_color == 'W') && (color == BLACK))) {
			recv_address.setAddress(recv_ip);
			if ((recv_address != QHostAddress:: Null)  && 
			    (recv_address != localhost_address) &&
                            (recv_ip != self_ip)) {
				if (recv_need_answer == 'Y') {
					sendAnnouncement("N");
				}
				if (!servers_list.contains(recv_ip)) {
					servers_list<<recv_ip;
					searchUpdate();
					qDebug()<<"ADD IN LIST SERVER"<<recv_ip;	
				}
			}
			
		}
	}
}

QList<QString> Network_Player::getEnemyIpAddresses() {
	return servers_list;
}
void Network_Player::resolution(QString YN, QTcpSocket* soketResolution) {
		QByteArray  arrBlock;
		QDataStream out(&arrBlock, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);
		out << quint16(0)<<YN;
		qDebug()<<YN;
		out.device()->seek(0);
		out << quint16(arrBlock.size() - sizeof(quint16));
		soketResolution->write(arrBlock);



}
void Network_Player::slotNewConnection() {
	if (game_in_progress == false) {
		tcp_socket = tcp_server->nextPendingConnection();
		connect(tcp_socket, SIGNAL(disconnected()), tcp_socket, SLOT(deleteLater()));
		connect(tcp_socket, SIGNAL(readyRead()),SLOT(slotReadyRead()));
		slotConnected();
		resolution("Y", tcp_socket);
		connect(tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));
		startGame();

	}
	else{
		QTcpSocket*temp_tcp_socket = tcp_server->nextPendingConnection();
		resolution("N", temp_tcp_socket);
		temp_tcp_socket->close();
		delete temp_tcp_socket;
	}
}	
void Network_Player::slotError(QAbstractSocket::SocketError err) {
	if ( err == QAbstractSocket::HostNotFoundError) {
		tcp_socket->close();
		error(HOST_NOT_FOUND_ERROR);
		qDebug()<<"HostNotFoundError";
	}	
	else if (err == QAbstractSocket::ConnectionRefusedError) {
		tcp_socket->close();
		error(CONNECTION_REFUSED_ERROR);
		qDebug()<<"ConnectionRefusedError";
	}
	else if (err == QAbstractSocket::RemoteHostClosedError) {
		tcp_socket->close();
		error(REMOTE_HOST_CLOSED_ERROR);
		qDebug()<<"RemoteHostClosedError";
	}
}
void Network_Player::createClient( QString Host) {
	if (tcp_socket != NULL) {
		tcp_socket->close();
		delete tcp_socket;
		tcp_socket = NULL;
	};
	qDebug()<<"conect too hast:" <<Host;
	tcp_socket = new QTcpSocket(this);
	next_block_size = 0;
	tcp_socket->connectToHost(Host, PORT_CONNECT);
	connect(tcp_socket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(tcp_socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));

}
void Network_Player::slotConnected() {
	qDebug()<<"Received the connected() signal";
}

void Network_Player::slotReadyRead() {
	if (cur_move) {
		qDebug()<<"vait read signal";
		QDataStream in(tcp_socket);
		in.setVersion(QDataStream::Qt_4_0);
		for (;;) {
			if (!next_block_size) {
				if (tcp_socket->bytesAvailable() < sizeof(quint16)) {
					break;
				}
				in >> next_block_size;
			}
			if (tcp_socket->bytesAvailable() < next_block_size) {
				qDebug()<<"reed signal";
				break;
			}
			if (game_in_progress == false) {
					QString mes;
					in >>mes;
					qDebug()<<mes<<"-signal";
					if (mes == "Y") {
						qDebug()<<game_in_progress<<"signal";
						startGame();
					}
					else{
						tcp_socket->close();
					}
					next_block_size = 0;
					return;
			}
			else{	
				qDebug()<<"vait read";
				QDataStream in(tcp_socket);
				in.setVersion(QDataStream::Qt_4_0);
						result.from.x = 0;
						result.from.y = 0;
						result.to.x = 0;
						result.to.y = 0;
						in >>result.from.x>>result.from.y>>result.to.x>>result.to.y;
						cur_move = false;
						qDebug()<<result.from.x;
						qDebug()<<result.from.y;
						qDebug()<<result.to.x;
						qDebug()<<result.to.y;
						next_block_size = 0;
						return;
			}
		}
	}
}
QList<QString> Network_Player::getSelfIpAddresses() { 
	QList<QString> list_interfase;
	QString temp;
	QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
	QHostAddress localhost_address("127.0.0.1");
	foreach (QHostAddress ip_temp,QNetworkInterface::allAddresses ()){
		temp=ip_temp.toString();
		if ((temp.count(":")==0)&&(ip_temp!=localhost_address)) {
			list_interfase<<temp;
		}
	}
	return list_interfase;
}
void Network_Player::giveLastMoves(MOVE lastMove[maxFiguresNumber]) {
	int i=0;
	while (i < maxFiguresNumber) {
		if ((lastMove[i].from.x != 0)||(lastMove[i].from.y != 0)||(lastMove[i].to.x != 0)||(lastMove[i].to.y != 0)) {
			QByteArray  arr_block;
			QDataStream out(&arr_block, QIODevice::WriteOnly);
			out.setVersion(QDataStream::Qt_4_0);
			out << quint16(0) <<lastMove[i].from.x << lastMove[i].from.y << lastMove[i].to.x <<lastMove[i].to.y;
			out.device()->seek(0);
			out << quint16(arr_block.size() - sizeof(quint16));
			qDebug()<<quint16(arr_block.size() - sizeof(quint16));
			tcp_socket->write(arr_block);
			qDebug()<<"out";
			qDebug()<<lastMove[i].from.x<<lastMove[i].from.y<<lastMove[i].to.x<<lastMove[i].to.y;
			lastMove[i].from.x = 0;
			lastMove[i].from.y = 0;
			lastMove[i].to.x = 0;
			lastMove[i].to.y = 0;
		}
		i++;
	}
}
void Network_Player::execMove(BOARD board) {
	sleep(1);	
	slotReadyRead();
	do {
		if (cur_move == false) {
			break;
		}
		usleep(300);
	} while (true);
	moveExecuted();
	cur_move = true;
}
MOVE Network_Player::getMove() {
	return result;
}
bool Network_Player::isIp(QString ip) {
	QHostAddress hostaddress;
	hostaddress.setAddress(ip);
	if (hostaddress != QHostAddress::Null) return 1;
	return 0;
}
bool Network_Player::setSelfIp(QString ip){
	if (isIp(ip)) {
		self_ip = ip;
		udp_listen_socket = new QUdpSocket(this);
		udp_listen_socket->bind(PORT_CONNECT_ANNOUNCE);
		connect(udp_listen_socket, SIGNAL(readyRead()), this, SLOT(processAnnouncement()));
		return true;
	}
	return false;
}
Network_Player::~Network_Player() {
	qDebug()<<"delited";
}
