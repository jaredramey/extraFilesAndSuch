#pragma once
#include "SteeringBehavior.h"

class Seek : public SteeringBehavior
{
public:
	Seek();
	~Seek();

	Agent* Target;

	//std::vector<float> GetForce() = 0;
};

