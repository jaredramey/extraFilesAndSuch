#include <iostream>
#include "AIE.h"
#include "Graph.h"
#include "GraphNode.h"
#include "Agent.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	Graph TestGraph = Graph();
	TestGraph.CreateGraph();
	TestGraph.DisplayNeighbors();

	int frame = 0;

    //Game Loop
    do
    {
		ClearScreen();
		TestGraph.CheckMouseClick();
		TestGraph.DrawGraph();
		TestGraph.AIAPath(GetDeltaTime(), 100.0f);
		TestGraph.m_AI.DrawAI();


    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
