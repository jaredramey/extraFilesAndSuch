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

enum AIMODE
{
	eBehavior,
	eGraphA,
	GraphB
};

//Put my stuff into functions to be called upon in the loop
void AgentBehaviors(std::vector<Agent*> in_myAgents);
void NewAgentAtClick();
void ResetBehaviorAgents(std::vector<Agent*> in_myAgents);
void GraphNodeAI(Graph in_TestGraph, Agent* in_Agent);
void ResetGraphAI(Graph in_TestGraph, Agent* in_Agent);
void NewNodeAtClick();

//create a point for Delta time so I can easily use it later
Point DeltaTime;

std::vector<Agent*> myAgents;
std::vector<SteeringBehavior*> OtherList;
bool click = false;
bool click2 = false;
int BGraphNodeNum = 0;

Graph TestGraph = Graph();
Graph BehaviorGraph = Graph();

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "AI_Test");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//For randomize sake
	srand(time(NULL));

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//-----------------------------------------------------------------------------|| For AI and Behaviors ||---------------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

	//create vector of agents to make flocking easier to manage
	/*for (int i = 0; i < 6; i++)
	{
		myAgents.emplace_back(new Agent((rand() % 600 + 100), (rand() % 500 + 100), 96, 48, CreateSprite("./images/invaders/invaders_2_00.png", 96, 48, true), 0.25f));
	}*/
	/*myAgents.push_back(TestWander);
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
	myAgents.push_back(TestWander15);*/

	//behavior list to test out anything that's not flocking
	std::vector<SteeringBehavior*> TestList;
	TestList.push_back(new Wander());
	TestList[0]->weight = 1;

	//behavior list for flocking
	OtherList.push_back(new Cohesion(myAgents));
	OtherList.push_back(new Allingment(myAgents));
	OtherList.push_back(new Seperation(myAgents));

	//weight of different behaviors in flocking
	//Cohesion
	OtherList[0]->weight = 0.6f;
	//Allingment
	OtherList[1]->weight = 0.03f;
	//Seperation
	OtherList[2]->weight = 0.45f;

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

	TestGraph.CreateGraph();
	TestGraph.AStarPathTest(0, 9);

	//create the agent that will be moving on the graph
	Agent* GraphAI = new Agent(TestGraph.ClosedList[0]->x, TestGraph.ClosedList[0]->y, 96, 48, CreateSprite("./images/cannon.png", 96, 48, true), 0.25f);
	GraphAI->GetPath(TestGraph.ClosedList);

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//---------------------------------------------------------------------------|| For Graphs and Path Finding ||----------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

	//Enum for switiching between AI Modes
	AIMODE mode = eBehavior;

    //Game Loop
    do
    {
		ClearScreen();
		
		if (GetAsyncKeyState(VK_LEFT))
		{
			mode = eBehavior;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			mode = eGraphA;
		}

		if (GetAsyncKeyState('R'))
		{
			click = false;
		}

		switch (mode)
		{
		case eBehavior:
			ResetGraphAI(TestGraph, GraphAI);
			DrawString("Flocking AI", 300, 600, SColour(255, 255, 255, 255));
			NewAgentAtClick();
			NewNodeAtClick();
			AgentBehaviors(myAgents);
			BehaviorGraph.DrawGraph();
			break;

		case eGraphA:
			ResetBehaviorAgents(myAgents);
			DrawString("Graph Path Finding", 300, 600, SColour(255, 255, 255, 255));
			GraphNodeAI(TestGraph, GraphAI);
			break;
		}

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}


