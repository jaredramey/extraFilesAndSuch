#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <vector>

enum NodeType
{
	eSurface,
	eWall
};

class GraphNode
{
public:
	GraphNode(int a_iNum);
	~GraphNode();

	int m_iNodeNumber;
	bool m_bVisited;
	float x;
	float y;
	int textureHandle;
	int nodeWeight;
	float m_fCost;
	float p_GScore;
	NodeType NT;
	bool isTraversable;

	struct Edge;

	typedef std::vector<Edge> EdgeList;
	struct Edge{
		GraphNode* m_pStart;
		GraphNode* m_pEnd;
		int gCost;
		float hScore;
		float fCost;
	};

	Edge myEdges;
	EdgeList connectedEdges;
	GraphNode* Parent;
	std::vector<GraphNode*> Children;
};

#endif //_GRAPH_H_