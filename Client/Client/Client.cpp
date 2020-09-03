// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Client.h"
#include<iostream>
#include<afxsock.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Common.h"
#include "Game.h"
#include "Board.h"
//#include "Play.h"
#include"Player.h"
P Game::a1;
P Game::a2;
int Game::mark[15][15] = { 0 };
void Play();
static int BOARD_SIZE = 15;
static int LEFT = 50;
static int TOP = 4;
// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
	int nRetCode = 0;
	HMODULE hModule = ::GetModuleHandle(nullptr);
	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			if (AfxSocketInit() == 0)
			{
				cout << "Failed to init socket library." << endl;
				return false;
			}
			else
			{
				Play();
			}

		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode;
}


void Play()
{
	CSocket ClientSocket;
	ClientSocket.Create();
	wstring addr;
	Common::setTextColor(226);
	cout << "Please enter the IP address you want to connect:";
	wcin >> addr;
	LPCWSTR ipAddr = addr.c_str();
	if (ClientSocket.Connect(ipAddr,1234)!=0)
	{
		cout << "Connect to the server successfully!" << endl;
		Common::fixConsoleWindow();
		Common::removeScrollbar();
		Game g(BOARD_SIZE, LEFT, TOP);
		Common::hideCursor(TRUE);
		Common::gameName(243);
		g.startGame();
		int a[15][15] = { 0 };
		int turn = g.getTurn();
		int x, y;
		int move1, move2;
		int pWhowin = 2;
		COORD pos = { g.getBoard()->getXAt(0,0),g.getBoard()->getYAt(0,0) };
		while (g.isContinue())
		{
			ClientSocket.Receive(&turn, 4, 0);
			ClientSocket.Receive(&move1, 4, 0);
			ClientSocket.Receive(&move2, 4, 0);
			if (turn)
			{
				Common::gotoXY(20, 20);
				Common::setTextColor(244);
				cout << "Player 1: " << "X" << endl;
			}
			else
			{
				Common::gotoXY(130, 20);
				Common::setTextColor(243);
				cout << "Player 2: " << "O" << endl;
			}
			ClientSocket.Receive(&pWhowin, 4, 0);
			if (pWhowin == -1)
			{
				if (turn)  Common::Result("YouWon.txt");
				else Common::Result("YouLost.txt");
				cout << "\n								Restarting new game..." << endl;
				Sleep(3000);
				system("cls");
				Play();
				break;
			}
			if (pWhowin == 1)
			{
				if (!turn) Common::Result("YouWon.txt");
				else Common::Result("YouLost.txt");
				cout << "\n								Restarting new game..." << endl;
				Sleep(3000);
				system("cls");
				Play();
				break;
			}
			if (pWhowin == 0)
			{
				Common::Result("Draw.txt");
				cout << "\n								Restarting new game..." << endl;
				Sleep(3000);
				system("cls");
				Play();
				break;
			}
			if (pWhowin == 2)
			{
				g.setTurn(turn);
				if (ClientSocket.Receive((char*)Game::mark, sizeof(Game::mark), 0))
				{
					g.getBoard()->setBoard(Game::mark);
					g.getBoard()->drawBoard();
					Game::a1.SetMove(move1);
					Game::a2.SetMove(move2);
					if (turn)
					{
						Common::setTextColor(244);
						Game::a1.drawInfo("  You", 10, 5);
						Common::setTextColor(243);
						Game::a2.drawInfo("Opponent", 130, 5);
					}
					else
					{
						Common::setTextColor(244);
						Game::a1.drawInfo("Opponent", 10, 5);
						Common::setTextColor(243);
						Game::a2.drawInfo("  You", 130, 5);
					}
					ClientSocket.Receive(&x, 4, 0);
					ClientSocket.Receive(&y, 4, 0);
					Common::gotoXY(x, y);
				}
				int played = 1;
				while(1)
				{
					ClientSocket.Receive(&played, 4, 0);
					if (played !=0 )
					{
						char c = _getch();
						int lenh = toupper(c);
						if (ClientSocket.Send(&lenh, sizeof(lenh), 0))
						{
							//if (ClientSocket.Receive(&lenh, sizeof(lenh), 0))
							//{
								g.SetCommand(lenh);
								int command = g.getCommand();
								if (command == 27)
								{
									Common::Result("YouLost.txt");
									Common::gotoXY(30, 30);
									exit(0);
									break;
								}
								if (command == 'A' || command == 75)
								{
									pos = g.moveLeft();
									Common::gotoXY(pos.X, pos.Y);
									ClientSocket.Send(&pos.X, 4, 0);
									ClientSocket.Send(&pos.Y, 4, 0);

								}
								if (command == 'S' || command == 80)
								{
									pos = g.moveDown();
									Common::gotoXY(pos.X, pos.Y);
									ClientSocket.Send(&pos.X, 4, 0);
									ClientSocket.Send(&pos.Y, 4, 0);

								}
								if (command == 'D' || command == 77)
								{
									pos = g.moveRight();
									Common::gotoXY(pos.X, pos.Y);
									ClientSocket.Send(&pos.X, 4, 0);
									ClientSocket.Send(&pos.Y, 4, 0);

								}
								if (command == 'W' || command == 72)
								{
									pos = g.moveUp();
									Common::gotoXY(pos.X, pos.Y);
									ClientSocket.Send(&pos.X, 4, 0);
									ClientSocket.Send(&pos.Y, 4, 0);

								}
								if (command == 13)
								{
									COORD temp = g.getBoard()->getCOORD(pos.X, pos.Y);
									played = g.getBoard()->getCheck(temp.X, temp.Y);
									
									if (played == 0)
									{
										ClientSocket.Send(&played, 4, 0);
											if (turn)
											{
												g.getBoard()->setCheckAt(temp.X, temp.Y, -1);
											}
											else
											{
												g.getBoard()->setCheckAt(temp.X, temp.Y, 1);
											}
											g.updateBoard();
											g.getBoard()->drawBoard();
											if (turn) Game::a1.IncreaseMove();
											else Game::a2.IncreaseMove();
											if (turn)
											{
												Common::setTextColor(244);
												Game::a1.drawInfo("  You", 10, 5);
												Common::setTextColor(243);
												Game::a2.drawInfo("Opponent", 130, 5);
											}
											else
											{
												Common::setTextColor(244);
												Game::a1.drawInfo("Opponent", 10, 5);
												Common::setTextColor(243);
												Game::a2.drawInfo("  You", 130, 5);
											}
											Common::setTextColor(244);
											move1 = Game::a1.getMove();
											move2 = Game::a2.getMove();
											ClientSocket.Send(&pos.X, 4, 0);
											ClientSocket.Send(&pos.Y, 4, 0);
											ClientSocket.Send(&move1, 4, 0);
											ClientSocket.Send(&move2, 4, 0);
											g.updateBoard();
											ClientSocket.Send((char*)Game::mark, sizeof(Game::mark), 0);
											pWhowin = g.processFinish();
											ClientSocket.Send(&pWhowin, 4, 0);
											break;
									}
									if (played !=0)
									{
										ClientSocket.Send(&played, 4, 0);
										move1 = Game::a1.getMove();
										move2 = Game::a2.getMove();
										ClientSocket.Send(&pos.X, 4, 0);
										ClientSocket.Send(&pos.Y, 4, 0);
										ClientSocket.Send(&move1, 4, 0);
										ClientSocket.Send(&move2, 4, 0);
										g.updateBoard();
										ClientSocket.Send((char*)Game::mark, sizeof(Game::mark), 0);
										pWhowin = g.processFinish();
										ClientSocket.Send(&pWhowin, 4, 0);
										break;
									}
								}
							//}
						}
					}
					if (played == 0) break;
				}		
			}
		}
		ClientSocket.Close();
	}
	else
	{
	cout << "Server not found" << endl;
	exit(0);
	}
}
