#ifndef _BOARD_H_
	#define _BOARD_H_
	
	// фигуры на доске
	#define WHITE      +1 // белая шашка
	#define WHITE_KING +2 // белая дамка
	#define BLACK      -1 // чёрная шашка
	#define BLACK_KING -2 // чёрная дамка
	
	#define ISWIN_WHITE 1 // выиграли белые
	#define ISWIN_BLACK 2 // выиграли чёрные
	#define ISWIN_DRAW  3 // ничья
	#define ISWIN_GAME  0 // игра не закончилась
	
	// класс, описывающий клетку доски
	class CELL {
	public:
		int x, y;
		// конструкторы класса
		CELL(): x(0), y(0) {};
		CELL(int _x, int _y): x(_x), y(_y) {};
	};
	
	// класс, описывающий ход с одной клетки на другую
	class MOVE {
	public:
		CELL from, to;
		// конструкторы класса
		MOVE() {};
		MOVE(CELL _from, CELL _to) {from = _from; to = _to;};
	};
	
	// класс, описывающий флаги хода
	class CANMOVE {
	public:
		int eat, king;
		// конструкторы класса
		CANMOVE(): eat(0), king(0) {};
		CANMOVE(int _eat, int _king): eat(_eat), king(_king) {};
	};
	
	// класс "Доска для игры в шашки"
	class BOARD {
	public:
		// размер доски
		const static int size = 8;
	protected:
		// кол-во белых и чёрных фигур
		int b, w;
		// кол-во белых и чёрных дамок
		int bk, wk;
		// массив клеток доски; 0 - пусто, >0 - белые, <0 - чёрные
		char cells[size][size]; // [x][y]; x - столбец, y - строка
		// флаг, указывающий на первый неполный полуход
		bool ufirst;
		// флаг, указывающий на факт съедения в прошлом неполном полуходе
		bool ueaten;
		// цвет игрока на текущий полуход
		int utype;
		// заблокированная на текущий полуход фигура
		CELL ublocked;
	public:
		// конструктор класса
		explicit BOARD();
		// начало полухода
		void start_move(int type);
		// выполнение неполного полухода
		int move(MOVE _move);
		int move(CELL /* from */ a, CELL /* to */ z);
		int move(int x1, int y1, int x2, int y2);
		// возможность неполного полухода
		int can_move(MOVE move, CANMOVE *flags = NULL, int _type = 0);
		int can_move(CELL /* from */ a, CELL /* to */ z, CANMOVE *flags = NULL, int _type = 0);
		int can_move(int x1, int y1, int x2, int y2, CANMOVE *flags = NULL, int _type = 0);
		// возможность продолжения хода
		int can_move();
		// получение набора возможных неполных полуходов для заданной точки
		int moves(CELL cell, CELL *arr = NULL);
		// проверка конца игры
		int is_win();
		// вывод доски на экран
		friend std::ostream& operator<< (std::ostream &cout, BOARD &board);
		// флаг, указывающий на первый неполный полуход
		int first() {return ufirst;}
		// количество белых фигур
		int white() {return w;}
		// количество чёрных фигур
		int black() {return b;}
		// количество белых дамок
		int white_king() {return wk;}
		// количество чёрных дамок
		int black_king() {return bk;}
	};
	
#endif
