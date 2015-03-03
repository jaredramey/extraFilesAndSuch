#include <iostream>
#include "AIE.h"
#include "Graph.h"
#include "GraphNode.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	Graph TestGraph = Graph();
	Graph OtherGraph = Graph();

	TestGraph.CreateGraph();
	OtherGraph.CreateGraph();

    //Game Loop
    do
    {
		ClearScreen();
		TestGraph.DrawGraph();
		OtherGraph.DrawGraph();

		TestGraph.ShortestPath(15, 0);
		TestGraph.m_AI.DrawAI();

		if (IsKeyDown('A'))
		{
			TestGraph.m_AI.DrawAI();
		}

		if (IsKeyDown('S'))
		{
			OtherGraph.ShortestPath(0, 15);
			OtherGraph.m_AI.DrawAI();
		}

		if (IsKeyDown('R'))
		{
			TestGraph.ResetAI();
			OtherGraph.ResetAI();
		}

		//DrawString("Note: Make sure to press 'R' to reset AI", 50.0f, 580.0f, SColour(255, 255, 255, 255));

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
