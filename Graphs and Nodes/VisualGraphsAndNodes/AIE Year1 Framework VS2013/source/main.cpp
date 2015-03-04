#include <iostream>
#include "AIE.h"
#include "Graph.h"
#include "GraphNode.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	Graph TestGraph = Graph();
	TestGraph.CreateGraph();
	TestGraph.DisplayNeighbors();
	TestGraph.ShortestPath(0, 1);

    //Game Loop
    do
    {
		ClearScreen();
		TestGraph.DrawGraph();

		if (IsKeyDown('A'))
		{
			TestGraph.ShortestPath(15, 0);
		}

		if (IsKeyDown('S'))
		{
			TestGraph.ShortestPath(0, 15);
		}


		TestGraph.m_AI.DrawAI();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
