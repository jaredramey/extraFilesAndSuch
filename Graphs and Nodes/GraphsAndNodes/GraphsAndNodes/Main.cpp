//Standard Libraries
#include <iostream>
//Custom Headers
#include "GraphNode.h"
#include "Graph.h"

using namespace std;

Graph myGraph = Graph();
Graph testGraph = Graph();
//Create some Nodes
GraphNode* myNode1 = new GraphNode(1);
GraphNode* myNode2 = new GraphNode(1);
GraphNode* myNode3 = new GraphNode(1);
GraphNode* myNode4 = new GraphNode(1);
GraphNode* myNode5 = new GraphNode(1);
GraphNode* myNode6 = new GraphNode(1);

int main()
{
	system("CLS");

	//Flesh out the Nodes and Link
	myGraph.AddNode(myNode1);
	myGraph.AddNode(myNode2);
	myGraph.AddNode(myNode3);
	myGraph.AddNode(myNode4);
	myGraph.AddNode(myNode5);
	myGraph.AddNode(myNode6);

	myGraph.LinkNodes(myNode1, myNode2);
	myGraph.LinkNodes(myNode1, myNode5);
	myGraph.LinkNodes(myNode2, myNode3);
	myGraph.LinkNodes(myNode3, myNode1);
	myGraph.LinkNodes(myNode3, myNode4);
	myGraph.LinkNodes(myNode4, myNode6);
	myGraph.LinkNodes(myNode4, myNode5);
	myGraph.LinkNodes(myNode6, myNode5);

	myGraph.DisplayNeighbors();

	//Remove a node
	myGraph.RemoveNode(myNode2);
	cout << "Removed a Node" << endl;

	myGraph.DisplayNeighbors();

	cout << "------------------" << endl;

 	system("PAUSE");
	return 0;
}