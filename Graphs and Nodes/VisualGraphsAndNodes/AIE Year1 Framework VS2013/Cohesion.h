#ifndef _Cohesion_h_
#define _Cohesion_h_
#pragma once
#include "SteeringBehavior.h"

class Cohesion : public SteeringBehavior
{
public:
	Cohesion();
	Cohesion(std::vector<Agent*> in_List);
	~Cohesion();

	Agent* Target;
	std::vector<Agent*> Agents;
	std::vector<Agent*> NeighborList;
	Point GetForce();
};
#endif

