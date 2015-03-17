#include "Agent.h"


Agent::Agent() : AI()
{
}

Agent::Agent(float a_x, float a_y, float a_width, float a_height, float a_textureHandler, float a_maxVelocity)
{
	x = a_x;
	y = a_y;
	Pos.x = a_x;
	Pos.y = a_y;
	width = a_width;
	height = a_height;
	maxVelocity = a_maxVelocity;
	textureHandler = a_textureHandler;
}

Agent::~Agent()
{
}

void Agent::SetBehaviors(std::vector<SteeringBehavior*> in_Behaviors)
{
	BehaviorList = in_Behaviors;
	std::sort(BehaviorList.begin(), BehaviorList.end(), WeightCompare());
}

void Agent::UpdateAgent(SteeringBehavior* a_behavior, Agent* Target, Point DeltaTime)
{
	/*behavior = a_behavior;
	behavior->owner = this;
	Velocity += (behavior->GetForce() * DeltaTime);*/
	for (int i = 0; i < BehaviorList.size(); i++)
	{
		BehaviorList[i]->owner = this;
		Velocity += BehaviorList[i]->GetForce() * DeltaTime;
	}

	if (Velocity.x > maxVelocity || Velocity.y > maxVelocity)
	{
		if (Velocity.x >= maxVelocity*1.5f)
		{
			Velocity.x = maxVelocity*1.5f;
		}
		else if (Velocity.x <= -maxVelocity*1.5)
		{
			Velocity.x = -maxVelocity*1.5;
		}
		if (Velocity.y >= maxVelocity)
		{
			Velocity.y = maxVelocity;
		}
		else if (Velocity.y <= -maxVelocity)
		{
			Velocity.y = -maxVelocity;
		}
	}
	
	//screen loop/ bounce
	if (Pos.x + (width / 2) >= 800)
	{
		Velocity.x *= -1;
		Pos.x = 800 - width;
	}
	else if (Pos.x - (width / 2) <= 0)
	{
		Velocity.x *= -1;
		Pos.x = 0 + width;
	}
	if (Pos.y + (height / 2) >= 600)
	{
		Velocity.y *= -1;
		Pos.y = 600 - height;
	}
	else if (Pos.y - (height / 2) <= 0)
	{
		Velocity.y *= -1;
		Pos.y = 0 + height;
	}

	Pos += Velocity;
	
}

void Agent::ControlOveride()
{
	if (IsKeyDown('W'))
	{
		Pos.y++;
	}

	if (IsKeyDown('S'))
	{
		Pos.y--;
	}

	if (IsKeyDown('A'))
	{
		Pos.x--;
	}

	if (IsKeyDown('D'))
	{
		Pos.x++;
	}
}