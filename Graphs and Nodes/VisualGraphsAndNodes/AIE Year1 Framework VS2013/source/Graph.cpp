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

	srand(time(NULL));

	for (int i = 0; i < (a_uiNodeCount*3); i++)
	{
		int node1 = (rand() % a_uiNodeCount);
		int node2 = (rand() % a_uiNodeCount);
		while (node2 == node1)
		{
			node2 = (rand() % a_uiNodeCount);
		}

		if (m_aNodes[node1]->connectedEdges.size() == 0)
		{
			LinkNodes(m_aNodes[(node1)], m_aNodes[(node2)]);
		}

		for (int k = 0; k < m_aNodes[node1]->connectedEdges.size(); k++)
		{
			if (m_aNodes[node1]->connectedEdges[k].m_pEnd->m_iNodeNumber != m_aNodes[node2]->m_iNodeNumber)
			{
				LinkNodes(m_aNodes[(node1)], m_aNodes[(node2)]);
				k += 10;
			}
		}
	}
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

void Graph::Traverse(int StartNode)
{
	GraphNode* CurrentNode = m_aNodes[StartNode];

	int loop = 0;
	int nodeChoice;

	while (loop == 0)
	{
		system("CLS");
		std::cout << "You are currently in node " << CurrentNode->m_iNodeNumber << std::endl;
		std::cout << "It's current neighbors are: ";
		for (int i = 0; i < CurrentNode->connectedEdges.size(); i++)
		{
			std::cout << CurrentNode->connectedEdges[i].m_pEnd->m_iNodeNumber;
			if (i < (CurrentNode->connectedEdges.size()-1))
			{
				std::cout << ", ";
			}
		}

		nodeChoice = 0;

		std::cout << "\n Please Choose a Neighbor Node to go to." << std::endl;
		TryAgain:
		std::cin >> nodeChoice;
		if (nodeChoice > CurrentNode->connectedEdges.size())
		{
			std::cout << "That's not an avaliable Node. Please Select an avaliable Node" << std::endl;
			goto TryAgain;
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			loop++;
		}

		CurrentNode = m_aNodes[nodeChoice-1];
	}
}

void Graph::ResetVisited()
{
	for (int i = 0; i < m_aNodes.size(); i++)
	{
		m_aNodes[i]->m_bVisited = false;
	}
}

bool Graph::SearchDFS(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	std::stack<GraphNode*> oNodeStack;
	oNodeStack.push(a_pStart);

	while (!oNodeStack.empty())
	{
		GraphNode* pCurrent = oNodeStack.top();
		oNodeStack.pop();

		if (pCurrent->m_bVisited == true)
		{
			continue;
		}

		pCurrent->m_bVisited = true;

		if (pCurrent == a_pEnd)
		{
			return true;
		}

		for (int i = 0; i < pCurrent->connectedEdges.size(); i++)
		{
			oNodeStack.push(pCurrent->connectedEdges[i].m_pEnd);
		}
	}

	return false;
}

bool Graph::SearchBFS(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	std::queue<GraphNode*> oNodeStack;
	oNodeStack.push(a_pStart);

	while (!oNodeStack.empty())
	{
		GraphNode* pCurrent = oNodeStack.back();
		oNodeStack.pop();

		if (pCurrent->m_bVisited == true)
		{
			continue;
		}

		pCurrent->m_bVisited = true;

		if (pCurrent == a_pEnd)
		{
			return true;
		}

		for (int i = 0; i < pCurrent->connectedEdges.size(); i++)
		{
			oNodeStack.push(pCurrent->connectedEdges[i].m_pEnd);
		}
	}

	return false;
}

