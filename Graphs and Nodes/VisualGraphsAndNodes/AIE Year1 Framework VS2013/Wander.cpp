#include "Wander.h"
#include "Agent.h"


Wander::Wander()
{
}


Wander::~Wander()
{
}


Point Wander::GetForce()
{
	//Code based on a guide and jeffs code
	////Code made with the help of wander explination of wander behavior from http://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624
	////Addition insight on wander from Jeff's code: https://github.com/JeffreyMJohnson/AITanks/blob/dev/Tanks/source/Wander.cpp
	////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\\
	////Get the Radius
	////radius = ((owner->height / 2) + ((owner->width * owner->width) / (8*owner->height)));
	////Get the Circle Center
	//Point CircleCenter = owner->Pos + owner->Velocity;
	////Normalize it
	//float magnitude = std::sqrt((CircleCenter.x * CircleCenter.x) + (CircleCenter.y * CircleCenter.y));
	//if (CircleCenter.x != 0 && CircleCenter.y != 0)
	//{
	//	CircleCenter.x = CircleCenter.x / magnitude;
	//	CircleCenter.y = CircleCenter.y / magnitude;
	//}
	////Scale the center so it's in front of the Agent
	////Value wull have to be played with to find a working distance but for now i'm going to start with 10.0f
	//CircleCenter.x = CircleCenter.x *= 50.0f;
	//CircleCenter.y = CircleCenter.y *= 50.0f;
	////Setup displacement which is responsible for right-left turning. Displacement is allinged along the y-axis
	//Point displacement;
	//displacement.x = 0.0f;
	//displacement.y = -1.0f;
	////Scale displacement By radius
	//displacement.x = displacement.x *= radius;
	//displacement.y = displacement.y *= radius;
	////Randomly change vector direction
	//float length = std::sqrt((displacement.x * displacement.x) + (displacement.y * displacement.y));
	//displacement.x = std::cosf((float)wanderAngle * (3.14 / 180)) * length;
	//displacement.x = std::sinf((float)wanderAngle * (3.14 / 180)) * length;
	////Set a wander angle and change it slightly so the angle changes
	//int r = (rand() % angleChange + 1);
	//int s = (int)(angleChange*.5f);
	//wanderAngle += r - s;
	////Time to get the force and return it
	//Point force = CircleCenter + displacement;
	//float forceMagnitude = std::sqrt((force.x * force.x) + (force.y * force.y));
	//force.x = force.x / forceMagnitude;
	//force.y = force.y / forceMagnitude;
	//return force;

	//code based off quinn's code
	Point force;

	Point CirclePos = owner->Pos;
	CirclePos.x += owner->Velocity.x*100.0f;
	CirclePos.y += owner->Velocity.y*100.0f;

	wanderPoint = (static_cast <float> (rand() / static_cast <float> (1.0f)));
	if (wanderPoint < 0.0f) {
		wanderPoint *= -1;
	}
	while (wanderPoint > 2.0f)  {
		wanderPoint -= 2.0f;
	}

	Point RandPos;
	RandPos.x = CirclePos.x + radius * cos(wanderPoint * (3.14159265359f/180.0f));
	RandPos.y = CirclePos.y + radius * sin(wanderPoint * (3.14159265359f/180.0f));

	float randMagnitude = sqrt((RandPos.x*RandPos.x) + (RandPos.y*RandPos.y));
	RandPos.x = RandPos.x / randMagnitude;
	RandPos.y = RandPos.y / randMagnitude;

	RandPos.x = RandPos.x * radius;
	RandPos.y = RandPos.y * radius;

	force = RandPos;

	float speed = sqrt((force.x * force.x) + (force.y * force.y));

	force.x = force.x / speed;
	force.y = force.y / speed;

	force.x = force.x * owner->maxVelocity;
	force.y = force.y * owner->maxVelocity;

	//Can't figure out why it always steers towards the top right so hacky slashy it chooses a random way now
	int NegiX = rand() % 2 + 1;
	int NegiY = rand() % 2 + 1;
	if (NegiX == 1)
	{
		force.x *= -1;
	}
	if (NegiY == 2)
	{
		force.y *= -1;
	}

	return force;
}