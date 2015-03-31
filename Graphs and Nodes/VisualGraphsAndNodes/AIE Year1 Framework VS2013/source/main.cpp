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

//Enum to switch between three methods to match up with specs
enum AIMODE
{
	eBehavior,
	eGraphA,
	eGraphB
};

//Put my stuff into functions to be called upon in main loop
void AgentBehaviors(std::vector<Agent*> in_myAgents);
void NewAgentAtClick();
void ResetBehaviorAgents(std::vector<Agent*> in_myAgents);
void GraphNodeAI(Agent* in_Agent);
void ResetGraphAI(Graph in_TestGraph, Agent* in_Agent);
void NewNodeAtClick();
void Dijkstras(Agent* in_Agent);

//create a point for Delta time so I can easily use it later
Point DeltaTime;

//Had to move all this stuff to Global Space so I could alter values in later functions
std::vector<Agent*> myAgents;
std::vector<SteeringBehavior*> OtherList;
bool click = false;
bool click2 = false;
bool ProgramRun = true;
int BGraphNodeNum = 0;

//create all the graphs
Graph TestGraph = Graph();
Graph DGraph = Graph();
Graph BehaviorGraph = Graph();

//create the agent that will be moving on the graph
Agent* GraphAI;

int main( int argc, char* argv[] )
{	
	//Initialize the AIE framework
    Initialise(800, 600, false, "AI_Test");
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//For randomize sake
	srand(time(NULL));

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//-----------------------------------------------------------------------------|| For AI and Behaviors ||---------------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

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

	GraphAI = new Agent(100.0f, 100.0f, 96, 48, CreateSprite("./images/cannon.png", 96, 48, true), 0.25f);

	//create graph for A*
	TestGraph.CreateGraph();

	//Create graph for Dijkstras
	DGraph.CreateGraph();

	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//=\\
	//---------------------------------------------------------------------------|| For Graphs and Path Finding ||----------------------------------------------------------------------------------------------------------\\
	//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//==//

	//Enum for switiching between AI Modes (start on Flocking AI)
	AIMODE mode = eBehavior;

    //Game Loop
    do
    {
		//clear the screen
		ClearScreen();
		
		//Take in which AI state the user wants to see
		if (GetAsyncKeyState(VK_LEFT))
		{
			mode = eBehavior;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			mode = eGraphA;
		}

		if (GetAsyncKeyState(VK_UP))
		{
			mode = eGraphB;
		}
		
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			ProgramRun = false;
		}

		switch (mode)
		{
			//For seeing the Flocking AI
		case eBehavior:
			//Reset the Graph AI
			ResetGraphAI(TestGraph, GraphAI);
			//Tell the user what they're seeing
			DrawString("Flocking AI", 300, 600, SColour(255, 255, 255, 255));
			//Check for mouse input on new Agent or a New Node
			NewAgentAtClick();
			NewNodeAtClick();
			//Update all the agents in the list
			AgentBehaviors(myAgents);
			//Draw all the Nodes
			BehaviorGraph.DrawGraph();
			break;

			//For seeing the A* path finding
		case eGraphA:
			//Reset the Flocking AI
			ResetBehaviorAgents(myAgents);
			//Tell the user where the user is
			DrawString("Graph Path Finding (A*)", 300, 600, SColour(255, 255, 255, 255));
			//Update Function
			GraphNodeAI(GraphAI);
			break;

			//For seeing Dijkstras Path finding
		case eGraphB:
			//Reset Flocking Agents
			ResetBehaviorAgents(myAgents);
			//Tell the user where they are
			DrawString("Graph Path Finding (Dijkstras)", 250, 600, SColour(255, 255, 255, 255));
			//Update Function
			Dijkstras(GraphAI);
			break;
		default:
			
			break;
		}
	} while (!FrameworkUpdate() && ProgramRun == true);

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

	//Update the agents
	for (int i = 0; i < in_myAgents.size(); i++)
	{
		in_myAgents[i]->NeighborList.clear();
		MoveSprite(in_myAgents[i]->textureHandler, in_myAgents[i]->Pos.x, in_myAgents[i]->Pos.y);
		DrawSprite(in_myAgents[i]->textureHandler);
	}

	//More update stuff
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

	//Check for mouse state down (click)
	if (GetMouseButtonDown(MOUSE_BUTTON_1))
	{
		//A bool condition so it only registers the click once
		if (click != true)
		{
			click = true;
			//Get the mouse pos then change it to match up with how the screen is layed out
			GetMouseLocation(mXPos, mYPos);
			mXPos = 0 + mXPos;
			mYPos = 600 - mYPos;
			//Change it to a float so I can make a new agent with the quardnets
			aXPos = (float)(mXPos);
			aYPos = (float)(mYPos);
			//New agent!
			myAgents.emplace_back(new Agent(aXPos, aYPos, 96, 48, CreateSprite("./images/invaders/invaders_5_00.png", 96, 48, true, SColour(0, 0, 255, 255)), 0.25f));
			myAgents[myAgents.size() - 1]->SetBehaviors(OtherList);
		}
	}
	else
	{
		//If the mouse isn't clicked then set to bool to false
		click = false;
	}
}

void ResetBehaviorAgents(std::vector<Agent*> in_myAgents)
{
	//Reset function for the agents
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

void GraphNodeAI(Agent* in_Agent)
{
	//Draw the Graph
	TestGraph.DrawGraph();
	//Check mouse click
	TestGraph.CheckMouseClick();
	//Get the path if there is one to be had
	in_Agent->GetPath(TestGraph.ClosedList);
	//Move on the path (if there is one)
	in_Agent->MoveOnGraphPath(0.25f);

}

void Dijkstras(Agent* in_Agent)
{
	//Draw the Graph
	DGraph.DrawGraph();
	//Check mouse click
	DGraph.DCheckMouseClick();
	//Get the path if there is one to be had
	in_Agent->GetPath(DGraph.ClosedList);
	//Move on the path (if there is one)
	in_Agent->MoveOnGraphPath(0.25f);
}

void NewNodeAtClick()
{
	double mXPos, mYPos;
	float aXPos, aYPos;

	//Same thing as adding a new agent but to add a node
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
	//Reset the AI that traverses graphs
	GraphAI->closedList.clear();
	GraphAI->Pos.x = 100.0f;
	GraphAI->Pos.y = 100.0f;
	GraphAI->NodeNumber = 0;
}
