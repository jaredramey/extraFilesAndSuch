#pragma once
#include <vector>
#include "AIE.h"

class AI
{
public:
	AI();
	~AI();

	float AI_X, AI_Y;
	int width, height;
	int textureHandler;
	//std::vector<float> transform;
	

	void CreateAI(int a_w, int a_h, int texturePath);
	void DrawAI();
	void UpdateAI(float a_x, float a_y);
	virtual void UpdateAgent(float a_x, float a_y);
};

