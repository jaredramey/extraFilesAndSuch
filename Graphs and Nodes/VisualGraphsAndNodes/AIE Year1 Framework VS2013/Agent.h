#pragma once
#include "AI.h"
#include "SteeringBehavior.h"

class Agent : public AI
{
public:
	Agent();
	~Agent();

	//Velocity[0] = x, Velocity[1] = y
	std::vector<float> Velocity = {0, 0};
	std::vector<float> Pos = {10, 10};
	float maxVelocity;
	SteeringBehavior behavior;

	void UpdateAgent(float a_x, float a_y) = 0;

};

