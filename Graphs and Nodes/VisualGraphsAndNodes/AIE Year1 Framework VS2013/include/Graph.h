#pragma once
#include <iostream>
#include <algorithm>
#include <time.h>
#include <Windows.h>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
#include "GraphNode.h"
#include "AIE.h"
#include "AI.h"

class Graph
{
public:
	typedef std::vector<GraphNode*> NodeList;

	Graph();
	~Graph();

	struct NodeCompare
	{
		inline bool operator() (const GraphNode* left, const GraphNode* right)
		{
			return (left->nodeWeight < right->nodeWeight);
		}
	};

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
	void DrawGraph();
	std::vector<GraphNode*> GetNeighbors(GraphNode* a_pNode);
	std::vector<GraphNode*> BuildPath(GraphNode* a_pStart, GraphNode* a_pEnd);
	void ShortestPath(int a_pStart, int a_pEnd);
	void ResetAI();
	void CreateAI(float x, float y);

	AI m_AI;

private:
	NodeList m_aNodes;
	NodeList AIPath;
	int CurrentNodeOnPath;
	int AIStart;
};

