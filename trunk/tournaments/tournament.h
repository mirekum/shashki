#ifndef _TOURNAMENT_H_
	#define _TOURNAMENT_H_
	
	#include <QtCore>
	#include "Model/board.h"
	#include "Model/game.h"
	#include "Players/player.h"
	
	class Tournament: public QObject {
		Q_OBJECT
	protected:
		// игроки
		Player *wp, *bp;
		// метаинформация
		char *title;
		// кол-во партий
		int Num;
		// счётчики
		int Cnt, w, b, d;
	public:
		// проведение турнира
		Tournament(char *_title, Player *_wp, Player *_bp, int _Num);
	protected:
		// проведение одного матча
		void game();
		// результаты турнира
		void results();
	public slots:
		// конец игры
		void finishGame(GAMESTATE);
	};
	
#endif

