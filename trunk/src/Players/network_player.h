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
		QTcpServer*m_ptcpServer;
		QTcpSocket* m_pTcpSocket;
		quint16     m_nNextBlockSize;
		QString selfIp;
		QList<QString> listServer;
	public:
		void startgame();
		void relise();
		QList<QString> getList();
		QList<QString> getActivInterfase();
		void setSelfIp(QString Ip);//zadanie svoego Ip
		void giveLastMoves(MOVE lastMove[maxFiguresNumber]) ;
		Network_Player();
		char createServer();
		virtual MOVE getMove();
		void execMove(BOARD board);
		char createClient(QString strHost);//coedinenie c ukazannim Ip
		~Network_Player();
		// get player type
		virtual PLAYER_TYPE type() {return NETWORK;};
	private slots:
		void slotReadyRead();
		void slotConnected();
		void slotNewConnection();
		void processPendingDatagrams();
		void processPendingDatagramsinput();
	signals:
		void searchUpdate();
		void conectComplite();//signal o soedinenii
		
	};
	
#endif
