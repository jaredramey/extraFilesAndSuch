#include "Player.h"
#include "AIE.h"

Player::Player()
{
}

void Player::SetSpeed(float a_speed)
{
	speed = a_speed;
}

float Player::GetSpeed()
{
	return speed;
}

void Player::SetMovementKey(unsigned int a_moveLeft, unsigned int a_moveRight)
{
	moveLeftKey = a_moveLeft;
	moveRightKey = a_moveRight;
}

void Player::SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme)
{
	leftMoveExtreeme = a_leftExtreeme;
	rightMoveExtreeme = a_rightExtreeme;
}

void Player::Shoot(unsigned int a_textureID, float delta)
{
	if (IsKeyDown(32) && currentRealodBulletTime >= maxBulletReloadTime)
	{
			GetInactiveBullet().InitializeBullet(GetX(), GetY(), 0, 100, a_textureID);
	}

	currentRealodBulletTime += delta;
}

Bullet& Player::GetInactiveBullet()
{
	if (setTextures == false)
	{
		for (int i = 0; i < Max_Bullets; i++)
		{
			bullets[i].bulletTextureID = CreateSprite("./images/invaders/invaders_5_00.png", 15, 60, true);
		}
		setTextures = true;
	}
	for (int i = 0; i < Max_Bullets; i++)
	{
		if (!bullets[i].isActive && currentRealodBulletTime >= maxBulletReloadTime)
		{
			return bullets[i];
		}
		
	}

	return bullets[0];
}

void Player::Update(float delta)
{
	if (IsKeyDown(moveLeftKey))
	{
		x -= delta * speed;
		if (x < (leftMoveExtreeme + width*.5f))
		{
			x = (leftMoveExtreeme + width*.5f);
		}
	}

	if (IsKeyDown(moveRightKey))
	{
		x += delta * speed;
		if (x >(rightMoveExtreeme - width*.5f))
		{
			x = (rightMoveExtreeme - width*.5f);
		}
	}
}

void Player::Draw()
{
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}


Player::~Player()
{
}