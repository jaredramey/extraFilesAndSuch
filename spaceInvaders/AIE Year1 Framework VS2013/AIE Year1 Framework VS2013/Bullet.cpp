#include "Bullet.h"
#include "AIE.h"


Bullet::Bullet()
{
}

void Bullet::TextureID(unsigned int a_textureID)
{
	bulletTextureID = a_textureID;
}

void Bullet::Draw()
{
	if (isActive)
	{
		MoveSprite(bulletTextureID, x, y);
		DrawSprite(bulletTextureID);
	}
}

void Bullet::Update(float delta)
{
	if (y > 1000)
	{
		isActive = false;
	}

	if (isActive)
	{
		x += velocityX * delta;
		y += velocityY * delta;
	}
}

void Bullet::InitializeBullet(float a_x, float a_y, float a_velocityX, float a_velocityY, unsigned int a_textureID)
{
	x = a_x;
	y = a_y;
	velocityX = a_velocityX;
	velocityY = a_velocityY;

	isActive = true;
}

Bullet::~Bullet()
{
}
