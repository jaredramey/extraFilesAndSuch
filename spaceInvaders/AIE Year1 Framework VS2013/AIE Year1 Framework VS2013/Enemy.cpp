#include "Enemy.h"
#include "AIE.h"


Enemy::Enemy()
{
}

void Enemy::SetSpriteID(unsigned int a_spriteID)
{
	spriteID = a_spriteID;
}

void Enemy::SetSize(float a_Width, float a_Hieght)
{
	width = a_Width;
	height = a_Hieght;
}

void Enemy::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

float Enemy::GetWidth()
{
	return width;
}

float Enemy::GetHeight()
{
	return height;
}

float Enemy::GetX()
{
	return x;
}

float Enemy::GetY()
{
	return y;
}

void Enemy::Move()
{

}

void Enemy::Draw()
{
	
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
