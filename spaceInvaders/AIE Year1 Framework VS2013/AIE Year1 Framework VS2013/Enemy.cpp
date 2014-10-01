#include "Enemy.h"
#include "AIE.h"


Enemy::Enemy()
{
	isActive = true;
}

void Enemy::Update(float delta)
{
	bool thisDirection = false;

	for (int i = 0; i < 18; i++)
	{
		if (isActive == true && direction == 1)
		{
			x -= .04f;
			if (x < 30) {
				thisDirection = true;
			}
		}

		if (direction == 2)
		{
			x += .04f;
			if (x >(672 - 30)) {
				thisDirection = true;
			}
		}

		//MoveSprite(spriteID, x, y);
	}

	if (thisDirection == true)
	{
		//Change direction from left to right
		if (direction == 1) //Continue Here
		{
			direction = 2;
		}

		//change the direction from right to left
		else
		{
			direction = 1;
		}

			if (y > 0)
			{

				y -= 4.f;

			}
		

	}
}

void Enemy::SetDirection(int a_direction)
{
	direction = a_direction;
}

int Enemy::GetDirection()
{
	return direction;
}

void Enemy::SetSpeed(float a_speed)
{
	speed = a_speed;
}

float Enemy::GetSpeed()
{
	return speed;
}

void Enemy::SetIsActive(bool a_isActive)
{
	isActive = a_isActive;
}

bool Enemy::GetIsActive()
{
	return isActive;
}

void Enemy::Draw()
{
	if (isActive)
	{
		MoveSprite(spriteID, x, y);
		DrawSprite(spriteID);
	}
}

/*void Enemy::UpdateEnemyMove()
{
	//loop to handel enemies moving left, right and down
	direction = false;

	for (int i = 0; i < 18; i++)
	{
		if (eCurrentDirection == eLeft)
		{
			alienShips[i].x -= .04f;
			if (alienShips[i].x < 30) {
				direction = true;
			}
		}

		if (eCurrentDirection == eRight)
		{
			alienShips[i].x += .04f;
			if (alienShips[i].x >(screenWidth - 30)) {
				direction = true;
			}
		}

		MoveSprite(alienShips[i].alienID, alienShips[i].x, alienShips[i].y);
	}

	if (direction == true)
	{
		//Change direction from left to right
		if (eCurrentDirection == eLeft) //Continue Here
		{
			eCurrentDirection = eRight;
		}

		//change the direction from right to left
		else
		{
			eCurrentDirection = eLeft;
		}

		for (int i = 0; i < 18; i++)
		{
			if (alienShips[i].y > 0)
			{

				alienShips[i].y -= 4.f;

			}

			//see if I can get this to work....
			if (alienShips[i].y <= 40)
			{
				SetFont(invadersFont);
				DrawString("GAME OVER", screenWidth * 0.31f, screenHieght * 0.5f);

			}
		}

	}
}
*/

Enemy::~Enemy()
{
}
