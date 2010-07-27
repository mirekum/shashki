#ifndef _NETWORK_H_
	#define _NETWORK_H_
	
	#include "Players/player.h"
	#include <QTcpSocket>
	
	class QTcpServer;
	class QUdpSocket;
	class Network_Player: public Player {
		Q_OBJECT
	private:
		bool waiting;
		bool cur_move;
		bool game_in_progress;
		QTcpSocket *tcp_socket;
		QTcpServer *tcp_server;
		quint16     next_block_size;
		QString self_ip;
		QList<QString> servers_list;
		QUdpSocket *udp_listen_socket;
	public:
		bool isIp(QString ip);
		void startGame();
		void sendAnnouncement(QString need_answer);
		QList<QString> getEnemyIpAddresses();
		QList<QString> getSelfIpAddresses();
		bool setSelfIp(QString ip);
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
		void processAnnouncement();
		void slotError(QAbstractSocket::SocketError);
	signals:
		void searchUpdate();
		void connectComplete();
		
	};
	
#endif

