#ifndef _Agent_h_
#define _Agent_h_
#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include "AI.h"
#include "SteeringBehavior.h"
#include "Seek.h"
#include "Graph.h"
#include "GraphNode.h"

class Agent : public AI
{
public:
	//struct to compare Agent weights
	struct WeightCompare
	{
		inline bool operator() (const SteeringBehavior* left, const SteeringBehavior* right)
		{
			return(left->weight < right->weight);
		}
	};

	//Default Constructor
	Agent();
	//Custom Constructor
	Agent(float a_x, float a_y, float a_width, float a_heigt, float a_textureHandler, float a_maxVelocity);
	//Default Constructor
	~Agent();

	//essentially random variables
	float maxVelocity;
	float Magnitude;
	float neighborRadius;
	int neighborCount;

	//Custom stuff
	Point Velocity;
	Point Pos;
	std::vector<SteeringBehavior*> BehaviorList;
	std::vector<Agent*> NeighborList;
	SteeringBehavior* behavior;
	Seek* TheTarget;

	//Functions
	void SetBehaviors(std::vector<SteeringBehavior*> in_Behaviors);
	void UpdateAgent(SteeringBehavior* a_behavior, Agent* Target, Point DeltaTime);
	void ControlOveride();
	void CheckNeighbors(std::vector<Agent*> in_Agents);
	void AvoidGraphNode(std::vector<GraphNode*> GraphNodes);

	//New stuff needed to use graphs
	int NodeNumber = 0;

	Graph myGraph;
	std::vector<GraphNode*> closedList;

	void GetPath(std::vector<GraphNode*> in_closedList);
	void MoveOnGraphPath(float speed);
};
#endif
