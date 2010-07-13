#ifndef _PLAYER_FACTORY_H_
	#define _PLAYER_FACTORY_H_
	
	#include "Players/player.h"
	#include "Players/ai.h"
	#include "Players/bluetooth.h"
	#include "Players/network.h"
	#include "View/view_board.h"
	
	class Player_Factory {
	private:
		Player_Factory() {}
	public:
		static Player* create(PLAYER_TYPE _type) {
			switch (_type) {
				case HUMAN:
					return new View_Board();
				case AI:
					return new Ai_Player();
				case NETWORK:
					return new Network_Player();
				case BLUETOOTH:
					return new Bluetooth_Player();
				default:
					exit(1);
			}
			return NULL;
		}
		static char* getPlrText(PLAYER_TYPE _type) {
			switch (_type) {
				case HUMAN:
					return "Human";
				case AI:
					return "Computer";
				case NETWORK:
					return "Network";
				case BLUETOOTH:
					return "Bluetooth";
				default:
					exit(1);
			}
			return NULL;
		}
	};
	
#endif

