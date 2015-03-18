#ifndef _Seperation_h_
#define _Seperation_h_
#pragma once
#include "SteeringBehavior.h"

class Seperation : public SteeringBehavior
{
public:
	Seperation();
	Seperation(Agent* in_Target);
	~Seperation();
	
	Agent* Target;
	Point GetForce();
};
#endif
