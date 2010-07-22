#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#include <QtCore>
	#include "Model/board.h"
	
	enum PLAYER_TYPE {HUMAN, AI, NETWORK, BLUETOOTH};
	
	class Player: public QObject {
		Q_OBJECT
	public:
		const static unsigned int maxFiguresNumber = BOARD::size*2;
	protected:
		// player color
		COLOR color;
		// choosen move
		MOVE result;
	public:
		Player() {color = NONE;}
		// sets player color (white or black)
		void setColor(COLOR _color) {color = _color;};
		// get player type
		virtual PLAYER_TYPE type() = 0;
		// choose partial half-move
		virtual void execMove(BOARD board) = 0;
		// get result of partial half-move
		MOVE getMove() {return result;}
		// set player level (for AI players)
		virtual void setLevel(int level) {};
		// give last moves array to player
		virtual void giveLastMoves(MOVE lastMove[maxFiguresNumber]) {
			int i=0;
			while(i<maxFiguresNumber){
				lastMove[i].from.x=0;
				lastMove[i].from.y=0;
				lastMove[i].to.x=0;
				lastMove[i].to.y=0;
				i++;
			}
		};
	signals:
		void moveExecuted();
	};
	
#endif

