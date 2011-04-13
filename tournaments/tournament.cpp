#include "tournament.h"

// проведение турнира
Tournament::Tournament(std::string _title, Player *_wp, Player *_bp, int _Num) {
	Cnt = 0;
	w = b = d = 0;
	Num = _Num;
	title = _title;
	wp = _wp;
	bp = _bp;
	// поехали!
	startGame();
}

// проведение одного матча
void Tournament::startGame() {
	// создаём игру
	game = new Game();
	// подсоединяемся к слоту
	connect(game, SIGNAL(finishGame(GAMESTATE)), SLOT(finishGame(GAMESTATE)));
	// запускаем игру
	game->init(wp, bp);
	game->start();
}

// результаты турнира
void Tournament::results() {
	qDebug() << "----------------------------------------";
	qDebug() << title.c_str();
	qDebug() << "White: " << w;
	qDebug() << "Black: " << b;
	qDebug() << "Draws: " << d;
	qDebug() << "----------------------------------------";
}

// конец игры
void Tournament::finishGame(GAMESTATE res_flag) {
	// удаляем игру
	delete game;
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
	// промежуточные результаты
	if (Cnt % 100 == 0) qDebug() << title.c_str() << " :: " << Cnt << " (w: " << w << ", b: " << b << ", d: " << d << ")";
	// следим за окончанием
	if (++Cnt >= Num) {
		results();
	} else {
		startGame();
	}
}

