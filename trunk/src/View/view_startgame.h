#ifndef _VIEW_STARTGAME_H_
	#define _VIEW_STARTGAME_H_
	
	#include "View/view.h"
	#include "View/view_main.h"
	#include "Players/player.h"
	#include "Players/ai_player.h"
	#include "Players/bluetooth_player.h"
	#include "Players/network_player.h"
	
	class View_StartGame: public QObject, public View {
		Q_OBJECT
	protected:
		QWidget *window;
		QFrame *greeting;
		QFrame *settingsBox;
		QPushButton *next_btn;
		Ai_Player *AiPlr;
		Network_Player *NetworkPlr;
		Bluetooth_Player *BluetoothPlr;
		PLAYER_TYPE wPlr, bPlr;
		Player *wp, *bp;
		COLOR curColor;
	public:
		View_StartGame(View_Main &main_ui);
		~View_StartGame();
		// show first screen
		void show();
		// setting up players
		void setupPlayerBegin(COLOR color);
		// set up ai
		void setupAi();
		void setupAiShowLevel();
		void setupAiShowThrnum();
		void setupAiEnd();
		// set up network
		void setupNetwork();
		void setupNetworkShowInterface();
		void setupNetworkShowSearch();
		void setupNetworkEnd();
		// set up bluetooth
		void setupBluetooth();
		// send data for game creation
		void sendPlayersData();
	signals:
		void createGame(Player *wp, Player *bp);
		void setupPlayerEndSignal(Player *p);
	protected slots:
		void startGame();
		// setting up players
		void setupPlayerEndSlot(Player *p);
		// set up ai
		void setupAiGetLevel();
		void setupAiGetThrnum();
		// set up network
		void setupNetworkGetInterface();
		void setupNetworkGetSearch();
		void setupNetworkUpdateSearch();
		// set up bluetooth
	};
	
#endif

