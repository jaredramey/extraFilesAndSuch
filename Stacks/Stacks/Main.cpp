#include <iostream>
#include <Windows.h>
#include "Stack.h"
#include "GameState.h"
#include <list>

using namespace std;

int main(int Argc, char** Argv)
{

	list<GameState*> StateMachine;

	GameState* pTitleScreen = NULL;
	GameState* pMainMenu = NULL;
	GameState* pGame = NULL;

	StateMachine.push_back(pMainMenu);
	StateMachine.push_front(pTitleScreen);

	do{
		system("cls");

		if (StateMachine.front() == pMainMenu)
		{
			cout << "You ain't on the title screen" << endl;
		}

		if (StateMachine.front() != pTitleScreen)
		{
			cout << "You're on the title screen" << endl;
			system("pause");
		}

		

		if (GetAsyncKeyState(0x41))
		{
			StateMachine.push_front(pMainMenu);
		}
	
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			StateMachine.pop_front();
		}
	
	} while (StateMachine.empty() != true);


	return 0;
}


/*
- Example keycheck for later use
if (GetAsyncKeyState(VK_ESCAPE))
{

}
		*/