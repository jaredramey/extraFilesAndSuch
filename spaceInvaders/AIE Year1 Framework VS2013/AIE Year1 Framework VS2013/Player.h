#pragma once
#include "Bullet.h"
const int Max_Bullets = 20;

class Player
{
private:
	unsigned int spriteID;
	float width;
	float hieght;
	float x;
	float y;
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	unsigned int leftMoveExtreeme;
	unsigned int rightMoveExtreeme;

public:
	Player();

	Bullet bullets[Max_Bullets];
	float currentRealodBulletTime = 0.0f;
	float maxBulletReloadTime = 0.5f;
	bool setTextures = false;

	void SetSize(float a_Width, float a_Hieght);
	void SetPosition(float a_x, float a_y);
	void SetMovementKey(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme);
	void Move(float a_timeStep, float a_speed);

	void Shoot(unsigned int textureID, float delta);
	Bullet& GetInactiveBullet();

	void SetSpriteID(unsigned int spriteID);
	unsigned int GetSpriteID();

	void SetWidth(float width);
	void SetHeight(float heigth);

	float GetWidth();
	float GetHeight();

	//void SetX();
	//void SetY();

	float GetX();
	float GetY();

	~Player();
};

