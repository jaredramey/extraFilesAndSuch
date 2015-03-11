#pragma once
#include <vector>

class Agent;

class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();

	Agent* owner = nullptr;

	//virtual std::vector<float> GetForce() = 0;
};

