#ifndef _CONTROL_H_
	#define _CONTROL_H_
	
	#include <QtCore>
	#include "View/view_main.h"
	#include "Players/player.h"
	#include "Model/game.h"
	
	class Control: public QObject {
		Q_OBJECT
	protected:
		View_Main *main_ui;
		Game *game;
	public:
		Control(View_Main &_main_ui, Game &_game);
	public slots:
		void createGame(PLAYER_SETTINGS wSet, PLAYER_SETTINGS bSet);
	};
	
#endif