void Graph::CreateGraph()
{
	float xPos = 50, yPos = 50;

	srand(time(NULL));

	for (int i = 0; i < 16; i++)
	{
		AddNode(new GraphNode(i));
		m_aNodes[i]->nodeWeight = (rand() % 6);

		if (i > 0)
		{
			xPos += 150;
			if (i == 4 )
			{
				yPos += 150;
				xPos = 50;
			}

			if (i == 8)
			{
				yPos += 150;
				xPos = 50;
			}

			if (i == 12)
			{
				yPos += 150;
				xPos = 50;
			}
		}

		CreateVisualNode(i, CreateSprite("./images/crate_sideup.png", 64, 64, true), xPos, yPos);
	}

	for (int i = 0; i < m_aNodes.size(); i++)
	{
		for (int k = 0; k < m_aNodes.size(); k++)
		{
			if ((m_aNodes[k]->x <= (m_aNodes[i]->x + 200) && m_aNodes[k]->y <= (m_aNodes[i]->y + 150)) && (m_aNodes[k]->x >= (m_aNodes[i]->x - 200)))
			{
				if ((i < 3) && k != i)
				{
					LinkNodes(m_aNodes[i], m_aNodes[k]);
				}
			}

			if ((m_aNodes[k]->x <= (m_aNodes[i]->x + 200) && m_aNodes[k]->y <= (m_aNodes[i]->y + 150)) && (m_aNodes[k]->x >= (m_aNodes[i]->x - 200) && m_aNodes[k]->y <= (m_aNodes[i]->y + 150)))
			{
				if ((i > 2 && i < 4) && k != i)
				{
					LinkNodes(m_aNodes[i], m_aNodes[k]);
				}
			}

			if ((m_aNodes[k]->x <= (m_aNodes[i]->x + 200) && m_aNodes[k]->y <= (m_aNodes[i]->y + 150)) && (m_aNodes[k]->x >= (m_aNodes[i]->x - 200) && m_aNodes[k]->y <= (m_aNodes[i]->y + 150)))
			{
				if ((i > 3 && i < 8) && k != i)
				{
					LinkNodes(m_aNodes[i], m_aNodes[k]);
				}
			}

			if ((m_aNodes[k]->x <= (m_aNodes[i]->x + 200) && m_aNodes[k]->y <= (m_aNodes[i]->y + 150)) && (m_aNodes[k]->x >= (m_aNodes[i]->x - 200) && m_aNodes[k]->y >= (m_aNodes[i]->y - 150)))
			{
				if ((i > 7 && i < 12) && k != i)
				{
					LinkNodes(m_aNodes[i], m_aNodes[k]);
				}
			}

			if ((m_aNodes[k]->x <= (m_aNodes[i]->x + 200) && m_aNodes[k]->y <= (m_aNodes[i]->y + 150)) && (m_aNodes[k]->x >= (m_aNodes[i]->x - 200) && m_aNodes[k]->y >= (m_aNodes[i]->y - 150)))
			{
				if ((i > 11 && i < 16) && k != i)
				{
					LinkNodes(m_aNodes[i], m_aNodes[k]);
				}
			}
		}
	}
}

void Graph::CreateVisualNode(int NodeID, int a_texturePath, float a_x, float a_y)
{
	m_aNodes[NodeID]->textureHandle = a_texturePath;
	m_aNodes[NodeID]->x = a_x;
	m_aNodes[NodeID]->y = a_y;
}

void Graph::DrawGraph()
{
	for (int i = 0; i < m_aNodes.size(); i++)
	{
		MoveSprite(m_aNodes[i]->textureHandle, m_aNodes[i]->x, m_aNodes[i]->y);
		DrawSprite(m_aNodes[i]->textureHandle);
	}

	for (int i = 0; i < m_aNodes.size(); i++)
	{
		for (int k = 0; k < m_aNodes[i]->connectedEdges.size(); k++)
		{
			DrawLine(m_aNodes[i]->x, m_aNodes[i]->y, m_aNodes[i]->connectedEdges[k].m_pEnd->x, m_aNodes[i]->connectedEdges[k].m_pEnd->y, SColour(215, 46, 0, 255));
		}
	}
}