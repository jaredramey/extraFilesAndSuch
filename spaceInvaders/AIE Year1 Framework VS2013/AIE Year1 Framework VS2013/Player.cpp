#include "Player.h"
#include "AIE.h"

Player::Player()
{
}

void Player::SetSpriteID(unsigned int a_spriteID)
{
	spriteID = a_spriteID;
}

unsigned int Player::GetSpriteID()
{
	return spriteID;
}

void Player::SetWidth(float width)
{
	this->width = width;
}

void Player::SetHeight(float heigth)
{
	this->hieght = heigth;
}

void Player::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

float Player::GetWidth()
{
	return width;
}

float Player::GetHeight()
{
	return hieght;
}

void Player::SetSize(float a_Width, float a_Hieght)
{
	width = a_Width;
	hieght = a_Hieght;
}

float Player::GetX()
{
	return x;
}

float Player::GetY()
{
	return y;
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

void Player::Move(float a_timeStep, float a_speed)
{
	if (IsKeyDown(moveLeftKey))
	{
		x -= a_timeStep * a_speed;
		if (x < (leftMoveExtreeme + width*.5))
		{
			x = (leftMoveExtreeme + width*.5);
		}
	}

	if (IsKeyDown(moveRightKey))
	{
		x += a_timeStep * a_speed;
		if (x >(rightMoveExtreeme - width*.5))
		{
			x = (rightMoveExtreeme - width*.5);
		}
	}
	//MoveSprite(this->spriteID, this->x, this->y);
}


Player::~Player()
{
}