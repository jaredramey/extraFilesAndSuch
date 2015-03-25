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

	//check the neighbors
	//owner->CheckNeighbors(Agents);
	NeighborList = owner->NeighborList;

	//get the velocity of all the other neighbors
	for (int i = 0; i < NeighborList.size(); i++)
	{
		force.x += NeighborList[i]->Velocity.x;
		force.y += NeighborList[i]->Velocity.y;
	}

	//if there are no nieghbors, return 0
	if (NeighborList.size() == 0)
	{
		force.x = 0;
		force.y = 0;
		return force;
	}

	if (owner->neighborCount != 0)
	{
		//devide by the number of neighbors
		force.x /= owner->neighborCount;
		force.y /= owner->neighborCount;
	}

	float magnitude = sqrt((force.x * force.x) + (force.y * force.y));

	//if magnitude isn't equal to 0 then normalize
	if (magnitude != 0)
	{
		force.x = force.x / magnitude;
		force.y = force.y / magnitude;
	}

	return force;
}