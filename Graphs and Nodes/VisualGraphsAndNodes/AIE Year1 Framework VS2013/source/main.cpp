#include <iostream>
#include <list>
#include "AIE.h"
#include "Graph.h"
#include "GraphNode.h"
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"
#include "Seperation.h"
#include "Cohesion.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "AI_Test");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//For randomize sake
	srand(time(NULL));

	Agent* TestWander = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander2 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander3 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander4 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander5 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander6 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander7 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander8 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);
	Agent* TestWander9 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.5f);

	Point DeltaTime;

	std::vector<Agent*> myAgents;
	myAgents.push_back(TestWander);
	myAgents.push_back(TestWander2);
	myAgents.push_back(TestWander3);
	myAgents.push_back(TestWander4);
	myAgents.push_back(TestWander5);
	myAgents.push_back(TestWander6);
	myAgents.push_back(TestWander7);
	myAgents.push_back(TestWander8);
	myAgents.push_back(TestWander9);

	std::vector<SteeringBehavior*> TestList;
	TestList.push_back(new Wander());
	TestList[0]->weight = 1;

	std::vector<SteeringBehavior*> OtherList;
	OtherList.push_back(new Cohesion(myAgents));
	//OtherList.push_back(new Seperation(myAgents));

	for (int i = 0; i < myAgents.size(); i++)
	{
		myAgents[i]->SetBehaviors(OtherList);
	}

    //Game Loop
    do
    {
		ClearScreen();
		DeltaTime.x = GetDeltaTime();
		DeltaTime.y = GetDeltaTime();

		for (int i = 0; i < myAgents.size(); i++)
		{
			myAgents[i]->CheckNeighbors(myAgents);
			myAgents[i]->UpdateAgent(new Seperation(myAgents), myAgents[i], DeltaTime);
		}

		for (int i = 0; i < myAgents.size(); i++)
		{
			myAgents[i]->NeighborList.clear();
			MoveSprite(myAgents[i]->textureHandler, myAgents[i]->Pos.x, myAgents[i]->Pos.y);
			DrawSprite(myAgents[i]->textureHandler);
		}

		for (int i = 0; i < myAgents.size(); i++)
		{
			DrawLine(myAgents[i]->Pos.x, myAgents[i]->Pos.y, (myAgents[i]->Pos.x + (myAgents[i]->Velocity.x * 100)), (myAgents[i]->Pos.y + (myAgents[i]->Velocity.y * 100)), SColour(255, 0, 0, 255));
		}

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
