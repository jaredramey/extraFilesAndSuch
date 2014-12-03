#include <iostream>
#include "Stack.h"
#include "GameState.h"

using namespace std;

int main(int Argc, char** Argv)
{
	bool loop = true;

	MyStack<GameState*> StateMachine;

	GameState* pTitleScreen = NULL;
	GameState* pMainMenu = NULL;
	GameState* pGame = NULL;

	StateMachine.Push(pTitleScreen);

	do{
	
	
	} while (loop != false);


	system("pause");
	return 0;
}