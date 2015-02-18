#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>

struct Edge{
	GraphNode* m_pStart;
	GraphNode* m_pEnd;
	float m_fCoast;

};

class GraphNode
{
public:
	GraphNode(int a_iNum);
	~GraphNode();

	int m_iNodeNumber;
};

#endif //_GRAPH_H_