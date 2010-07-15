#ifndef _CONTROL_H_
	#define _CONTROL_H_
	
	#include <QtCore>
	#include "Model/game.h"
	#include "View/view_main.h"
	#include "View/view_startgame.h"
	#include "View/view_board.h"
	#include "View/view_info.h"
	
	class Control: public QObject {
		Q_OBJECT
	protected:
		Game *game;
		Player *wp, *bp;
		View_Main *main_ui;
		View_StartGame *start_ui;
		View_Board *board_ui;
		View_Info *info_ui;
	public:
		Control(Game &_game, View_Main &_main_ui, View_StartGame &_start_ui, View_Board &_board_ui, View_Info &_info_ui);
		~Control();
	protected:
		Player *createPlayer(PLAYER_TYPE plr, PLAYER_SETTINGS set);
		void destroyPlayer(Player *p);
	public slots:
		void createGame(PLAYER_TYPE wPlr, PLAYER_SETTINGS wSet, PLAYER_TYPE bPlr, PLAYER_SETTINGS bSet);
	};
	
#endif
