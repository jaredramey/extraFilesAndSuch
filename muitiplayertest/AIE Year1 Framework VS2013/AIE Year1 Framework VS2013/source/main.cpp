#include "AIE.h"
#include <iostream>
#include <windows.h>
#include <fstream>

int main( int argc, char* argv[] )
{	
    Initialise(1024, 700, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

    int myTextureHandle = CreateSprite("./images/crate_sideup.png", 64, 64, true);
    float xPos = 100;
    float yPos = 100;

    //Game Loop
    do
    {
        MoveSprite(myTextureHandle, xPos, yPos);
        DrawSprite(myTextureHandle);


		//KeyPress way1 GetAsyncKeyState(VK_[key]);
		///*
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (xPos > 0)
			{
				xPos--;
			}
		}

		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (xPos < 1024)
			{
				xPos++;
			}
		}

		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (yPos > 0)
			{
				yPos--;
			}
		}

		else if (GetAsyncKeyState(VK_UP))
		{
			if (yPos < 700)
			{
				yPos++;
			}
		}
		//*/

		/* Play around with this movement type [AIE header movement function]
		if (IsKeyDown(glfw key values))
		{
			yPos++;
		}
		*/


        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
