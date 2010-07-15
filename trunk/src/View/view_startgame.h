#ifndef _VIEW_STARTGAME_H_
	#define _VIEW_STARTGAME_H_
	
	#include "Players/player.h"
	#include "View/view.h"
	#include "View/view_main.h"
	
	class View_StartGame: public View {
		Q_OBJECT
	protected:
		QWidget *window;
		QFrame *greeting;
		QFrame *settingsBox;
		PLAYER_TYPE wPlr, bPlr;
		PLAYER_SETTINGS wSet, bSet;
		COLOR curColor;
	public:
		View_StartGame(View_Main &main_ui);
		// show first screen
		void show();
		// ask settings for players
		void playersSettings(COLOR color = WHITE);
		// send data for game creation
		void sendPlayersData();
	signals:
		void createGame(PLAYER_TYPE wPlr, PLAYER_SETTINGS wSet, PLAYER_TYPE bPlr, PLAYER_SETTINGS bSet);
	protected slots:
		// set up players dialog
		void startGame();
		// remember player settings
		void getPlrSettings();
	};
	
#endif

