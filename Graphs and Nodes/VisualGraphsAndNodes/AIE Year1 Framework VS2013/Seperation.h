#ifndef _Seperation_h_
#define _Seperation_h_
#pragma once
#include "SteeringBehavior.h"

class Seperation : public SteeringBehavior
{
public:
	Seperation();
	Seperation(std::vector<Agent*> in_List);
	~Seperation();
	
	Agent* Target;
	std::vector<Agent*> Agents;
	std::vector<Agent*> NeighborList;
	Point GetForce();
};
#endif
