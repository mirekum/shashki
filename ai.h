#ifndef _AI_H_
	#define _AI_H_
	
	#define MINMAX_END 2000000
	
	// класс "Игрок-компьютер"
	class AI_PLAYER: public PLAYER {
	protected:
		// альфа-бета-усечение
		const static int ab = 0;
		// глубина просмотра (кол-во полуходов) - должна быть чётной
		int max_step;
		// статистическая оценочная функция
		virtual int srf(BOARD board);
	public:
		// конструктор класса
		AI_PLAYER() {max_step = 4;}
		// выполнение хода
		virtual MOVE move(BOARD board);
	protected:
		// выбор наилучшего хода
		virtual int choose(BOARD board, int _type, MOVE *res, int step = 0, int last = -MINMAX_END, bool smflag = true);
	};
	
	// немного другой игрок-компьютер
	class AI_PLAYER2: public AI_PLAYER {
	public:
		AI_PLAYER2() {max_step = 4;}
	};
	
#endif

