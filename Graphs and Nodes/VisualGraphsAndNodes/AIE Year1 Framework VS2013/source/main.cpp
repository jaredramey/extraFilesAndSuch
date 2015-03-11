#include <iostream>
#include "AIE.h"
#include "Graph.h"
#include "GraphNode.h"
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "AI_Test");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	Graph TestGraph = Graph();
	Agent* TestSeek = new Agent(100, 100, 96, 48, CreateSprite("./images/crate_sideup.png", 96, 48, true), 3);
	Agent* TestDummy = new Agent(700, 500, 96, 48, CreateSprite("./images/cannon.png", 96, 48, true), 3);
	Point DeltaTime;

	int frame = 0;

    //Game Loop
    do
    {
		ClearScreen();
		DeltaTime.x = GetDeltaTime();
		DeltaTime.y = GetDeltaTime();

		TestSeek->UpdateAgent(new Seek(TestDummy), TestDummy, DeltaTime);
		TestDummy->UpdateAgent(new Flee(TestSeek), TestSeek, DeltaTime);

		MoveSprite(TestSeek->textureHandler, TestSeek->Pos.x, TestSeek->Pos.y);
		DrawSprite(TestSeek->textureHandler);

		TestDummy->ControlOveride();

		MoveSprite(TestDummy->textureHandler, TestDummy->Pos.x, TestDummy->Pos.y);
		DrawSprite(TestDummy->textureHandler);


    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
