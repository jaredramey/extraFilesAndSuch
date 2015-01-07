#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

Player::Player(TriangleVertex *Data)
{
	Postions[4] = Data->fPositions[4];
	Colours[4] = Data->fColours[4];
}



