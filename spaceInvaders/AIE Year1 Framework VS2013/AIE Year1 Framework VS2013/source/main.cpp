#include "AIE.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <vector>

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

DIRSTATE eCurrentDirection;

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
float deltaT;
bool direction;
int leftRight;
int alienMove;
int numAliens = 18;

//Declaring what I need from classes
Player player = Player();
Enemy enemy = Enemy();
//Enemy aliens = Enemy();
Bullet bullet = Bullet();

std::vector<Enemy> aliens;


//Function Prototype calls
void UpdateMainMenu();
void UpdateGameState(float deltaTime);
//void UpdateEnemyMove();

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



//ect Sprites
int arcadeMarquee;
float marqueeXPos = 336;
float marqueeYPos = 390;

//Add Invaders Font
const char* invadersFont = "./fonts/invaders.fnt";

int main(int argc, char* argv[])
{
	aliens.push_back(enemy);

	//screen and window set up
	Initialise(672, 780, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", 672, 780, true);

	//set values for player
	//SetSize(64.f, 32.f);
	player.SetHeigth(32.f);
	player.SetWidth(64);
	player.SetMovementKey('A', 'D');
	player.SetSpriteID(CreateSprite("./images/cannon.png", player.GetWidth(), player.GetHeigth(), true));
	player.SetPosition(screenWidth * 0.5, 80);
	player.SetMoveExtreeme(0.0, screenWidth);
	player.SetSpeed((float)screenWidth);
	alienMove = 1;

	//set values for Aliens
	//enemy.SetSize(64.f, 32.f);
	//unsigned int ship = (CreateSprite("./images/invaders/invaders_1_00.png", enemy.GetWidth(), enemy.GetHeigth(), true));
	float enemyX = screenWidth * 0.2f;
	float enemyY = screenHieght * 0.7f;
	

	for (int i = 0; i < 18; ++i)
	{
		aliens[i].SetSize(64.f, 32.f);
		aliens[i].SetSpriteID(CreateSprite("./images/invaders/invaders_1_00.png", aliens[i].GetWidth(), aliens[i].GetHeigth(), true));
		aliens[i].SetX(enemyX);
		aliens[i].SetY(enemyY);
		MoveSprite(aliens[i].GetSpriteID(), aliens[i].GetX(), aliens[i].GetY());
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
		deltaT = GetDeltaTime();
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


	DestroySprite(player.GetSpriteID());
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

	//Bullet Time
	player.Shoot(bullet.bulletTextureID, GetDeltaTime());
	for (int i = 0; i < Max_Bullets; i++)
	{
		player.bullets[i].Update(0.01f);
		player.bullets[i].Draw();
	}
	//player movement handled by player class
	player.Update(deltaT);
	player.Draw();

	//Goto updatenemymove for alien movement
	for (int i = 0; i < 18; i++)
	{
		aliens[i].Update(deltaT);
	}

	//Draw Alien Ships
	for (int i = 0; i < 18; ++i)
	{
		DrawSprite(aliens[i].GetSpriteID());
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

/*void UpdateEnemyMove()
{
	//loop to handel enemies moving left, right and down
	direction = false;

	for (int i = 0; i < 18; i++)
	{
		if (eCurrentDirection == eLeft)
		{
			aliens[i]. -= .04f;
			if (aliens[i].x < 30) {
				direction = true;
			}
		}

		if (eCurrentDirection == eRight)
		{
			aliens[i].x += .04f;
			if (aliens[i].x >(screenWidth - 30)) {
				direction = true;
			}
		}

		MoveSprite(aliens[i].alienID, aliens[i].x, aliens[i].y);
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
			if (aliens[i].y > 0)
			{

				aliens[i].y -= 4.f;

			}

			//see if I can get this to work....
			if (aliens[i].y <= 40)
			{
				SetFont(invadersFont);
				DrawString("GAME OVER", screenWidth * 0.31f, screenHieght * 0.5f);

			}
		}

	}
}*/