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
	Point force = fTarget->Pos + owner->Pos;
	float magnitude = std::sqrt((force.x * force.x) + (force.y * force.y));

	if (magnitude != 0)
	{
		force.x = force.x / magnitude;
		force.y = force.y / magnitude;
	}

	force.x = force.x * owner->maxVelocity;
	force.y = force.y * owner->maxVelocity;
	//if (force.x > owner->maxVelocity || force.y > owner->maxVelocity)
	//{
	//	if (force.x > owner->maxVelocity)
	//	{
	//		force.x = owner->maxVelocity;
	//	}
	//	if (force.y > owner->maxVelocity)
	//	{
	//		force.y = owner->maxVelocity;
	//	}
	//}
	return force + owner->Velocity;
}
