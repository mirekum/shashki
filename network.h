#ifndef _NETWORK_H_
	#define _NETWORK_H_
	#include <iostream>
	#include "board.h"
	#include "player.h"
	#include <unistd.h>
	#include <sys/ioctl.h>
	#include <net/if.h>
	#include <arpa/inet.h>
	#include <stdio.h>
	#include <string.h>
	class NETWORK_PLAYER: public PLAYER {
	private:
		bool createServer();
		bool createLine();
		int sock;
		bool isitServer;
		bool sendServerOrClient();
	public:
		bool getServerOrClient(){return isitServer;};
		void giveLastMoves(MOVE lastMove[maxFiguresNumber]);
		NETWORK_PLAYER();
		~NETWORK_PLAYER();
		// chooses partial half-move
		virtual MOVE getMove(BOARD board);
		
	};
	
#endif

