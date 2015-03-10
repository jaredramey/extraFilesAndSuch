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
	a_pNode->m_iNodeNumber = m_aNodes.size();
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
				std::cout << "(" << m_aNodes[i]->nodeWeight << ")";
				std::cout << " -> ";
				std::cout << m_aNodes[i]->connectedEdges[k].m_pEnd->m_iNodeNumber;
				std::cout << "(" << m_aNodes[i]->connectedEdges[k].m_pEnd->nodeWeight << ")";
				std::cout << " = " << m_aNodes[i]->connectedEdges[k].gCost << std::endl;
			}

			else if (m_aNodes[i]->connectedEdges[k].m_pEnd == NULL)
			{
				std::cout << m_aNodes[i]->connectedEdges[k].m_pStart->m_iNodeNumber;
				std::cout << "(" << m_aNodes[i]->nodeWeight << ")";
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
		m_aNodes[i]->nodeWeight = (rand() % 4+1);

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

		CreateVisualNode(i, CreateSprite("./images/invaders/invaders_7_01.png", 64, 64, true), xPos, yPos);
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

		for (int k = 0; k < m_aNodes[i]->connectedEdges.size(); k++)
		{
				m_aNodes[i]->connectedEdges[k].gCost = (m_aNodes[i]->nodeWeight + m_aNodes[i]->connectedEdges[k].m_pEnd->nodeWeight);
				m_aNodes[i]->p_GScore = m_aNodes[i]->connectedEdges[k].gCost;
				m_aNodes[i]->NT = eSurface;
				m_aNodes[i]->isTraversable = true;
		}
	}
	ResetVisited();
	m_AI.CreateAI(96, 48, CreateSprite("./images/cannon.png", 96, 48, true));

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

	std::string gCostToDisplay;

	for (int i = 0; i < m_aNodes.size(); i++)
	{
		for (int k = 0; k < m_aNodes[i]->connectedEdges.size(); k++)
		{
			gCostToDisplay = std::to_string(m_aNodes[i]->connectedEdges[k].gCost);
			char const *pchar = gCostToDisplay.c_str();
			if (m_aNodes[i]->connectedEdges[k].m_pEnd->x > m_aNodes[i]->x && m_aNodes[i]->connectedEdges[k].m_pEnd->y == m_aNodes[i]->y)
			{
				DrawString(pchar, ((m_aNodes[i]->connectedEdges[k].m_pEnd->x-100)), ((m_aNodes[i]->connectedEdges[k].m_pEnd->y)), SColour(255, 255, 255, 255));
			}

			if (m_aNodes[i]->connectedEdges[k].m_pEnd->y > m_aNodes[i]->y && m_aNodes[i]->connectedEdges[k].m_pEnd->x == m_aNodes[i]->x)
			{
				DrawString(pchar, ((m_aNodes[i]->connectedEdges[k].m_pEnd->x)), ((m_aNodes[i]->connectedEdges[k].m_pEnd->y-75)), SColour(255, 255, 255, 255));
			}

			if (m_aNodes[i]->connectedEdges[k].m_pEnd->y > m_aNodes[i]->y && m_aNodes[i]->connectedEdges[k].m_pEnd->x > m_aNodes[i]->x)
			{
				DrawString(pchar, ((m_aNodes[i]->connectedEdges[k].m_pEnd->x - 100)), ((m_aNodes[i]->connectedEdges[k].m_pEnd->y - 75)), SColour(255, 255, 255, 255));
			}

			if (m_aNodes[i]->connectedEdges[k].m_pEnd->y < m_aNodes[i]->y && m_aNodes[i]->connectedEdges[k].m_pEnd->x < m_aNodes[i]->x)
			{
				DrawString(pchar, ((m_aNodes[i]->connectedEdges[k].m_pEnd->x + 100)), ((m_aNodes[i]->connectedEdges[k].m_pEnd->y + 75)), SColour(255, 255, 255, 255));
			}
			//DrawString(pchar, ((m_aNodes[i]->connectedEdges[k].m_pEnd->x)), ((m_aNodes[i]->connectedEdges[k].m_pEnd->y)), SColour(255, 255, 255, 255));
			DrawLine(m_aNodes[i]->x, m_aNodes[i]->y, m_aNodes[i]->connectedEdges[k].m_pEnd->x, m_aNodes[i]->connectedEdges[k].m_pEnd->y, SColour(215, 46, 0, 255));
			
		}
	}
}

