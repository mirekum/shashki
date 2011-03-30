#include "tournament.h"

// проведение турнира
Tournament::Tournament(char *_title, Player *_wp, Player *_bp, int _Num) {
	Cnt = 0;
	w = b = d = 0;
	Num = _Num;
	title = _title;
	wp = _wp;
	bp = _bp;
	// поехали!
	for (int i = 0; i < Num; i++) {
		game();
	}
}

// проведение одного матча
void Tournament::game() {
	Game *game = new Game();
	
	connect(game, SIGNAL(finishGame(GAMESTATE)), SLOT(finishGame(GAMESTATE)));
	
	game->init(wp, bp);
	game->start();
	
	//disconnect(game, SIGNAL(finishGame(GAMESTATE)), SLOT(finishGame(GAMESTATE)));
}

// результаты турнира
void Tournament::results() {
	qDebug() << "----------------------------------------";
	qDebug() << title;
	qDebug() << "White: " << w;
	qDebug() << "Black: " << b;
	qDebug() << "Draws: " << d;
	qDebug() << "----------------------------------------";
}

// конец игры
void Tournament::finishGame(GAMESTATE res_flag) {
	//qDebug() << title << " -> " << res_flag;
	// запоминаем результат
	switch (res_flag) {
		case END_WHITE:
			w++;
		break;
		case END_BLACK:
			b++;
		break;
		default:
			d++;
		break;
	}
	// следим за окончанием
	if (++Cnt >= Num) {
		results();
	}
}

