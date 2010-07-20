#ifndef _NETWORK_H_
	#define _NETWORK_H_
	
	#include "Players/player.h"
	#include <QTcpSocket>
	
	class QTcpServer;
	class QUdpSocket;
	class Network_Player: public Player {
		Q_OBJECT
	private:
		QTcpServer*m_ptcpServer;
		MOVE thisMuve;
		QTcpSocket* m_pTcpSocket;
		quint16     m_nNextBlockSize;
		QString selfIp;
		QList<QString> listServer;
	public:
		void relise();
		QList<QString> getList();
		QList<QString> getActivInterfase();//возвращает значения парами i-име i+1-IP
		void setSelfIp(QString Ip);//zadanie svoego Ip
		void giveLastMoves(MOVE lastMove[maxFiguresNumber]) ;
		Network_Player();
		char createServer();
		virtual void getMove(BOARD board);
		char createClient(QString strHost);//coedinenie c ukazannim Ip
		~Network_Player();
		// get player type
		virtual PLAYER_TYPE type() {return NETWORK;};
	private slots:
		void slotReadyRead();
		void slotConnected();
		void slotNewConnection();
		void processPendingDatagrams();
	signals:
		void giveMuve();//signal chto nado vzat hod
		void conectComplite();//signal o soedinenii
		
	};
	
#endif

