#include "Cohesion.h"
#include "Agent.h"


Cohesion::Cohesion()
{
}

Cohesion::Cohesion(Agent* in_Target)
{
	Target = in_Target;
}


Cohesion::~Cohesion()
{
}

Point Cohesion::GetForce()
{
	Point force;

	if (Target->Pos.x > 0 && Target->Pos.y > 0)
	{
		force.x += Target->Pos.x;
		force.y += Target->Pos.y;

		force.x = force.x / owner->neighborCount;
		force.y = force.y / owner->neighborCount;

		force.x = force.x - owner->Pos.x;
		force.y = force.y - owner->Pos.y;

		float magnitude = std::sqrt((force.x * force.x) + (force.y * force.y));

		force.x = force.x / magnitude;
		force.y = force.y / magnitude;
	}

	else
	{
		force.x = 0;
		force.y = 0;
	}

	return force;
}