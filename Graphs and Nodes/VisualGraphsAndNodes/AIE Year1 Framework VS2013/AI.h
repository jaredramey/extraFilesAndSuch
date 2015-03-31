#ifndef _AI_h_
#define _AI_h_
#pragma once
#include <vector>
#include "AIE.h"
#include "Point.h"
#include "SteeringBehavior.h"

class AI
{
public:
	AI();
	~AI();

	float x = 0, y = 0;
	int width = 0, height = 0;
	int textureHandler;
	Point Transfrom;
	

	void CreateAI(int a_w, int a_h, int texturePath);
	void DrawAI();
	void UpdateAI(float a_x, float a_y);
	virtual void UpdateAgent(SteeringBehavior* a_behavior, Agent* Target, Point DeltaTime) = 0;
};
#endif

