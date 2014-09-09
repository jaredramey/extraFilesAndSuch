#include "AIE.h"
#include <iostream>

//start of Main menu
enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eEND

};

enum DIRSTATE
{
	eRight,
	eLeft,
	eDown
};

//Global Variables
//stuff to be displayed
char score1[10] = "00000";
char highScore[10] = "00000";
char score2[10] = "00000";
char credit[10] = "99";
char insertCoins[10] = "00";
char credits[10] = "01";


int alienMove;

const int screenWidth = 672;
const int screenHieght = 780;
float xPos = 336;
float yPos = 100;
bool direction;
int leftRight;

DIRSTATE eCurrentDirection = eLeft;

//Function Prototype calls
void UpdateMainMenu();
void UpdateGameState(float deltaTime);
void UpdateEnemyMove();
//void CreateEnemies();

//Initializing structurs

struct PlayerCannon
{
	unsigned int spriteID;

	float width;
	float hieght;
	void SetSize(float a_Width, float a_Hieght)
	{
		width = a_Width;
		hieght = a_Hieght;
	}

	float x;
	float y;
	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y + y;
	}

	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	void SetMovementKey(unsigned int a_moveLeft, unsigned int a_moveRight)
	{
		moveLeftKey = a_moveLeft;
		moveRightKey = a_moveRight;
	}

	unsigned int leftMoveExtreeme;
	unsigned int rightMoveExtreeme;
	void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme)
	{
		leftMoveExtreeme = a_leftExtreeme;
		rightMoveExtreeme = a_rightExtreeme;
	}

	void Move(float a_timeStep, float a_speed)
	{
		if (IsKeyDown(moveLeftKey))
		{
			xPos -= a_timeStep * a_speed;
			if (xPos < (leftMoveExtreeme + width*.5f))
			{
				xPos = (leftMoveExtreeme + width*.5f);
			}
		}

		if (IsKeyDown(moveRightKey))
		{
			xPos += a_timeStep * a_speed;
			if (xPos >(rightMoveExtreeme - width*.5f))
			{
				xPos = (rightMoveExtreeme - width*.5f);
			}
		}
		MoveSprite(spriteID, x, y);
	}
};
PlayerCannon player;

struct Enemy
{
	unsigned int alienID;

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
	bool Move( int a_Direction)
	{
		if (a_Direction == eLeft)
		{
			x -= 1;
			if (x <= 0)
			{
				return true;
			}
		}
		if (a_Direction == eRight)
		{
			x += 1.f;
			if ( x >= screenWidth)
			{
				return true;
			}
		}
		if (a_Direction == eDown)
		{
			y -= screenHieght * 0.2f;
		}
		return false;
	}
};
Enemy enemy; 

Enemy alienShips[18];




//ect Sprites
int arcadeMarquee;
float marqueeXPos = 336;
float marqueeYPos = 390;




//Add Invaders Font
const char* invadersFont = "./fonts/invaders.fnt";

int main(int argc, char* argv[])
{


	//screen and window set up
	Initialise(672, 780, false, "Space Invaders Clone");


	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", 672, 780, true);


	//set values for player
	player.SetSize(64.f, 32.f);
	player.SetMovementKey('A', 'D');
	player.spriteID = CreateSprite("./images/cannon.png", player.width, player.hieght, true);
	player.x = screenWidth * 0.5f;
	player.y = 80.f;
	player.SetMoveExtreeme(0.0f, screenWidth);
	alienMove = 1;
	

	//set values for Aliens
	enemy.SetSize(64.f, 32.f);
	enemy.SetMoveExtreeme(0.0f, screenWidth);
	enemy.alienID = CreateSprite("./images/invaders/invaders_1_00.png", enemy.width, enemy.hieght, true);

	float enemyX = screenWidth * 0.2f;
	float enemyY = screenHieght * 0.7f;

	for (int i = 0; i < 18; ++i)
	{
		alienShips[i].alienID = CreateSprite("./images/invaders/invaders_1_00.png", 64, 62, true);
		alienShips[i].x = enemyX;
		alienShips[i].y = enemyY;
		MoveSprite(alienShips[i].alienID, enemyX, enemyY);
		enemyX += 0.12 * screenWidth;
		if (enemyX > screenWidth * 0.8f)
		{
			enemyX = screenWidth * 0.2f;
			enemyY -= 0.08 * screenHieght;
		}
	}




	//Space invaders font


	GAMESTATES eCurrentState = eMAIN_MENU;
	



	AddFont(invadersFont);


	//Game Loop
	do
	{

		ClearScreen();
		float deltaT = GetDeltaTime();
		switch (eCurrentState)
		{
		start:
		case eMAIN_MENU:
			//Call function for main menu
			UpdateMainMenu();
			if (IsKeyDown(257))
			{
				eCurrentState = eGAMEPLAY;
			}

			break;

		case eGAMEPLAY:
			//Game function
			UpdateGameState(GetDeltaTime());
			if (IsKeyDown(256))
			{
				eCurrentState = eMAIN_MENU;
				goto start;
			}

			break;

		case eEND:
			break;

		default:
			break;
		}

	} while (FrameworkUpdate() != true);


	DestroySprite(player.spriteID);
	//DestroySprite(arcadeMarquee);

	Shutdown();

	return 0;
}


