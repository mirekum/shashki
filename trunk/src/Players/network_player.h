#ifndef _NETWORK_H_
	#define _NETWORK_H_
	
	#include "Players/player.h"
	#include <QTcpSocket>
	
	class QTcpServer;
	class QUdpSocket;
	class Network_Player: public Player {
		Q_OBJECT
	private:
		bool vaiting;
		bool curMove;
		bool gameInProgress;
		QTcpSocket* TcpSocket;
		QTcpServer* tcpServer;
		quint16     NextBlockSize;
		QString selfIp;
		QList<QString> ServerList;
		QUdpSocket*udpSocketrelise;
	public:
		bool isIp(QString Ip);
		void startGame();
		void sendAnnouncement();
		QList<QString> getEnemyIpAddresses();
		QList<QString> getSelfIpAddresses();
		bool setSelfIp(QString Ip);
		void giveLastMoves(MOVE lastMove[maxFiguresNumber]) ;
		Network_Player();
		int createServer();
		virtual MOVE getMove();
		void execMove(BOARD board);
		void createClient(QString Host);
		~Network_Player();
		virtual PLAYER_TYPE type() {return NETWORK;};
	private slots:
		void slotReadyRead();
		void slotConnected();
		void slotNewConnection();
		void processPendingDatagrams();
		void slotError(QAbstractSocket::SocketError);
	signals:
		void searchUpdate();
		void connectComplete();//signal o soedinenii
		
	};
	
#endif

