// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Server.h"
#include<afxsock.h>
#include<iostream>
#include<conio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int InitServer();

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
			if (AfxSocketInit() == false)
			{
				cout << "Failed to init the socket library" << endl;
				return false;
			}
			else
			{
				while (1)
				{
					InitServer();
					cout << "Press any key to continue...";
					_getch();
				}
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

int InitServer()
{
	system("cls");
	CSocket ServerSocket;
	if (ServerSocket.Create(1234, SOCK_STREAM, NULL) == false)
	{
		cout << "Created Server failed." << endl;
		cout << ServerSocket.GetLastError() << endl;
		return false;
	}
	else
	{
		cout << "Created Server Successfully" << endl << endl;
		cout << "Waiting for Players Connect...." << endl;
		if (ServerSocket.Listen(2) == false)
		{
			cout << "Khong the lang nghe tren port nay" << endl;
			ServerSocket.Close();
			return false;
		}
		CSocket Connector[2];
		if (ServerSocket.Accept(Connector[0]))
		{
			cout << "Player 1 Connect Successfully" << endl;
			cout << "Waiting for Player 2...." << endl;
			if (ServerSocket.Accept(Connector[1]))
			{
				cout << "Player 2 Connect Successfully" << endl;
				cout << "Game start" << endl;
				int lenh1 = 0, lenh2 = 0;
				int a[15][15] = { 0 };
				int x = 52, y = 5;
				int turn = 1;
				int move1 = 0, move2 = 0;
				int whoWin = 2;
				do
				{
					if (whoWin == 1 || whoWin == 0)
					{
						if (lenh1 == 27)
						{
							Connector[1].Send(&turn, 4, 0);
							Connector[1].Send(&move1, 4, 0);
							Connector[1].Send(&move2, 4, 0);
							Connector[1].Send(&whoWin, 4, 0);
						}
						else
						{
							Connector[0].Send(&turn, 4, 0);
							Connector[0].Send(&move1, 4, 0);
							Connector[0].Send(&move2, 4, 0);
							Connector[0].Send(&whoWin, 4, 0);
						}
						break;
					}
					 if (whoWin == -1 || whoWin == 0)
					{
						 if (lenh2 == 27)
						 {
							 Connector[0].Send(&turn, 4, 0);
							 Connector[0].Send(&move1, 4, 0);
							 Connector[0].Send(&move2, 4, 0);
							 Connector[0].Send(&whoWin, 4, 0);
						 }
						 else
						 {
							 Connector[1].Send(&turn, 4, 0);
							 Connector[1].Send(&move1, 4, 0);
							 Connector[1].Send(&move2, 4, 0);
							 Connector[1].Send(&whoWin, 4, 0);
						 }
						
						break;
					}
					if (whoWin == 2)
					{
						if (turn)
						{
							int played1 = 1;
							while (played1 != 0)
							{
								Connector[0].Send(&turn, 4, 0);
								Connector[0].Send(&move1, 4, 0);
								Connector[0].Send(&move2, 4, 0);
								Connector[0].Send(&whoWin, 4, 0);
								Connector[0].Send((char*)a, sizeof(a), 0);
								Connector[0].Send(&x, 4, 0);
								Connector[0].Send(&y, 4, 0);
								while (1)
								{
									Connector[0].Send(&played1, 4, 0);
									Connector[0].Receive(&lenh1, 4, 0);
									cout << "Waiting for Player 1 playing..." << endl;
									if (lenh1 == 27)
									{
										played1 = 0;
										whoWin = 1;
										cout << "Player 1 Exits" << endl;
										break;
									}
									if (lenh1 == 'A' || lenh1 == 75)
									{
										Connector[0].Receive(&x, 4, 0);
										Connector[0].Receive(&y, 4, 0);
									}
									if (lenh1 == 'W' || lenh1 == 72)
									{
										Connector[0].Receive(&x, 4, 0);
										Connector[0].Receive(&y, 4, 0);
									}
									if (lenh1 == 'S' || lenh1 == 80)
									{
										Connector[0].Receive(&x, 4, 0);
										Connector[0].Receive(&y, 4, 0);
									}
									if (lenh1 == 'D' || lenh1 == 77)
									{
										Connector[0].Receive(&x, 4, 0);
										Connector[0].Receive(&y, 4, 0);
									}
									if (lenh1 == 13)
									{

										cout << "Player 1 makes a move" << endl;
										Connector[0].Receive(&played1, 4, 0);
										Connector[0].Receive(&x, 4, 0);
										Connector[0].Receive(&y, 4, 0);
										Connector[0].Receive(&move1, 4, 0);
										Connector[0].Receive(&move2, 4, 0);
										Connector[0].Receive((char*)a, sizeof(a), 0);
										Connector[0].Receive(&whoWin, 4, 0);
										break;
									}
								}
								//if (played1 == 0 || lenh1 == 27) break;
							} //while (1);
						}
						else
						{
							int played2 = 1;
							do
							{
								Connector[1].Send(&turn, 4, 0);
								Connector[1].Send(&move1, 4, 0);
								Connector[1].Send(&move2, 4, 0);
								Connector[1].Send(&whoWin, 4, 0);
								Connector[1].Send((char*)a, sizeof(a), 0);
								Connector[1].Send(&x, 4, 0);
								Connector[1].Send(&y, 4, 0);
								while (1)
								{
									Connector[1].Send(&played2, 4, 0);
									Connector[1].Receive(&lenh2, 4, 0);
									cout << "Waiting for Player 2 playing..." << endl;
									if (lenh2 == 27)
									{
										played2 = 0;
										whoWin = -1;
										cout << "Player 2 Exits" << endl;
										break;
									}
									if (lenh2 == 'A' || lenh2 == 75)
									{
										Connector[1].Receive(&x, 4, 0);
										Connector[1].Receive(&y, 4, 0);
									}
									if (lenh2 == 'W' || lenh2 == 72)
									{
										Connector[1].Receive(&x, 4, 0);
										Connector[1].Receive(&y, 4, 0);
									}
									if (lenh2 == 'S' || lenh2 == 80)
									{
										Connector[1].Receive(&x, 4, 0);
										Connector[1].Receive(&y, 4, 0);
									}
									if (lenh2 == 'D' || lenh2 == 77)
									{
										Connector[1].Receive(&x, 4, 0);
										Connector[1].Receive(&y, 4, 0);
									}
									if (lenh2 == 13)
									{
										cout << "Player 2 makes a move" << endl;
										Connector[1].Receive(&played2, 4, 0);
										Connector[1].Receive(&x, 4, 0);
										Connector[1].Receive(&y, 4, 0);
										Connector[1].Receive(&move1, 4, 0);
										Connector[1].Receive(&move2, 4, 0);
										Connector[1].Receive((char*)a, sizeof(a), 0);
										Connector[1].Receive(&whoWin, 4, 0);
										break;
									}

								}
								if (played2 == 0 || lenh2 == 27) break;
							} while (1);
						}
							turn = !turn;
					}
					//if (lenh1 == 27 || lenh2 == 27) break;
				}while (1);
			}
			Connector[0].Close();
			Connector[1].Close();
			ServerSocket.Close();
		}
		else
		{
			Connector[0].Close();
			Connector[1].Close();
			ServerSocket.Close();
		}
	}
}