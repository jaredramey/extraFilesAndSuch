#ifndef _Agent_h_
#define _Agent_h_
#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include "AI.h"
#include "SteeringBehavior.h"
#include "Seek.h"

class Agent : public AI
{
public:
	//Example function for sorting to base sorting the list off of
	/*struct NodeCompare
	{
		inline bool operator() (const GraphNode* left, const GraphNode* right)
		{
			return (left->nodeWeight < right->nodeWeight);
		}
	};*/

	struct WeightCompare
	{
		inline bool operator() (const SteeringBehavior* left, const SteeringBehavior* right)
		{
			return(left->weight < right->weight);
		}
	};

	Agent();
	Agent(float a_x, float a_y, float a_width, float a_heigt, float a_textureHandler, float a_maxVelocity);
	~Agent();

	Point Velocity;
	Point Pos;
	float maxVelocity;
	float Magnitude;
	std::vector<SteeringBehavior*> BehaviorList;
	SteeringBehavior* behavior;
	Seek* TheTarget;

	void SetBehaviors(std::vector<SteeringBehavior*> in_Behaviors);
	void UpdateAgent(SteeringBehavior* a_behavior, Agent* Target, Point DeltaTime);
	void ControlOveride();

};
#endif
