#include "Cohesion.h"
#include "Agent.h"


Cohesion::Cohesion()
{
}

Cohesion::Cohesion(std::vector<Agent*> in_List)
{
	Agents = in_List;
}


Cohesion::~Cohesion()
{
}

Point Cohesion::GetForce()
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
		force.x = force.x /= owner->neighborCount;
		force.y = force.y /= owner->neighborCount;

		float magnitude = sqrt((force.x * force.x) + (force.y * force.y));

		force.x = force.x / magnitude;
		force.y = force.y / magnitude;
	}

	NeighborList.clear();

	return force;
}