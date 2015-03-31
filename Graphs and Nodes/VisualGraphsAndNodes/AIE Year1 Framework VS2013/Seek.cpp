#include "Seek.h"
#include "Agent.h"

Seek::Seek() : SteeringBehavior()
{
}

Seek::Seek(Agent* in_target)
{
	sTarget = in_target;
}

Seek::~Seek()
{
}

Point Seek::GetForce()
{
	//Get distance between the agent and it's target so it can get closer
	Point force = sTarget->Pos - owner->Pos;
	//Normalize
	float magnitude = std::sqrt((force.x * force.x) + (force.y * force.y));
	force.x = force.x / magnitude;
	force.y = force.y / magnitude;
	//times by max velocity
	force.x = force.x * owner->maxVelocity;
	force.y = force.y * owner->maxVelocity;
	//return force
	return force - owner->Velocity;
}
