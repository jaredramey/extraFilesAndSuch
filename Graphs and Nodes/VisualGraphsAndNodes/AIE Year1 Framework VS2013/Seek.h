#ifndef _Seek_h
#define _Seek_h_
#pragma once
#include "SteeringBehavior.h"

class Seek : public SteeringBehavior
{
public:
	Seek();
	Seek(Agent* in_target);
	~Seek();

	Agent* sTarget;

	Point GetForce();
};

#endif _Seek_h_

