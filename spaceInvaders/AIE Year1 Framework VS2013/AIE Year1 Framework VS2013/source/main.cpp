#include "AIE.h"
#include <iostream>

//start of Main menu
enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eEND

};


int main(int argc, char* argv[])
{
	//screen and window set up
	Initialise(672, 780, false, "Space Invaders Clone");
	const int screenWidth = 672;
	const int screenHieght = 780;

	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));

	//player sprite
	int playerCannon = CreateSprite("./images/cannon.png", 64, 32, true);
	float xPos = 336;
	float yPos = 100;

	//enemy sprites
	unsigned int alienShips[18];
	float enemyX = screenWidth * 0.2f;
	float enemyY = screenHieght * 0.7f;
	for (int i = 0; i < 18; ++i)
	{
		alienShips[i] = CreateSprite("./images/invaders/invaders_1_00.png", 64, 62, true);
		MoveSprite(alienShips[i], enemyX, enemyY);
		enemyX += 0.12 * screenWidth;
		if (enemyX > screenWidth * 0.8f)
		{
			enemyX = screenWidth * 0.2f;
			enemyY -= 0.08 * screenHieght;
		}
	}


	//ect Sprites
	int arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", 672, 780, true);
	float marqueeXPos = 336;
	float marqueeYPos = 390;

	//Space invaders font
	const char* invadersFont = "./fonts/invaders.fnt";

	//stuff to be displayed
	char score1[10] = "00000";
	char highScore[10] = "00000";
	char score2[10] = "00000";
	char credit[10] = "99";
	char insertCoins[10] = "00";
	char credits[10] = "01";

	GAMESTATES eCurrentState = eMAIN_MENU;

	AddFont(invadersFont);
	

	
		//Game Loop
		do
		{
			
			ClearScreen();
			switch (eCurrentState)
			{
				start:
				case eMAIN_MENU:
					SetFont(invadersFont);
					//initializing special invaders font
					DrawSprite(arcadeMarquee); //(where did this come from?)
					MoveSprite(arcadeMarquee, marqueeXPos, marqueeYPos);
					DrawString(insertCoins, screenWidth * 0.43f, screenHieght - 275);
					DrawString("INSERT COINS", screenWidth * 0.357f, screenHieght - 250);
					DrawString(" / ", screenWidth * 0.4745f, screenHieght - 275);
					DrawString(credits, screenWidth * 0.5f, screenHieght - 275);
					DrawString("PRESS ENTER TO START", screenWidth * 0.27f, screenHieght - 400);

					if (IsKeyDown(257))
					{
						eCurrentState = eGAMEPLAY;
					}

				break;

				case eGAMEPLAY:
					//Player Variables
					//float playerX = screenWidth * 0.5f;		(playerX & playerY replaced by xPos and yPos?)
					//float playerY = screenHieght * 80.f;
					MoveSprite(playerCannon, xPos, yPos);
					DrawSprite(playerCannon);
					SetFont(invadersFont);
					//draw aliens
					for (int i = 0; i < 18; ++i)
					{
						DrawSprite(alienShips[i]);
					}

					//Player controls
					if (IsKeyDown(65)) // Move Left
					{
						if (xPos >= 0) //Prevent Player from moving off the screen
						{
							xPos -= 0.3f; //Movement Speed
						}
					}

					if (IsKeyDown(68)) //Move Right
					{
						if (xPos <= 668) //Prevent player from moving off the screen
						{
							xPos += 0.3f; // Movement Speed
						}
					}

					//initializing special invaders font
				


					//Screen text
					DrawString("SCORE <1>", screenWidth * 0.025f, screenHieght - 2);
					DrawString("HIGH SCORE", screenWidth * 0.39f, screenHieght - 2);
					DrawString("SCORE <2>", screenWidth * 0.79f, screenHieght - 2);
					DrawString(score1, screenWidth * 0.05f, screenHieght - 30);
					DrawString(highScore, screenWidth * 0.4345f, screenHieght - 30);
					DrawString(score2, screenWidth * 0.82f, screenHieght - 30);

					//Line accross screen
					//DrawLine(0, 40, screenWidth, 40, SColour(0x00, 0xFC, 0x00, 0xFF));

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
	

		DestroySprite(playerCannon);

		Shutdown();

		return 0;
}
