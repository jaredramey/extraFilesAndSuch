#ifndef _Flee_h_
#define _Flee_h_
#pragma once
#include "SteeringBehavior.h"

class Flee : public SteeringBehavior
{
public:
	Flee();
	Flee(Agent* in_Target);
	~Flee();

	Agent* fTarget;

	Point GetForce();
};

#endif _Flee_h_
