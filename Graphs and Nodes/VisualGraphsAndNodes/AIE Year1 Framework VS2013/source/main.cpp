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
#include "Allingment.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "AI_Test");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//For randomize sake
	srand(time(NULL));

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//-----------------------------------------------------------------------------|| For AI and Behaviors ||---------------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

	//create all the agnets I need for flocking, randomize the position for more interesting results
	Agent* TestWander = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander2 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander3 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander4 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander5 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander6 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander7 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander8 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander9 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander10 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander11 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander12 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander13 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander14 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	Agent* TestWander15 = new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f);
	//Ect Agents for everything else

	//create a point for Delta time so I can easily use it later
	Point DeltaTime;

	//create vector of agents to make flocking easier to manage
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
	myAgents.push_back(TestWander10);
	myAgents.push_back(TestWander11);
	myAgents.push_back(TestWander12);
	myAgents.push_back(TestWander13);
	myAgents.push_back(TestWander14);
	myAgents.push_back(TestWander15);

	//behavior list to test out anything that's not flocking
	std::vector<SteeringBehavior*> TestList;
	TestList.push_back(new Wander());
	TestList[0]->weight = 1;

	//behavior list for flocking
	std::vector<SteeringBehavior*> OtherList;
	OtherList.push_back(new Cohesion(myAgents));
	OtherList.push_back(new Allingment(myAgents));
	OtherList.push_back(new Seperation(myAgents));

	//weight of different behaviors in flocking, in the end they should all equal out to 1.0 when added up
	//Cohesion
	OtherList[0]->weight = 0.2f;
	//Allingment
	OtherList[1]->weight = 0.5f;
	//Seperation
	OtherList[2]->weight = 0.3f;

	//set the agents behavior lists to the flocking list
	for (int i = 0; i < myAgents.size(); i++)
	{
		myAgents[i]->SetBehaviors(OtherList);
	}

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//-----------------------------------------------------------------------------|| For AI and Behaviors ||---------------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

	//==============================================================================================================================================================================================================================\\

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//---------------------------------------------------------------------------|| For Graphs and Path Finding ||----------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

	Graph TestGraph = Graph();
	TestGraph.CreateGraph();
	TestGraph.AStarPathTest(0, 9);

	//create the agent that will be moving on the graph
	Agent* GraphAI = new Agent(TestGraph.ClosedList[0]->x, TestGraph.ClosedList[0]->y, 96, 48, CreateSprite("./images/cannon.png", 96, 48, true), 0.25f);
	GraphAI->GetPath(TestGraph.ClosedList);

	int frame = 0;

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//---------------------------------------------------------------------------|| For Graphs and Path Finding ||----------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//


    //Game Loop
    do
    {
		ClearScreen();
		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
		//-----------------------------------------------------------------------------|| For AI and Behaviors ||---------------------------------------------------------------------------------------------------------------\\
		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//
		//Set delta time
		DeltaTime.x = GetDeltaTime();
		DeltaTime.y = GetDeltaTime();

		//Update the agents
		for (int i = 0; i < myAgents.size(); i++)
		{
			myAgents[i]->CheckNeighbors(myAgents);
			myAgents[i]->UpdateAgent(new Seperation(myAgents), myAgents[i], DeltaTime);
		}
		//More update stuff
		for (int i = 0; i < myAgents.size(); i++)
		{
			myAgents[i]->NeighborList.clear();
			MoveSprite(myAgents[i]->textureHandler, myAgents[i]->Pos.x, myAgents[i]->Pos.y);
			DrawSprite(myAgents[i]->textureHandler);
		}

		//Draw line just to see what the velocity is and where the agent is heading
		for (int i = 0; i < myAgents.size(); i++)
		{
			DrawLine(myAgents[i]->Pos.x, myAgents[i]->Pos.y, (myAgents[i]->Pos.x + (myAgents[i]->Velocity.x * 100)), (myAgents[i]->Pos.y + (myAgents[i]->Velocity.y * 100)), SColour(255, 0, 0, 255));
		}
		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
		//-----------------------------------------------------------------------------|| For AI and Behaviors ||---------------------------------------------------------------------------------------------------------------\\
		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

		//============================================================================================================================================================================================================================\\

		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
		//---------------------------------------------------------------------------|| For Graphs and Path Finding ||----------------------------------------------------------------------------------------------------------\\
		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

		/*TestGraph.CheckMouseClick();
		TestGraph.DrawGraph();
		GraphAI->MoveOnGraphPath(0.25f);*/

		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
		//---------------------------------------------------------------------------|| For Graphs and Path Finding ||----------------------------------------------------------------------------------------------------------\\
		//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
