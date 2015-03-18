#include "Seperation.h"
#include "Agent.h"


Seperation::Seperation()
{
}

Seperation::Seperation(Agent* in_Target)
{
	Target = in_Target;
}

Seperation::~Seperation()
{
}

Point Seperation::GetForce()
{
	Point force;

	force.x = Target->Pos.x - owner->Pos.x;
	force.y = Target->Pos.y - owner->Pos.y;

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
