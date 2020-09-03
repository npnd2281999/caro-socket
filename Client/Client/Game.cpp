#include "Game.h"

Game::Game(int pSize, int pLeft, int pTop)
{
	b = new Board(pSize, pLeft, pTop);
	loop = true;
	turn = true;
	command = -1;
	x = pLeft, y = pTop;
	a1 = P();
	a2 = P();
}

Game::~Game()
{
	delete b;
}

int Game::getCommand()
{
	return command;
}

bool Game::isContinue()
{
	return loop;
}


void Game::startGame()
{
	system("cls");
	b->resetData();
	Game::a1.SetMove(0);
	Game::a2.SetMove(0);
	/*Common::setTextColor(244);
	Game::a1.drawInfo("Player 1", 10, 5);
	Common::setTextColor(243);
	Game::a2.drawInfo("Player 2", 130, 5);*/
	b->drawBoard();
	x = b->getXAt(0, 0);
	y = b->getYAt(0, 0);
}

void Game::exitGame()
{
	system("cls");
	loop = false;
}


int Game::processFinish()
{
	Common::gotoXY(0, b->getYAt(b->getSize() - 1, b->getSize() - 1) + 2);
	int pWhoWin = b->testBoard(x, y);
	Common::gotoXY(x, y);
	return pWhoWin;
}

COORD Game::moveRight()
{
	if (x < b->getXAt(b->getSize() - 1, b->getSize() - 1))
	{
		x += 4;
		//Common::gotoXY(x, y);
	}
	COORD pos;
	pos.X = x;
	pos.Y = y;
	return pos;
}

COORD Game::moveLeft()
{
	if (x > b->getXAt(0, 0))
	{
		x -= 4;
		//Common::gotoXY(x, y);
	}
	COORD pos;
	pos.X = x;
	pos.Y = y;
	return pos;
}

COORD Game::moveUp()
{
	if (y > b->getYAt(0, 0))
	{
		y -= 2;
		//Common::gotoXY(x, y);
	}
	COORD pos;
	pos.X = x;
	pos.Y = y;
	return pos;
}

COORD Game::moveDown()
{
	if (y < b->getYAt(b->getSize() - 1, b->getSize() - 1))
	{
		y += 2;
		//Common::gotoXY(x, y);
	}
	COORD pos;
	pos.X = x;
	pos.Y = y;
	return pos;
}

void Game::SetCommand(int cmd)
{
	command = cmd;
}

Board* Game::getBoard()
{
	return b;
}

void Game::updateBoard()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			mark[i][j] = b->getCheck(i, j);
		}
	}
}

void Game::setTurn(bool pTurn)
{
	turn = pTurn;
}

bool Game::getTurn()
{
	return turn;
}

