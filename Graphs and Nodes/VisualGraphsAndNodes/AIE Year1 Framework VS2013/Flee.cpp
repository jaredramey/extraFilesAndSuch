#include "Flee.h"
#include "Agent.h"


Flee::Flee() : SteeringBehavior()
{

}

Flee::Flee(Agent* in_Target)
{
	fTarget = in_Target;
}


Flee::~Flee()
{
}

Point Flee::GetForce()
{
	//force starts out as a pos away from the target
	Point force = fTarget->Pos + owner->Pos;
	//Get a magnitude and normalize
	float magnitude = std::sqrt((force.x * force.x) + (force.y * force.y));

	//had a devided by 0 problem so give a little protection from that
	if (magnitude != 0)
	{
		force.x = force.x / magnitude;
		force.y = force.y / magnitude;
	}

	//times by velocity
	force.x = force.x * owner->maxVelocity;
	force.y = force.y * owner->maxVelocity;

	//return force
	return force + owner->Velocity;
}
