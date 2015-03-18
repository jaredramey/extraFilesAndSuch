#ifndef _Allingment_h_
#define _Allingment_h_
#pragma once
#include "SteeringBehavior.h"

class Allingment : public SteeringBehavior
{
public:
	Allingment();
	Allingment(std::vector<Agent*> in_List);
	~Allingment();

	std::vector<Agent*> Agents;
	std::vector<Agent*> NeighborList;

	Point GetForce();
};
#endif
