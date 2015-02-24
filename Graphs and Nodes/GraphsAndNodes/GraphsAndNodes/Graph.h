#pragma once
#include <iostream>
#include <algorithm>
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

private:
	NodeList m_aNodes;
};