//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
//-----------------------------------------------------------------------------|| For AI and Behaviors ||---------------------------------------------------------------------------------------------------------------\\
//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//
void AgentBehaviors(std::vector<Agent*> in_myAgents)
{
	//Set delta time
	DeltaTime.x = GetDeltaTime();
	DeltaTime.y = GetDeltaTime();

	//More update stuff
	for (int i = 0; i < in_myAgents.size(); i++)
	{
		in_myAgents[i]->NeighborList.clear();
		MoveSprite(in_myAgents[i]->textureHandler, in_myAgents[i]->Pos.x, in_myAgents[i]->Pos.y);
		DrawSprite(in_myAgents[i]->textureHandler);
	}

	//Update the agents
	for (int i = 0; i < in_myAgents.size(); i++)
	{
		in_myAgents[i]->CheckNeighbors(in_myAgents);
		in_myAgents[i]->UpdateAgent(new Seperation(in_myAgents), in_myAgents[i], DeltaTime);
		in_myAgents[i]->AvoidGraphNode(BehaviorGraph.m_aNodes);
	}

	//Draw line just to see what the velocity is and where the agent is heading
	for (int i = 0; i < in_myAgents.size(); i++)
	{
		DrawLine(in_myAgents[i]->Pos.x, in_myAgents[i]->Pos.y, (in_myAgents[i]->Pos.x + (in_myAgents[i]->Velocity.x * 100)), (in_myAgents[i]->Pos.y + (in_myAgents[i]->Velocity.y * 100)), SColour((rand() % 255), (rand() % 255), (rand() % 255), 255));
	}
}

void NewAgentAtClick()
{
	double mXPos, mYPos;
	float aXPos, aYPos;

	if (GetMouseButtonDown(MOUSE_BUTTON_1))
	{
		if (click != true)
		{
			click = true;
			GetMouseLocation(mXPos, mYPos);
			mXPos = 0 + mXPos;
			mYPos = 600 - mYPos;
			aXPos = (float)(mXPos);
			aYPos = (float)(mYPos);
			myAgents.emplace_back(new Agent(aXPos, aYPos, 96, 48, CreateSprite("./images/invaders/invaders_5_00.png", 96, 48, true, SColour(0, 0, 255, 255)), 0.25f));
			myAgents[myAgents.size() - 1]->SetBehaviors(OtherList);
		}
	}
	else
	{
		click = false;
	}
}

void ResetBehaviorAgents(std::vector<Agent*> in_myAgents)
{
	myAgents.clear();
	if (BehaviorGraph.m_aNodes.size() > 0)
	{
		BehaviorGraph.m_aNodes.clear();
	}
	BGraphNodeNum = 0;
}


//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
//---------------------------------------------------------------------------|| For Graphs and Path Finding ||----------------------------------------------------------------------------------------------------------\\
//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

void GraphNodeAI(Graph in_TestGraph, Agent* in_Agent)
{

	in_TestGraph.CheckMouseClick();
	in_TestGraph.DrawGraph();
	in_Agent->MoveOnGraphPath(0.25f);

}

//CreateVisualNode(i, CreateSprite("./images/invaders/invaders_7_01.png", 64, 64, true), xPos, yPos);
void NewNodeAtClick()
{
	double mXPos, mYPos;
	float aXPos, aYPos;

	if (GetMouseButtonDown(MOUSE_BUTTON_2))
	{
		if (click2 != true)
		{
			click2 = true;
			GetMouseLocation(mXPos, mYPos);
			mXPos = 0 + mXPos;
			mYPos = 600 - mYPos;
			aXPos = (float)(mXPos);
			aYPos = (float)(mYPos);
			BehaviorGraph.m_aNodes.emplace_back(new GraphNode(BGraphNodeNum));
			BehaviorGraph.CreateVisualNode(BGraphNodeNum, CreateSprite("./images/invaders/invaders_7_01.png", 64, 64, true), aXPos, aYPos);
			BGraphNodeNum++;
		}
	}
	else
	{
		click2 = false;
	}
	
}

void ResetGraphAI(Graph in_TestGraph, Agent* in_Agent)
{
	in_Agent->Pos.x = in_TestGraph.ClosedList[0]->x;
	in_Agent->Pos.y = in_TestGraph.ClosedList[0]->y;
	in_Agent->NodeNumber = 0;
}