#ifndef _NETWORK_H_
	#define _NETWORK_H_
	
	#include <iostream>
	#include <unistd.h>
	#include <sys/ioctl.h>
	#include <net/if.h>
	#include <arpa/inet.h>
	#include <stdio.h>
	#include <string.h>
	#include "Players/player.h"
	
	class Network_Player: public Player {
	private:
		bool createServer();
		bool createLine();
		int sock;
		bool isitServer;
		bool sendServerOrClient();
		bool giveAdres(std::string&adr);
	public:
		bool getServerOrClient(){return isitServer;};
		void giveLastMoves(MOVE lastMove[maxFiguresNumber]) ;
		Network_Player();
		~Network_Player();
		void sendToError(char send);
		// chooses partial half-move
		virtual MOVE getMove(BOARD board);
		// get player type
		virtual PLAYER_TYPE type() {return NETWORK;};
	};
	
#endif

