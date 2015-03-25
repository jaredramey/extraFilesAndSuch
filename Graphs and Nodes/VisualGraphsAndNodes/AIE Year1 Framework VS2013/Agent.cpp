#include <iostream>
#include "Agent.h"


Agent::Agent() : AI()
{
}

Agent::Agent(float a_x, float a_y, float a_width, float a_height, float a_textureHandler, float a_maxVelocity)
{
	//Just setting all the fun little variables
	x = a_x;
	y = a_y;
	Pos.x = a_x;
	Pos.y = a_y;
	width = a_width;
	height = a_height;
	maxVelocity = a_maxVelocity;
	textureHandler = a_textureHandler;
}

Agent::~Agent()
{
}

void Agent::SetBehaviors(std::vector<SteeringBehavior*> in_Behaviors)
{
	//set behavior list
	BehaviorList = in_Behaviors;
	std::sort(BehaviorList.begin(), BehaviorList.end(), WeightCompare());
}

void Agent::UpdateAgent(SteeringBehavior* a_behavior, Agent* Target, Point DeltaTime)
{
	//create some points for easier access later
	Point weight;
	Point force;

	//go through behavior list
	for (int i = 0; i < BehaviorList.size(); i++)
	{
		//set the owner
		BehaviorList[i]->owner = this;
		//get and set the weight for easier access
		weight.x = BehaviorList[i]->weight;
		weight.y = BehaviorList[i]->weight;
		//get force and multiply by DeltaTime
		force = (BehaviorList[i]->GetForce() * DeltaTime);
		//multiply by force in order to get a weaker/ stronger force out of behavior
		force.x = force.x * weight.x;
		force.y = force.y * weight.y;
		//add to Agents velocity
		Velocity += force;
	}

	//Update Agents velocity and make sure it doesn't go past the cap
	if (Velocity.x > maxVelocity || Velocity.y > maxVelocity)
	{
		if (Velocity.x >= maxVelocity*1.5f)
		{
			Velocity.x = maxVelocity*1.5f;
		}
		else if (Velocity.x <= -maxVelocity*1.5)
		{
			Velocity.x = -maxVelocity*1.5;
		}
		if (Velocity.y >= maxVelocity)
		{
			Velocity.y = maxVelocity;
		}
		else if (Velocity.y <= -maxVelocity)
		{
			Velocity.y = -maxVelocity;
		}
	}
	
	//screen loop/ bounce
	if (Pos.x + (width / 2) >= 800)
	{
		Velocity.x *= -1;
		Pos.x = 800 - width;
	}
	else if (Pos.x - (width / 2) <= 0)
	{
		Velocity.x *= -1;
		Pos.x = 0 + width;
	}
	if (Pos.y + (height / 2) >= 600)
	{
		Velocity.y *= -1;
		Pos.y = 600 - height;
	}
	else if (Pos.y - (height / 2) <= 0)
	{
		Velocity.y *= -1;
		Pos.y = 0 + height;
	}

	//Update agents position
	Pos += Velocity;
	
}

void Agent::ControlOveride()
{
	//Just a control overide for simple debugging purposes
	if (IsKeyDown('W'))
	{
		Pos.y++;
	}

	if (IsKeyDown('S'))
	{
		Pos.y--;
	}

	if (IsKeyDown('A'))
	{
		Pos.x--;
	}

	if (IsKeyDown('D'))
	{
		Pos.x++;
	}
}

void Agent::CheckNeighbors(std::vector<Agent*> in_Agents)
{
	//if there are no neighbors then it will default to 0
	int numOfNeighbors = 0;

	//check neighbors
	for (int i = 0; i < in_Agents.size(); i++)
	{
		if ((in_Agents[i]->Pos.x < (Pos.x + 100.0f) && in_Agents[i]->Pos.x >(Pos.x - 100.0f)) && (in_Agents[i]->Pos.y < (Pos.y + 100.0f) && in_Agents[i]->Pos.y >(Pos.y - 100.0f)))
		{
			//if there is a neighbor then increase the number of neighbors and add the neighbor to a list for later access
			numOfNeighbors++;
			NeighborList.push_back(in_Agents[i]);
		}
	}

	//Set the neighborcount
	neighborCount = numOfNeighbors;
}

void Agent::GetPath(std::vector<GraphNode*> in_closedList)
{
	if (in_closedList.size() != 0)
	{
		closedList = in_closedList;
	}
}

void Agent::MoveOnGraphPath(float speed)
{
	GraphNode* CurrentNode;
	if (closedList.size() != 0)
	{
		int LastNode = closedList.size() - 1;

		if (NodeNumber <= closedList.size() - 1)
		{
			CurrentNode = closedList[NodeNumber];
		}
		else
		{
			CurrentNode = closedList[LastNode];
			for (int i = closedList.size() - 2; i > 0; i--)
			{
				closedList.erase(closedList.begin()+i);
			}
		}

		if (Pos.x != CurrentNode->x || Pos.y != CurrentNode->y)
		{
			if (Pos.x <= CurrentNode->x)
			{
				Pos.x += speed;
			}
			else
			{
				Pos.x -= speed;
			}

			if (Pos.y <= CurrentNode->y)
			{
				Pos.y += speed;
			}
			else
			{
				Pos.y -= speed;
			}
		}

		if (Pos.x == CurrentNode->x && Pos.y == CurrentNode->y) //(Pos.x <= (CurrentNode->x + 100.0f) && Pos.x >= (CurrentNode->x - 100.0f)) && (Pos.y <= (CurrentNode->y + 100.0f) && Pos.y >= (CurrentNode->y - 100.0f))
		{
			NodeNumber++;
		}

		MoveSprite(textureHandler, Pos.x, Pos.y);
		DrawSprite(textureHandler);
	}
}

void Agent::AvoidGraphNode(std::vector<GraphNode*> GraphNodes)
{
	for (int i = 0; i < GraphNodes.size(); i++)
	{
		if ((Pos.x <= (GraphNodes[i]->x + (width / 2)) /**/ && /**/ Pos.x >= (GraphNodes[i]->x - (width / 2))) /**/ && /**/ (Pos.y <= (GraphNodes[i]->y + (height / 2)) /**/ && /**/ Pos.y >= (GraphNodes[i]->y - (height / 2))))
		{
			if (Pos.x <= (GraphNodes[i]->x + (width / 2)) /**/ && /**/ Pos.x >= (GraphNodes[i]->x - (width / 2)))
			{
				Velocity.x *= -1;
			}

			if (Pos.y <= (GraphNodes[i]->y + (height / 2)) /**/ && /**/ Pos.y >= (GraphNodes[i]->y - (height / 2)))
			{
				Velocity.y *= -1;
			}
		}
	}
}