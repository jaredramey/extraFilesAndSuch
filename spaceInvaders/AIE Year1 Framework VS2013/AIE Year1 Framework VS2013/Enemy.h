#pragma once

class Enemy
{
public:
	Enemy();



	struct Ships
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

		//Alien Movment Function
		/*void Move(int a_deltaTime)
		{
			for (int i = 0; i < 18; i++)
			{
				if (eCurrentDirection == eLeft)
				{
					x -= speed * a_deltaTime;
					if (eCurrentDirection == eLeft)
					{
						eCurrentDirection = eRight;
						y -= 4;
					}
				}

				if (eCurrentDirection == eRight)
				{
					x -= speed * a_deltaTime;
					if (eCurrentDirection == eRight)
					{
						eCurrentDirection = eLeft;
						y -= 4;
					}
				}
			}
		}*/
	};


	//setters
	void SetSpriteID(unsigned int a_spriteID);
	void SetSize(float a_Width, float a_Hieght);
	void SetPosition(float a_x, float a_y);
	void UpdateEnemyMove();
	void Move();
	void Draw();
	//void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme);

	//Getters
	unsigned int GetSpriteID();
	float GetWidth();
	float GetHeight();
	float GetX();
	float GetY();

	~Enemy();

private:
	unsigned int leftMoveExtreeme;
	unsigned int rightMoveExtreeme;
	unsigned int spriteID;

	float x;
	float y;

	float width;
	float height;
};

