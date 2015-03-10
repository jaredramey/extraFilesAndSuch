#include "AI.h"


AI::AI()
{
}


AI::~AI()
{
}

void AI::CreateAI(int a_w, int a_h, int texturePath)
{
	width = a_w;
	height = a_h;
	textureHandler = texturePath;
}

void AI::DrawAI()
{
	DrawSprite(textureHandler);
}

void AI::UpdateAI(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void AI::UpdateAgent(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}