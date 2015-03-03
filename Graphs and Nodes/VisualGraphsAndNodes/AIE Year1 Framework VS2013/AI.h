#pragma once
#include "AIE.h"

class AI
{
public:
	AI();
	~AI();

	float x, y;
	int width, height;
	int textureHandler;

	void CreateAI(float a_x, float a_y, int a_w, int a_h, int texturePath);
	void DrawAI();
	void UpdateAI(float a_x, float a_y);
};

