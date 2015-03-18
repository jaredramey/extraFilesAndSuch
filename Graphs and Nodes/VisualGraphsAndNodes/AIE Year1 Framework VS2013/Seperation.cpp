#include "Seperation.h"
#include "Agent.h"


Seperation::Seperation()
{
}

Seperation::Seperation(std::vector<Agent*> in_List)
{
	Agents = in_List;
}

Seperation::~Seperation()
{
}

Point Seperation::GetForce()
{
	Point force;

	owner->CheckNeighbors(Agents);
	NeighborList = owner->NeighborList;

	//Average out force
	for (int i = 0; i < NeighborList.size(); i++)
	{
		force.x += NeighborList[i]->Pos.x - owner->Pos.x;
		force.y += NeighborList[i]->Pos.y - owner->Pos.y;
	}

	if (force.x != 0 && force.y != 0)
	{
		force.x *= -1;
		force.y *= -1;

		float magnitude = std::sqrt((force.x * force.x) + (force.y * force.y));

		force.x = force.x / magnitude;
		force.y = force.y / magnitude;
	}

	return force;
}
