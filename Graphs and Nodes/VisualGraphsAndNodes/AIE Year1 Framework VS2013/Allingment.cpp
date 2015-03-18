#include "Allingment.h"
#include "Agent.h"


Allingment::Allingment()
{
}

Allingment::Allingment(std::vector<Agent*> in_List)
{
	Agents = in_List;
}


Allingment::~Allingment()
{
}

Point Allingment::GetForce()
{
	Point force;

	owner->CheckNeighbors(Agents);
	NeighborList = owner->NeighborList;

	for (int i = 0; i < NeighborList.size(); i++)
	{
		force.x += NeighborList[i]->Velocity.x;
		force.y += NeighborList[i]->Velocity.y;
	}

	if (NeighborList.size() == 0)
	{
		force.x = 0;
		force.y = 0;
		return force;
	}

	force.x /= owner->neighborCount;
	force.y /= owner->neighborCount;

	float magnitude = sqrt((force.x * force.x) + (force.y * force.y));

	force.x = force.x / magnitude;
	force.y = force.y / magnitude;

	return force;
}