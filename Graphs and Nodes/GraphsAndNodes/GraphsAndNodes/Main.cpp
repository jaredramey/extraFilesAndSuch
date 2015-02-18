//Standard Libraries
#include <iostream>
//Custom Headers
#include "GraphNode.h"
#include "Graph.h"

using namespace std;

Graph myGraph = Graph();
GraphNode* myNode1 = new GraphNode(1);
GraphNode* myNode2 = new GraphNode(1);
GraphNode* myNode3 = new GraphNode(1);
GraphNode* myNode4 = new GraphNode(1);

int main()
{

	system("CLS");
	myGraph.AddNode(myNode1);
	myGraph.AddNode(myNode2);
	myGraph.AddNode(myNode3);
	myGraph.AddNode(myNode4);

	myGraph.RemoveNode(myNode2);

 	system("PAUSE");
	return 0;
}