std::vector<GraphNode*> Graph::GetNeighbors(GraphNode* a_pNode)
{
	std::vector<GraphNode*> MyList;
	
	for (int i = 0; i < a_pNode->connectedEdges.size(); i++)
	{
		MyList.emplace_back(a_pNode->connectedEdges[i].m_pEnd);
	}

	return MyList;
}


std::vector<GraphNode*> Graph::BuildPath(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	std::vector<GraphNode*> MyNodeList;
	std::vector<GraphNode*> MyVecOfNodes;
	GraphNode* CurrentNode = a_pStart;
	MyNodeList.emplace_back(CurrentNode);

	while (MyNodeList.back() != a_pEnd)
	{
		MyVecOfNodes = GetNeighbors(CurrentNode);
		std::sort(MyVecOfNodes.begin(), MyVecOfNodes.end(), NodeCompare());

			for (int i = 0; i < MyVecOfNodes.size(); i++)
			{
				if (i <= 0)
				{
					for (int k = 0; k < MyVecOfNodes.size(); k++)
					{
						if (MyVecOfNodes[k] == a_pEnd)
						{
							CurrentNode = MyVecOfNodes[k];
							break;
						}
					}
				}

				if ((MyVecOfNodes[i]->m_iNodeNumber > MyNodeList.back()->m_iNodeNumber))
				{
					if (CurrentNode == a_pEnd)
					{
						break;
					}
					CurrentNode = MyVecOfNodes[i];
					break;
				}

				if (i > 14)
				{
					std::cout << "Uh-oh, something broke!" << std::endl;
					break;
				}
			}

		MyNodeList.emplace_back(CurrentNode);
	}
	std::cout << "Path Built" << std::endl;

	for (int i = 0; i < MyNodeList.size(); i++)
	{
		if (i < MyNodeList.size()-1)
		{
			std::cout << MyNodeList[i]->m_iNodeNumber;
			std::cout << " -> ";
			std::cout << MyNodeList[i + 1]->m_iNodeNumber << std::endl;
		}

		else
		{
			std::cout << "The end Node is " << MyNodeList[i]->m_iNodeNumber << std::endl;
		}
	}

	return MyNodeList;
}

void Graph::ShortestPath(int a_pStart, int a_pEnd)
{
	GraphNode* CurrentNode;
	int AILast;
	int p_aNewStart = a_pStart;

	Reset:

	if (AIPath.empty())
	{
		CurrentAINode = m_aNodes[a_pStart];
		AIStart = 0;
		GoalNode = m_aNodes[a_pEnd];
		CurrentNode = CurrentAINode;

		if (p_aNewStart > a_pEnd)
		{
			AIPath = BuildPath(m_aNodes[a_pEnd], m_aNodes[p_aNewStart]);
			std::reverse(AIPath.begin(), AIPath.end());
		}

		else
		{
			AIPath = BuildPath(m_aNodes[p_aNewStart], m_aNodes[a_pEnd]);
		}

		
		AILast = AIPath.size();
	}

	else
	{
		CurrentNode = AIPath[CurrentNodeOnPath];
	}

	if (m_aNodes[a_pEnd] != GoalNode)
	{
		CurrentAINode = CurrentNode;
		ResetAI();
		goto Reset;
	}

		MoveSprite(m_AI.textureHandler, m_AI.x, m_AI.y);

		if (a_pStart < a_pEnd)
		{
			if (m_AI.x <= CurrentNode->x)
			{
				m_AI.x += 0.25f;
			}

			if (m_AI.y <= CurrentNode->y)
			{
				m_AI.y += 0.25f;
			}

			if (CurrentNode == m_aNodes[a_pEnd])
			{
				if (m_AI.x >= CurrentNode->x)
				{
					m_AI.x -= 0.25f;
				}

				if (m_AI.y >= CurrentNode->y)
				{
					m_AI.y -= 0.25f;
				}
			}

			if (CurrentNode != m_aNodes[a_pEnd] && ((m_AI.x >= CurrentNode->x) && (m_AI.y >= CurrentNode->y)))
			{
				AIStart += 1;
			}

			CurrentNodeOnPath = AIStart;
		}

		if (a_pStart > a_pEnd)
		{
			if (m_AI.x >= CurrentNode->x)
			{
				m_AI.x -= 0.25f;
			}

			if (m_AI.y >= CurrentNode->y)
			{
				m_AI.y -= 0.25f;
			}

			if (CurrentNode == m_aNodes[a_pEnd])
			{
				if (m_AI.x <= CurrentNode->x)
				{
					m_AI.x += 0.25f;
				}

				if (m_AI.y <= CurrentNode->y)
				{
					m_AI.y += 0.25f;
				}
			}

			if (CurrentNode != m_aNodes[a_pEnd] && ((m_AI.x <= CurrentNode->x) && (m_AI.y <= CurrentNode->y)))
			{
				AIStart += 1;
			}

			CurrentNodeOnPath = AIStart;
		}
}

