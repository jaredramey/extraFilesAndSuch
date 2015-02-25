#pragma once
#include <iostream>
#include <algorithm>
#include <time.h>
#include <Windows.h>
#include <stack>
#include <queue>
#include "GraphNode.h"

class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	Graph();
	~Graph();

	void GraphOther(unsigned int a_uiNodeCount);
	void LinkNodes(GraphNode* a_pNode, GraphNode*a_pOtherNode);
	void AddNode(GraphNode* a_pNode);
	void RemoveNode(GraphNode* a_pNode);
	void DisplayNeighbors();
	bool CheckNeighbors(GraphNode* A, GraphNode* B);
	void Traverse(int StartNode);
	void ResetVisited();
	bool SearchDFS(GraphNode* a_pStart, GraphNode* a_pEnd);
	bool SearchBFS(GraphNode* a_pStart, GraphNode* a_pEnd);
	void CreateGraph();
	void CreateVisualNode(int NodeID ,int a_texturePath, float a_x, float a_y);

private:
	NodeList m_aNodes;
};

