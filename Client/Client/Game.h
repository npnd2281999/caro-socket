#ifndef _Game_h
#define _Game_h

#include "Board.h"
#include <conio.h>
#include"Player.h"


class Game
{
protected:
	Board* b;
	bool turn;
	int x; int y;
	int command;
	bool loop;
public:
	static P a1;
	static P a2;
	Game(int, int, int);
	~Game();
	int getCommand();
	bool isContinue();
	void startGame();
	void exitGame();
	int processFinish();
	COORD moveRight();
	COORD moveLeft();
	COORD moveUp();
	COORD moveDown();
	void SetCommand(int);
	Board* getBoard();
	static int mark[15][15];
	void setTurn(bool);
	void updateBoard();
	bool getTurn();
};

#endif
