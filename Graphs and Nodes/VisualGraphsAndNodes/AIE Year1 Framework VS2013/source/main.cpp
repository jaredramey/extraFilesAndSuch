#include <iostream>
#include <list>
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

	//For randomize sake
	srand(time(NULL));

	Graph TestGraph = Graph();
	Agent* TestSeek = new Agent(100, 100, 96, 48, CreateSprite("./images/crate_sideup.png", 96, 48, true), 1.0f);
	Agent* TestDummy = new Agent(200, 200, 96, 48, CreateSprite("./images/cannon.png", 96, 48, true), 0.5f);
	Agent* TestWander = new Agent(400, 300, 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 2.5f);
	Agent* TestWander2 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 1.5f);
	Agent* TestWander3 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 1.5f);
	Agent* TestWander4 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 1.5f);
	Agent* TestWander5 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 1.5f);

	Point DeltaTime;

	std::list<SteeringBehavior*> TestList;
	TestList.emplace_back(new Seek(TestWander));
	TestList.emplace_back(new Wander());

	TestDummy->SetBehaviors(TestList);

    //Game Loop
    do
    {
		ClearScreen();
		DeltaTime.x = GetDeltaTime();
		DeltaTime.y = GetDeltaTime();

		//TestSeek->UpdateAgent(new Seek(TestWander), TestDummy, DeltaTime);
		//TestDummy->UpdateAgent(new Flee(TestSeek), TestSeek, DeltaTime);
		TestWander->UpdateAgent(new Wander(), TestSeek, DeltaTime);
		TestWander2->UpdateAgent(new Wander(), TestSeek, DeltaTime);
		TestWander3->UpdateAgent(new Wander(), TestSeek, DeltaTime);
		TestWander4->UpdateAgent(new Wander(), TestSeek, DeltaTime);
		TestWander5->UpdateAgent(new Wander(), TestSeek, DeltaTime);


		//MoveSprite(TestSeek->textureHandler, TestSeek->Pos.x, TestSeek->Pos.y);
		//DrawSprite(TestSeek->textureHandler);

		/*MoveSprite(TestDummy->textureHandler, TestDummy->Pos.x, TestDummy->Pos.y);
		DrawSprite(TestDummy->textureHandler);*/

		MoveSprite(TestWander->textureHandler, TestWander->Pos.x, TestWander->Pos.y);
		DrawSprite(TestWander->textureHandler);
		MoveSprite(TestWander2->textureHandler, TestWander2->Pos.x, TestWander2->Pos.y);
		DrawSprite(TestWander2->textureHandler);
		MoveSprite(TestWander3->textureHandler, TestWander3->Pos.x, TestWander3->Pos.y);
		DrawSprite(TestWander3->textureHandler);
		MoveSprite(TestWander4->textureHandler, TestWander4->Pos.x, TestWander4->Pos.y);
		DrawSprite(TestWander4->textureHandler);
		MoveSprite(TestWander5->textureHandler, TestWander5->Pos.x, TestWander5->Pos.y);
		DrawSprite(TestWander5->textureHandler);

		DrawLine(TestWander->Pos.x, TestWander->Pos.y, (TestWander->Pos.x + (TestWander->Velocity.x * 100)), (TestWander->Pos.y + (TestWander->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander2->Pos.x, TestWander2->Pos.y, (TestWander2->Pos.x + (TestWander2->Velocity.x * 100)), (TestWander2->Pos.y + (TestWander2->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander3->Pos.x, TestWander3->Pos.y, (TestWander3->Pos.x + (TestWander3->Velocity.x * 100)), (TestWander3->Pos.y + (TestWander3->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander4->Pos.x, TestWander4->Pos.y, (TestWander4->Pos.x + (TestWander4->Velocity.x * 100)), (TestWander4->Pos.y + (TestWander4->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander5->Pos.x, TestWander5->Pos.y, (TestWander5->Pos.x + (TestWander5->Velocity.x * 100)), (TestWander5->Pos.y + (TestWander5->Velocity.y * 100)), SColour(255, 0, 0, 255));

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