void Graph::ResetAI()
{
	AIPath.clear();
	//CurrentNodeOnPath = 0;
	AIStart = 0;
}

float Graph::GetHueristic(const GraphNode* a_pCurrent, const GraphNode* a_pEnd)
{
	if (a_pCurrent != NULL && a_pEnd != NULL)
	{
		return(std::sqrt(((a_pCurrent->x - a_pEnd->x) * (a_pCurrent->x - a_pEnd->x)) + ((a_pCurrent->y - a_pEnd->y) * (a_pCurrent->y - a_pEnd->y))));
	}
	else
	{
		return 0;
	}
}

void Graph::AStarPath(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	GraphNode* CurrentNode;
	GraphNode* CurrentGoalNode;

	CurrentNode = a_pStart;
	CurrentGoalNode = a_pEnd;
	
	while (CurrentNode != CurrentGoalNode)
	{
		OpenList.emplace_back(CurrentNode);
		CurrentNode->m_bVisited = true;
		for (int i = 0; i < OpenList.size(); i++)
		{
			//Loop through and set H and then F
			for (int k = 0; k < CurrentNode->connectedEdges.size(); k++)
			{
				CurrentNode->connectedEdges[k].hScore = GetHueristic(CurrentNode->connectedEdges[k].m_pEnd, CurrentGoalNode);
				CurrentNode->connectedEdges[k].fCost = (CurrentNode->connectedEdges[k].gCost + CurrentNode->connectedEdges[k].hScore);
			}

			//Set the Open list to all connected edges
			for (int k = 0; k < CurrentNode->connectedEdges.size(); k++)
			{
				OpenList.emplace_back(CurrentNode->connectedEdges[k].m_pEnd);
			}
			//Loop through and set parents and children
			for (int k = 0; k < OpenList.size(); k++)
			{
				//Set the current Node as the Parent node
				OpenList[k]->Parent = CurrentNode;
				//Set the Current Node as the Parent Node
				CurrentNode->Children.emplace_back(OpenList[k]);
			}

			//Remove the Current Node from the Open List and move it onto the Closed list
			OpenList.erase(OpenList.begin());
			ClosedList.emplace_back(CurrentNode);

			//Loop through and set FScore to the OpenList Nodes so it's accessable
			for (int k = 0; k < CurrentNode->connectedEdges.size(); k++)
			{
				//for (int j = 0; j < TempList.size(); j++)
				OpenList[k]->m_fCost = CurrentNode->connectedEdges[k].fCost;
			}

			//Sort, see if any of the Nodes is the EndGoal Node and if one is then set it as the current Node, if not then repeat
			for (int k = 0; k < CurrentNode->connectedEdges.size(); k++)
			{
				if (CurrentNode->connectedEdges[k].m_pEnd == a_pEnd)
				{
					CurrentNode = CurrentNode->connectedEdges[k].m_pEnd;
					CurrentNode->m_bVisited = true;
					break;
				}
			}

			if (CurrentNode != a_pEnd)
			{
				std::sort(OpenList.begin(), OpenList.end(), AStarCompare());
				for (int k = 0; k < OpenList.size(); k++)
				{
					//Set the one with the lowest Fscore as the current Node
					if ((OpenList[k]->m_bVisited == false)/* && (OpenList[k]->x <= CurrentGoalNode->x && OpenList[k]->y <= CurrentGoalNode->y)*/)
					{
						if (OpenList[k]->isTraversable == true)
						{
							CurrentNode = OpenList[k];
							break;
						}
					}
				}
				//clear the OpenList of Nodes
				OpenList.clear();
				//Repeat until the last Node in the Closed list is the Goal Node
			}

			else
			{
				break;
			}
		}
	}

	if (CurrentNode == CurrentGoalNode)
	{
		ClosedList.emplace_back(CurrentNode);
	}

	//PathSmooth();
	//PathSmooth();

	if (ClosedList.size() > 1)
	{
		m_AI.UpdateAI(ClosedList[0]->x, ClosedList[0]->y);
	}
}

