#include "AIE.h"
#include <iostream>
#include "Vector.h"

Vector Start;
Vector End;
Vector Mid;

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	Start.SetPos(100, 350);
	End.SetPos(600, 350);
	Mid.SetPos(300, 25);


    int myTextureHandle = CreateSprite("./images/crate_sideup.png", 64, 64, true);

    //Game Loop
    do
    {
		
        MoveSprite(myTextureHandle, Start.getX(), Start.getY());
        DrawSprite(myTextureHandle);
		//Start.LERP(End, GetDeltaTime());
		Start.CubBezier(Mid, End, GetDeltaTime());

        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
