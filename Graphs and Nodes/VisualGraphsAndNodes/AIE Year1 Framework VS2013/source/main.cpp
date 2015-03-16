#include <iostream>
#include "AIE.h"
#include "Graph.h"
#include "GraphNode.h"
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "AI_Test");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	Graph TestGraph = Graph();
	Agent* TestSeek = new Agent(100, 100, 96, 48, CreateSprite("./images/crate_sideup.png", 96, 48, true), 1.0f);
	Agent* TestDummy = new Agent(200, 200, 96, 48, CreateSprite("./images/cannon.png", 96, 48, true), 0.5f);
	Agent* TestWander = new Agent(400, 300, 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 2.5f);
	Point DeltaTime;

	//For randomize sake
	srand(time(NULL));

    //Game Loop
    do
    {
		ClearScreen();
		DeltaTime.x = GetDeltaTime();
		DeltaTime.y = GetDeltaTime();

		TestSeek->UpdateAgent(new Seek(TestWander), TestDummy, DeltaTime);
		//TestDummy->UpdateAgent(new Flee(TestSeek), TestSeek, DeltaTime);
		TestWander->UpdateAgent(new Wander(), TestSeek, DeltaTime);

		MoveSprite(TestSeek->textureHandler, TestSeek->Pos.x, TestSeek->Pos.y);
		DrawSprite(TestSeek->textureHandler);

		/*MoveSprite(TestDummy->textureHandler, TestDummy->Pos.x, TestDummy->Pos.y);
		DrawSprite(TestDummy->textureHandler);*/

		MoveSprite(TestWander->textureHandler, TestWander->Pos.x, TestWander->Pos.y);
		DrawSprite(TestWander->textureHandler);

		DrawLine(TestWander->Pos.x, TestWander->Pos.y, (TestWander->Pos.x + (TestWander->Velocity.x*100)), (TestWander->Pos.y + (TestWander->Velocity.y*100)), SColour(255, 0, 0, 255));

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
