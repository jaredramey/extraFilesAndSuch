#ifndef _Allingment_h_
#define _Allingment_h_
#pragma once
#include "SteeringBehavior.h"

class Allingment : public SteeringBehavior
{
public:
	Allingment();
	~Allingment();

	Point GetForce();
};
#endif
