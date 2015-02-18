#include "Graph.h"


Graph::Graph()
{
}

Graph::~Graph()
{
}

Graph::Graph(unsigned int a_uiNodeCount)
{

}

void Graph::AddNode(GraphNode* a_pNode)
{
	a_pNode->m_iNodeNumber = m_aNodes.size() + 1;
	m_aNodes.emplace_back(a_pNode);
	std::cout << m_aNodes.size() << std::endl;
}

void Graph::RemoveNode(GraphNode* a_pNode)
{
	for (int i = 1; i < m_aNodes.size(); i++)
	{
		if (i == a_pNode->m_iNodeNumber)
		{
			m_aNodes.erase(m_aNodes.begin() + (i - 1));
		}
	}
	for (int k = 0; k < m_aNodes.size(); k++)
	{
		if (m_aNodes[k]->m_iNodeNumber > a_pNode->m_iNodeNumber)
		{
			m_aNodes[k]->m_iNodeNumber -= 1;
		}
	}
	
	std::cout << m_aNodes.size() << std::endl;
}
