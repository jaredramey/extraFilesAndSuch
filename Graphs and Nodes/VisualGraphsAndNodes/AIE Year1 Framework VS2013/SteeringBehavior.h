#ifndef _SteeringBehavior_h_
#define _SteeringBehavior_h_
#pragma once
#include <vector>
#include "Point.h"

class Agent;

class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();

	Agent* owner;
	
	virtual Point GetForce() = 0;
};

#endif
