#ifndef _Cohesion_h_
#define _Cohesion_h_
#pragma once
#include "SteeringBehavior.h"

class Cohesion : public SteeringBehavior
{
public:
	Cohesion();
	Cohesion(Agent* in_Target);
	~Cohesion();

	Agent* Target;
	Point GetForce();
};
#endif

