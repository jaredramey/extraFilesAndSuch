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

	Point DeltaTime;

	std::vector<Agent*> myAgents;
	myAgents.push_back(TestWander);
	myAgents.push_back(TestWander2);
	myAgents.push_back(TestWander3);
	myAgents.push_back(TestWander4);
	myAgents.push_back(TestWander5);

	std::vector<SteeringBehavior*> TestList;
	TestList.push_back(new Wander());
	TestList[0]->weight = 1;

	std::vector<SteeringBehavior*> OtherList;
	OtherList.push_back(new Cohesion(myAgents[0]));

	myAgents[0]->SetBehaviors(TestList);
	myAgents[1]->SetBehaviors(OtherList);
	myAgents[2]->SetBehaviors(OtherList);
	myAgents[3]->SetBehaviors(OtherList);
	myAgents[4]->SetBehaviors(OtherList);

    //Game Loop
    do
    {
		ClearScreen();
		DeltaTime.x = GetDeltaTime();
		DeltaTime.y = GetDeltaTime();

		for (int i = 0; i < myAgents.size(); i++)
		{
			myAgents[i]->CheckNeighbors(myAgents);
			myAgents[i]->UpdateAgent(new Seperation(myAgents[i]), myAgents[i], DeltaTime);
		}

		for (int i = 0; i < myAgents.size(); i++)
		{
			MoveSprite(myAgents[i]->textureHandler, myAgents[i]->Pos.x, myAgents[i]->Pos.y);
			DrawSprite(myAgents[i]->textureHandler);
		}

		DrawLine(TestWander->Pos.x, TestWander->Pos.y, (TestWander->Pos.x + (TestWander->Velocity.x * 100)), (TestWander->Pos.y + (TestWander->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander2->Pos.x, TestWander2->Pos.y, (TestWander2->Pos.x + (TestWander2->Velocity.x * 100)), (TestWander2->Pos.y + (TestWander2->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander3->Pos.x, TestWander3->Pos.y, (TestWander3->Pos.x + (TestWander3->Velocity.x * 100)), (TestWander3->Pos.y + (TestWander3->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander4->Pos.x, TestWander4->Pos.y, (TestWander4->Pos.x + (TestWander4->Velocity.x * 100)), (TestWander4->Pos.y + (TestWander4->Velocity.y * 100)), SColour(255, 0, 0, 255));
		DrawLine(TestWander5->Pos.x, TestWander5->Pos.y, (TestWander5->Pos.x + (TestWander5->Velocity.x * 100)), (TestWander5->Pos.y + (TestWander5->Velocity.y * 100)), SColour(255, 0, 0, 255));

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
