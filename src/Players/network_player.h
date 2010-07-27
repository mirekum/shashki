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
		bool gethod;
		bool gameInProgres;
		QTcpSocket* TcpSocket;
		QTcpServer* tcpServer;
		quint16     NextBlockSize;
		QString selfIp;
		QList<QString> listServer;
		QUdpSocket*udpSocketrelise;
		QUdpSocket*udpSocketinput;
	public:
		bool itThisIP(QString Ip);
		void startgame();
		void relise();
		QList<QString> getList();
		QList<QString> getActivInterfase();
		char setSelfIp(QString Ip);//zadanie svoego Ip
		void giveLastMoves(MOVE lastMove[maxFiguresNumber]) ;
		Network_Player();
		int createServer();
		virtual MOVE getMove();
		void execMove(BOARD board);
		void createClient(QString strHost);//coedinenie c ukazannim Ip
		~Network_Player();
		// get player type
		virtual PLAYER_TYPE type() {return NETWORK;};
	private slots:
		void slotReadyRead();
		void slotConnected();
		void slotNewConnection();
		void processPendingDatagrams();
		void slotError(QAbstractSocket::SocketError);
	signals:
		void inputSoed();
		void searchUpdate();
		void conectComplite();//signal o soedinenii
		
	};
	
#endif

