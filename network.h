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
		bool create_Server();
		bool create_Line();
		int sock;
	public:
		NETWORK_PLAYER(){
                type = NONE;
		char res[2];
                std::cout << "do you wont create server game [y/n]:"; std::cin >>res;
		switch (res[1]) {
			case 'y':
				if(!create_Server())exit(1);
			case 'n':
				if(!create_Line())exit(2);
			default:
				exit(3);
		}
		

		}
		// chooses partial half-move
		virtual MOVE getMove(BOARD board);
		
	};
	
#endif

