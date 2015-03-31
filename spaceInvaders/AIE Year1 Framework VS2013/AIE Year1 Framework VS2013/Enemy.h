#pragma once
#include <iostream>
#include <vector>
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy();

	/*struct Ships
	{
		unsigned int alienID;
		unsigned int speed;

		float x;
		float y;

		float width;
		float hieght;
		void SetSize(float a_Width, float a_Hieght)
		{
			width = a_Width;
			hieght = a_Hieght;
		}

		unsigned int leftMoveExtreeme;
		unsigned int rightMoveExtreeme;
		void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme)
		{
			leftMoveExtreeme = a_leftExtreeme;
			rightMoveExtreeme = a_rightExtreeme;
		}
	};*/

	//std::vector<int> test;

	virtual void Update(float delta);
	virtual void Draw();

	void SetSpeed(float a_speed);
	float GetSpeed();

	void SetDirection(int a_direction);
	int GetDirection();

	void SetIsActive(bool a_isActive);
	bool GetIsActive();

	~Enemy();

private:

	bool isActive;
	float speed;
	int direction;
	
};

