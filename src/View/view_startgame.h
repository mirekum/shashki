#ifndef _VIEW_STARTGAME_H_
	#define _VIEW_STARTGAME_H_
	
	#include "View/view.h"
	#include "View/view_main.h"
	#include "Players/player.h"
	
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
	protected slots:
		// set up players dialog
		void start_game();
		// remember player settings
		void getPlrSettings();
	};
	
#endif

