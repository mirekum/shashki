#ifndef _TOURNAMENT_H_
	#define _TOURNAMENT_H_
	
	#include <QtCore>
	#include <string>
	#include <ctype.h>
	#include "Model/board.h"
	#include "Model/game.h"
	#include "Players/player.h"
	
	class Tournament: public QObject {
		Q_OBJECT
	protected:
		// игра
		Game *game;
		// игроки
		Player *wp, *bp;
		// метаинформация
		std::string title;
		// кол-во партий
		int Num;
		// счётчики
		int Cnt, w, b, d;
	public:
		// проведение турнира
		Tournament(std::string _title, Player *_wp, Player *_bp, int _Num);
	protected:
		// проведение одного матча
		void startGame();
		// результаты турнира
		void results();
	public slots:
		// конец игры
		void finishGame(GAMESTATE);
	};
	
	// вспомогательная функция: строка - число?
	bool is_numeric(char *s);
	
#endif

