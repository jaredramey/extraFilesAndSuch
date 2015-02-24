#include "Graph.h"


Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::GraphOther(unsigned int a_uiNodeCount)
{
	for (int i = 0; i < a_uiNodeCount; i++)
	{
		AddNode(new GraphNode(i));
	}

	LinkNodes(m_aNodes[0], m_aNodes[1]);
	LinkNodes(m_aNodes[0], m_aNodes[5]);
	LinkNodes(m_aNodes[1], m_aNodes[2]);
	LinkNodes(m_aNodes[2], m_aNodes[0]);
	LinkNodes(m_aNodes[2], m_aNodes[3]);
	LinkNodes(m_aNodes[3], m_aNodes[5]);
	LinkNodes(m_aNodes[3], m_aNodes[4]);
	LinkNodes(m_aNodes[5], m_aNodes[4]);
}

void Graph::LinkNodes(GraphNode* a_pNode, GraphNode*a_pOtherNode)
{
	//Create an 'Edge' starting from the newly created Node to another Node
	a_pNode->myEdges.m_pStart = a_pNode;
	a_pNode->myEdges.m_pEnd = a_pOtherNode;
	a_pNode->connectedEdges.emplace_back(a_pNode->myEdges);
}

void Graph::AddNode(GraphNode* a_pNode)
{
	//Give the node an ID
	a_pNode->m_iNodeNumber = m_aNodes.size() + 1;
	//Place the Node in a Node list
	m_aNodes.emplace_back(a_pNode);
	//output the size of the Node list (for debugging purposes)
	//std::cout << m_aNodes.size() << std::endl;
	//Add a start to an edge so the later code doesn't freak out
	a_pNode->myEdges.m_pStart = a_pNode;
}

void Graph::RemoveNode(GraphNode* a_pNode)
{
	//Loop through Node list and delete any Edge that may be connected to the soon to be deleted Node
	for (int i = 0; i < m_aNodes.size(); i++)
	{
		for (int k = 0; k < m_aNodes[i]->connectedEdges.size(); k++)
		{
			//Check to see if the end of the Edge is pointing to the requested Node
			if (m_aNodes[i]->connectedEdges[k].m_pEnd == a_pNode)
			{
				//If the Edge is connected to the requested Node then delete that edge (or at least the end of it)
				m_aNodes[i]->connectedEdges[k].m_pEnd = NULL;
			}
		}
	}
	//Loop through the Node list to find requested Node and delete it
	for (int i = 1; i < m_aNodes.size(); i++)
	{
		//If the Node ID matches the current Node in the Node list then start Deleting
		if (i == a_pNode->m_iNodeNumber)
		{
			//Erase the Node
			m_aNodes.erase(m_aNodes.begin() + (i - 1));
		}
	}
	//Loop through the Node list again to fit ID's
	/*for (int k = 0; k < m_aNodes.size(); k++)
	{
		//If the Node ID is greater then the Deleted Nodes value then fir the ID
		if (m_aNodes[k]->m_iNodeNumber > a_pNode->m_iNodeNumber)
		{
			m_aNodes[k]->m_iNodeNumber -= 1;
		}
	}*/
	
	//Output the new size of the Node list (for debugging purposes)
	//std::cout << m_aNodes.size() << std::endl;
}

void Graph::DisplayNeighbors()
{
	for (int i = 0; i < m_aNodes.size(); i++)
	{
		for (int k = 0; k < m_aNodes[i]->connectedEdges.size(); k++)
		{
			if (m_aNodes[i]->connectedEdges[k].m_pEnd != NULL)
			{
				std::cout << m_aNodes[i]->connectedEdges[k].m_pStart->m_iNodeNumber;
				std::cout << " -> ";
				std::cout << m_aNodes[i]->connectedEdges[k].m_pEnd->m_iNodeNumber << std::endl;
			}

			else if (m_aNodes[i]->connectedEdges[k].m_pEnd == NULL)
			{
				std::cout << m_aNodes[i]->connectedEdges[k].m_pStart->m_iNodeNumber;
				std::cout << " -> ";
				std::cout << "*-REMOVED-*" << std::endl;
			}
		}
	}
	
}

bool Graph::CheckNeighbors(GraphNode* A, GraphNode* B)
{
	for (int i = 0; i < A->connectedEdges.size(); i++)
	{
		if (A->connectedEdges[i].m_pEnd == B)
		{
			return true;
		}
	}
		return false;
	
}
