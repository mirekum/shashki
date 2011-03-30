#include <QtCore>
#include "tournament.h"
#include "Players/ai_player.h"

// entry point
int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	
	new Tournament("Tournament #1 (2 vs 2)", new Ai_Player(2), new Ai_Player(2), 20);
	new Tournament("Tournament #2 (4 vs 2)", new Ai_Player(4), new Ai_Player(2), 20);
	new Tournament("Tournament #3 (2 vs 4)", new Ai_Player(2), new Ai_Player(4), 20);
	new Tournament("Tournament #4 (4 vs 4)", new Ai_Player(4), new Ai_Player(4), 20);
	
	return app.exec();
}

