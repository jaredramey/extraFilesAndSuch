//////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "GameDefs.h"
#include "Game.h"
#include "Cat.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>

int main( int argc, char* argv[] )
{	
	Initialise(iScreenWidth, iScreenHeight, false, "Cowboy Cats!");

	Cat cats[4];
	cats[0].initWithFile("./images/cat1.png");
	cats[1].initWithFile("./images/cat2.png");
	cats[2].initWithFile("./images/cat3.png");
	cats[3].initWithFile("./images/cat4.png");

	int background = CreateSprite("./images/background.png", iScreenWidth, iScreenHeight, false);
	MoveSprite(background, 0, 0);

	Game game;

	for(int i=0; i<4; i++) {
		game.attachObserver(&cats[i]);
	}

	float delta = 0;
	do 
	{
		ClearScreen();

		delta = GetDeltaTime();

		game.update(delta);

		DrawSprite(background);

		for(int i=0; i<4; i++) {
			cats[i].draw();
		}

	} while ( FrameworkUpdate() == false );

	DestroySprite(background);
	for(int i=0; i<4; i++) {
		game.detachObserver(&cats[i]);
		cats[i].destroy();
	}

	Shutdown();

	return 0;
}

