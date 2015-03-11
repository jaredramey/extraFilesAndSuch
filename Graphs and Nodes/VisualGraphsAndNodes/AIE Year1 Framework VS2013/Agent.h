#ifndef _Agent_h_
#define _Agent_h_
#pragma once
#include "AI.h"
#include "SteeringBehavior.h"
#include "Seek.h"

class Agent : public AI
{
public:
	Agent();
	Agent(float a_x, float a_y, float a_width, float a_heigt, float a_textureHandler, float a_maxVelocity);
	~Agent();

	Point Velocity;
	Point Pos;
	float maxVelocity;
	float Magnitude;
	SteeringBehavior* behavior;
	Seek* TheTarget;

	void UpdateAgent(SteeringBehavior* a_behavior, Agent* Target, Point DeltaTime);
	void ControlOveride();

};
#endif
