#ifndef _GAME_H_
	#define _GAME_H_
	
	// класс "Игра в шашки"
	class GAME {
	protected:
		// доска для игры в шашки
		BOARD board;
		// игрок белыми
		PLAYER *wp;
		// игрок чёрными
		PLAYER *bp;
	public:
		// конструктор класса
		explicit GAME(int w, int b);
	protected:
		// создание игрока
		PLAYER* createPlayer(int plr);
		// игровой цикл
		void process();
		// сообщаем о результатах
		void result(int res);
	};
	
#endif

