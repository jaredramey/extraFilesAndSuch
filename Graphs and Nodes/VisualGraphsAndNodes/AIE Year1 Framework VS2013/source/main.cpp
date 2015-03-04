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

    //Game Loop
    do
    {
		ClearScreen();
		TestGraph.DrawGraph();
		TestGraph.AStarPathTest(0, 7);


    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