void Graph::AStarPathTest(int a_start, int a_end)
{
	AStarPath(m_aNodes[a_start], m_aNodes[a_end]);
}

void Graph::AIAPath(float deltaTime, float velocity)
{
	if (ClosedList.size() > 0)
	{
		GraphNode* CurrentNode;
		int LastPos = ClosedList.size() - 1;

		if (AIAPathNumber < ClosedList.size())
		{
			CurrentNode = ClosedList[AIAPathNumber];
		}
		else
		{
			CurrentNode = ClosedList[LastPos];
		}

		if (CurrentNode != NULL)
		{
			if (m_AI.x != CurrentNode->x)
			{
				if (CurrentNode->x > m_AI.x)
				{
					m_AI.x += (deltaTime * velocity);
				}

				else if (CurrentNode->x < m_AI.x)
				{
					m_AI.x -= (deltaTime * velocity);
				}
			}

			if (m_AI.y != CurrentNode->y)
			{
				if (CurrentNode->y > m_AI.y)
				{
					m_AI.y += (deltaTime * velocity) * 2;
				}

				else if (CurrentNode->y < m_AI.y)
				{
					m_AI.y -= (deltaTime * velocity) * 2;
				}
			}

			if (((m_AI.x >= (CurrentNode->x + 50) || m_AI.x >= (CurrentNode->x - 50)) && (m_AI.y >= (CurrentNode->y + 50) || m_AI.y >= (CurrentNode->y - 50))))
			{
				AIAPathNumber++;
				goto end;
			}
		}

		end:
		MoveSprite(m_AI.textureHandler, m_AI.x, m_AI.y);
	}
}

void Graph::ChangeNodeType(int a_pNode)
{
	if (m_aNodes[a_pNode]->isTraversable == true)
	{
		m_aNodes[a_pNode]->NT = eWall;
		m_aNodes[a_pNode]->isTraversable = false;
		m_aNodes[a_pNode]->textureHandle = CreateSprite("./images/crate_sideup.png", 64, 64, true);
	}
	else
	{
		m_aNodes[a_pNode]->NT = eSurface;
		m_aNodes[a_pNode]->isTraversable = true;
		m_aNodes[a_pNode]->textureHandle = CreateSprite("./images/invaders/invaders_7_01.png", 64, 64, true);
	}
}

