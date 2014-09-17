#include "AIE.h"
#include "Player.h"
#include <iostream>

//start of Main menu
enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eEND

};

//For handeling movement
enum DIRSTATE
{
	eRight,
	eLeft,
	eDown
};

//Global Variables
//stuff to be displayed
const char* score1 = "00000";
const char* highScore = "00000";
const char* score2 = "00000";
const char* credit = "99";
const char* insertCoins = "00";
const char* credits = "01";
//Making the screen width and height
const int screenWidth = 672;
const int screenHieght = 780;
//Ect. variables
float xPos = 336;
float yPos = 100;
bool direction;
int leftRight;
int alienMove;
//Making direction state global
DIRSTATE eCurrentDirection = eLeft;

//Function Prototype calls
void UpdateMainMenu();
void UpdateGameState(float deltaTime);
void UpdateEnemyMove();

//Initializing structures
/*struct PlayerCannon
{
	unsigned int spriteID;
	float width;
	float hieght;
	float x;
	float y;
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	unsigned int leftMoveExtreeme;
	unsigned int rightMoveExtreeme;

	void SetSize(float a_Width, float a_Hieght)
	{
		width = a_Width;
		hieght = a_Hieght;
	}

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y + y;
	}

	void SetMovementKey(unsigned int a_moveLeft, unsigned int a_moveRight)
	{
		moveLeftKey = a_moveLeft;
		moveRightKey = a_moveRight;
	}

	void SetMoveExtreeme(unsigned int a_leftExtreeme, unsigned int a_rightExtreeme)
	{
		leftMoveExtreeme = a_leftExtreeme;
		rightMoveExtreeme = a_rightExtreeme;
	}

	void Move(float a_timeStep, float a_speed)
	{
		if (IsKeyDown(moveLeftKey))
		{
			x -= a_timeStep * a_speed;
			if (x < (leftMoveExtreeme + width*.5f))
			{
				x = (leftMoveExtreeme + width*.5f);
			}
		}

		if (IsKeyDown(moveRightKey))
		{
			x += a_timeStep * a_speed;
			if (x >(rightMoveExtreeme - width*.5f))
			{
				x = (rightMoveExtreeme - width*.5f);
			}
		}
		MoveSprite(spriteID, x, y);
	}
};
PlayerCannon player;*/

struct Enemy
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
	void Move(int a_deltaTime)
	{
		for (int i = 0; i < 18; i++)
		{
			if (eCurrentDirection == eLeft)
			{
				x -= speed * a_deltaTime;
				if (eCurrentDirection == eLeft)
				{
					eCurrentDirection == eRight;
					y -= 4;
				}
			}

			if (eCurrentDirection == eRight)
			{
				x -= speed * a_deltaTime;
				if (eCurrentDirection == eRight)
				{
					eCurrentDirection == eLeft;
					y -= 4;
				}
			}
		}
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
	SetSize(64.f, 32.f);
	SetMovementKey('A', 'D');
	Player::Player().SetSpriteID(CreateSprite("./images/cannon.png", Player().GetWidth(), Player().GetHeight(), true));
	x = screenWidth * 0.5f;
	y = 80.f;
	SetMoveExtreeme(0.0f, screenWidth);
	alienMove = 1;

	//set values for Aliens
	enemy.SetSize(64.f, 32.f);
	enemy.SetMoveExtreeme(0.0f, screenWidth);
	enemy.alienID = CreateSprite("./images/invaders/invaders_1_00.png", enemy.width, enemy.hieght, true);
	float enemyX = screenWidth * 0.2f;
	float enemyY = screenHieght * 0.7f;
	enemy.speed = .04f;

	for (int i = 0; i < 18; ++i)
	{
		alienShips[i].alienID = CreateSprite("./images/invaders/invaders_1_00.png", 64, 32, true);
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
	AddFont(invadersFont);

	//Set gamestate to Main menu
	GAMESTATES eCurrentState = eMAIN_MENU;

	//Game Loop
	do
	{

		ClearScreen();
		float deltaT = GetDeltaTime();
		switch (eCurrentState)
		{
			//pointer to start at later when exiting gamestate
		start:
		case eMAIN_MENU:
			//Call function for main menu
			UpdateMainMenu();

			//if enter is pressed change state to gameplay
			if (IsKeyDown(257))
			{
				eCurrentState = eGAMEPLAY;
			}

			break;

		case eGAMEPLAY:
			//Game function
			UpdateGameState(GetDeltaTime());

			//if ESC is pressed then exit to main menu
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


	DestroySprite(spriteID);
	//DestroySprite(arcadeMarquee);

	Shutdown();

	return 0;
}


void UpdateMainMenu()
{
	//Everything to make main menu
	DrawSprite(arcadeMarquee);
	MoveSprite(arcadeMarquee, marqueeXPos, marqueeYPos);
	SetFont(invadersFont);
	DrawString(insertCoins, screenWidth * 0.37f, screenHieght * 0.5f);
	DrawString(credits, screenWidth * 0.3f, screenHieght * 0.5f);
	DrawString("PRESS ENTER TO START", screenWidth * 0.31f, screenHieght * 0.45);

}

void UpdateGameState(float deltaTime)
{
	//playing the game

	//player movement handled by player struct
	Move(GetDeltaTime(), 150.f);
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);

	//alienShips[17].move(GetDeltaTime(), 100.f);
	//enemy.Move(GetDeltaTime());
	UpdateEnemyMove();

	//Draw Alien Ships
	for (int i = 0; i < 18; ++i)
	{
		DrawSprite(alienShips[i].alienID);
		//MoveSprite(alienShips[i].alienID, alienShips[i].x, alienShips[i].y);
	}

	//draw line to show where the aliens are trying to get to
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
			if (alienShips[i].x > (screenWidth-30)) {
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