void UpdateMainMenu()
{
	DrawSprite(arcadeMarquee);
	MoveSprite(arcadeMarquee, marqueeXPos, marqueeYPos);
	SetFont(invadersFont);
	DrawString(insertCoins, screenWidth * 0.37f, screenHieght * 0.5f);
	DrawString(credits, screenWidth * 0.3f, screenHieght * 0.5f);
	DrawString("PRESS ENTER TO START", screenWidth * 0.31f, screenHieght * 0.45);

}

void UpdateGameState(float deltaTime)
{
	//player movement handled by player struct
	player.Move(GetDeltaTime(), 150.f);
	MoveSprite(player.spriteID, xPos, yPos);
	DrawSprite(player.spriteID);
	
	//alienShips[17].move(GetDeltaTime(), 100.f);
	//enemy.Move(eCurrentDirection);
	UpdateEnemyMove();

	//Draw Alien Ships
	for (int i = 0; i < 18; ++i)
	{
		DrawSprite(alienShips[i].alienID);
	}


	
	DrawLine(0, 40, screenWidth, 40, SColour(0x00, 0xFC, 0x00, 0xFF));

	//Set Invaders font
	SetFont(invadersFont);

	//Screen text
	DrawString("SCORE <1>", screenWidth * 0.025f, screenHieght - 2);
	DrawString("HIGH SCORE", screenWidth * 0.39f, screenHieght - 2);
	DrawString("SCORE <2>", screenWidth * 0.79f, screenHieght - 2);
	DrawString(score1, screenWidth * 0.05f, screenHieght - 30);
	DrawString(highScore, screenWidth * 0.4345f, screenHieght - 30);
	DrawString(score2, screenWidth * 0.82f, screenHieght - 30);
}

void UpdateEnemyMove()
{
	direction = false;

		for (int i = 0; i < 18; i++)
		{
			if (eCurrentDirection == eLeft)
			{
				alienShips[i].x -= .025f;
				if (alienShips[i].x < 0) {
					direction = true;
				}
			}

			if (eCurrentDirection == eRight)
			{
				alienShips[i].x += .025f;
				if (alienShips[i].x > screenWidth) {
					direction = true;
				}
			}

			MoveSprite(alienShips[i].alienID, alienShips[i].x, alienShips[i].y);
		}
	 
		if (direction == true)
		{
			//Change direction from left to right
			if (eCurrentDirection == eLeft ) //Continue Here
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

					alienShips[i].y -= 1.f;

				}

				else if (alienShips[i].y <= 40)
				{
					SetFont(invadersFont);
					DrawString("GAME OVER", screenWidth * 0.31f, screenHieght * 0.5f);

				}
			}

		}
}

/*void CreateEnemies()
{
float enemyX = screenWidth * 0.2f;
float enemyY = screenHieght * 0.7f;
for (int i = 0; i < 18; i++)
{
alienShips[i] = CreateSprite("./images/invaders/invaders_1_00.png", 64, 62, true);
MoveSprite( alienShips[i], enemyX, enemyY);
enemyX += 0.12 * screenWidth;
if (enemyX < screenWidth * 0.8f)
{
enemyX = screenWidth * 0.2f;
enemyY = 0.08 * screenHieght;
}
}
}*/