void Graph::PathSmooth()
{
	GraphNode* CurrentNode;
	GraphNode* GoalNode = ClosedList[ClosedList.size()-1];

	for (int i = 0; i < ClosedList.size(); i++)
	{
		ClosedList[i]->m_fCost = (ClosedList[i]->p_GScore + GetHueristic(ClosedList[i], GoalNode));
	}

	for (int i = 0; i < ClosedList.size(); i++)
	{
		if (i+2 <= ClosedList.size()-1)
		{
			if ((ClosedList[i]->m_fCost + ClosedList[i + 2]->m_fCost) < (ClosedList[i]->m_fCost + ClosedList[i + 1]->m_fCost))
			{
				ClosedList.erase(ClosedList.begin() + (i + 1));
			}
		}
	}
}

void Graph::CheckMouseClick()
{
	double mXPos, mYPos;

	if (GetMouseButtonDown(0) && IsKeyDown('C'))
	{
		GetMouseLocation(mXPos, mYPos);
		for (int i = 0; i < m_aNodes.size(); i++)
		{
			if ((mXPos <= m_aNodes[i]->x + 50 && mYPos <= m_aNodes[i]->y + 50) && (mXPos >= m_aNodes[i]->x - 50 && mYPos >= m_aNodes[i]->y - 50))
			{
				if (i < 4)
				{
					ChangeNodeType(m_aNodes[i + 12]->m_iNodeNumber);
					break;
				}
				else if (i < 8)
				{
					ChangeNodeType(m_aNodes[i + 4]->m_iNodeNumber);
					break;
				}
				else if (i < 12)
				{
					ChangeNodeType(m_aNodes[i - 4]->m_iNodeNumber);
					break;
				}
				else
				{
					ChangeNodeType(m_aNodes[i - 12]->m_iNodeNumber);
					break;
				}
			}
		}
	}

	else if (GetMouseButtonDown(0) && IsKeyDown('S'))
	{
		GetMouseLocation(mXPos, mYPos);
		for (int i = 0; i < m_aNodes.size(); i++)
		{
			if ((mXPos <= m_aNodes[i]->x + 50 && mYPos <= m_aNodes[i]->y + 50) && (mXPos >= m_aNodes[i]->x - 50 && mYPos >= m_aNodes[i]->y - 50))
			{
				if (i < 4)
				{
					StartNode = m_aNodes[i + 12];
					MoveSprite(m_AI.textureHandler, StartNode->x, StartNode->y);
					std::cout << "Start Selected" << std::endl;
					break;
				}
				else if (i < 8)
				{
					StartNode = m_aNodes[i + 4];
					MoveSprite(m_AI.textureHandler, StartNode->x, StartNode->y);
					break;
				}
				else if (i < 12)
				{
					StartNode = m_aNodes[i - 4];
					MoveSprite(m_AI.textureHandler, StartNode->x, StartNode->y);
					break;
				}
				else
				{
					StartNode = m_aNodes[i - 12];
					MoveSprite(m_AI.textureHandler, StartNode->x, StartNode->y);
					break;
				}
			}
		}
	}

	else if (GetMouseButtonDown(0) && IsKeyDown('E'))
	{
		GetMouseLocation(mXPos, mYPos);
		for (int i = 0; i < m_aNodes.size(); i++)
		{
			if ((mXPos <= m_aNodes[i]->x + 50 && mYPos <= m_aNodes[i]->y + 50) && (mXPos >= m_aNodes[i]->x - 50 && mYPos >= m_aNodes[i]->y - 50))
			{
				if (i < 4)
				{
					EndNode = m_aNodes[i + 12];
					break;
				}
				else if (i < 8)
				{
					EndNode = m_aNodes[i + 4];
					break;
				}
				else if (i < 12)
				{
					EndNode = m_aNodes[i - 4];
					break;
				}
				else
				{
					EndNode = m_aNodes[i - 12];
					break;
				}
			}
		}
		if (ClosedList.size()>0)
		{
			ClosedList.clear();
		}
	}


	if (StartNode != NULL && EndNode != NULL)
	{
		AStarPath(StartNode, EndNode);
		StartNode = EndNode;
		EndNode = NULL;
		AIAPathNumber = 0;
	}
}

// || mPos.x >= m_aNodes[i]->x - 50     || mPos.y >= m_aNodes[i]->y - 50