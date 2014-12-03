#include <iostream>

using namespace std;

class GameState
{
public:
	enum GAMESTATE{
		eMainMenu,
		eGameState,
		eOptions,
		eQuit

	};

	GameState();
	~GameState();
	

};