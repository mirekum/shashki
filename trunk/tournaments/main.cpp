#include <QtCore>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tournament.h"
#include "Players/ai_player.h"

// entry point
int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	
	if (argc < 2) {
		qDebug() << "=== Error! ===========================================";
		qDebug() << "Please, give the filename with tournaments parametres!";
		qDebug() << "Example: " << argv[0] << " tournaments.txt";
		qDebug() << "======================================================";
	}
	
	std::ifstream file(argv[1]);
	char str[500], *p_title, *p_plr1, *p_lvl1, *p_plr2, *p_lvl2, *p_cnt;
	int level1, level2, cnt;
	
	while (!file.eof()) {
		file.getline(str, sizeof(str));
		// заголовок
		p_title = strtok(str, "\t\n\r");
		if (!p_title) continue;
		std::string title(p_title);
		// игрок 1
		p_plr1 = strtok(NULL, "\t\n\r");
		if (!p_plr1) continue;
		p_lvl1 = strtok(NULL, "\t\n\r");
		if (!p_lvl1) continue;
		level1 = atoi(p_lvl1);
		if (level1 <= 0 || level1 > 12) continue;
		// игрок 1
		p_plr2 = strtok(NULL, "\t\n\r");
		if (!p_plr2) continue;
		p_lvl2 = strtok(NULL, "\t\n\r");
		if (!p_lvl2) continue;
		level2 = atoi(p_lvl2);
		if (level2 <= 0 || level2 > 12) continue;
		// кол-во партий
		p_cnt = strtok(NULL, "\t\n\r");
		if (!p_cnt) continue;
		cnt = atoi(p_cnt);
		if (cnt <= 0) continue;
		// запускаем турнир
		new Tournament(title, Ai_Player::createAiPlayer(p_plr1, level1), Ai_Player::createAiPlayer(p_plr2, level2), cnt);
	}
	
	return app.exec();
}

