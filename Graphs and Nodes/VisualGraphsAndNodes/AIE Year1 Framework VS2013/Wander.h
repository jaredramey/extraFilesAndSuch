#ifndef _Wander_h_
#define _Wander_h_
#pragma once
#include "SteeringBehavior.h"
class Wander : public SteeringBehavior
{
public:
	Wander();
	~Wander();
	float radius = 100.0f;
	float offset;
	float jitter = -1.0f;
	int wanderAngle = 0;
	int angleChange = 10;
	float wanderPoint;

	Point GetForce();
};

#endif

