#include "Entity.h"

#pragma once

class Player : public Entity
{
private:
	float Postions[4];
	float Colours[4];

public:
	Player();
	~Player();

	//Triangle Data constructor
	Player(TriangleVertex *data);
};

