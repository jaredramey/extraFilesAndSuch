#pragma once
#include "Bullet.h"
#include "Entity.h"

const int Max_Bullets = 20;

class Player : public Entity
{
private:
	float speed;
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	unsigned int leftMoveExtreeme;
	unsigned int rightMoveExtreeme;

public:
	Player();

	Bullet bullets[Max_Bullets];
	float currentRealodBulletTime = 0.0f;
	float maxBulletReloadTime = 1.0f;
	bool setTextures = false;

	void SetMovementKey(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme);

	virtual void Update(float delta);
	virtual void Draw();

	void Shoot(unsigned int textureID, float delta);
	Bullet& GetInactiveBullet();

	void SetSpeed(float a_speed);
	float GetSpeed();

	~Player();
};

