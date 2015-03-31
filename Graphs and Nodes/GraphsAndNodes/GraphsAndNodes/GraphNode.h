#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <vector>

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

	struct Edge;

	typedef std::vector<Edge> EdgeList;
	struct Edge{
		GraphNode* m_pStart;
		GraphNode* m_pEnd;
		float m_fCoast;
	};

	Edge myEdges;
	EdgeList connectedEdges;

	void ConnectNodes(GraphNode& other);
};

#endif //_GRAPH_H_