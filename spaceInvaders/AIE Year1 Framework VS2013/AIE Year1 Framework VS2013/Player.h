#pragma once
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

	void SetSpriteID(unsigned int spriteID);
	unsigned int GetSpriteID();

	void SetWidth(float fWidth);
	void SetHeight(float fHeight);

	float GetWidth();
	float GetHeight();

	void SetX(float x);
	void SetY(float y);

	float GetX();
	float GetY();

	void SetSize(float a_Width, float a_Hieght);
	void SetPosition(float a_x, float a_y);
	void SetMovementKey(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme);
	void Move(float a_timeStep, float a_speed);

	Player();
	~Player();
};

