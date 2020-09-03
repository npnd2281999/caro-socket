
#ifndef _PLAYER_H
#define _PLAYER_H
#include"Common.h"
#include <string>

typedef class Player
{
private:
	int move;
public:
	Player();
	void drawInfo(string, int, int);
	int getMove();
	void IncreaseMove();
	void SetMove(const int);
} P;

#endif
