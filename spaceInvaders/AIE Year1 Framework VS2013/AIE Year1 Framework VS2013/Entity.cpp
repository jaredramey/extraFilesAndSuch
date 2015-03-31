#include "Entity.h"


Entity::Entity()
{
}

void Entity::SetSize(float a_width, float a_heigth)
{
	width = a_width;
	heigth = a_heigth;
}

void Entity::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void Entity::SetSpriteID(unsigned int a_spriteID)
{
	spriteID = a_spriteID;
}

unsigned int Entity::GetSpriteID()
{
	return spriteID;
}

void Entity::SetWidth(float a_width)
{
	width = a_width;
}

void Entity::SetHeigth(float a_heigth)
{
	heigth = a_heigth;
}

float Entity::GetWidth()
{
	return width;
}

float Entity::GetHeigth()
{
	return heigth;
}

void Entity::SetX(float a_x)
{
	x = a_x;
}

void Entity::SetY(float a_y)
{
	y = a_y;
}

float Entity::GetX()
{
	return x;
}

float Entity::GetY()
{
	return y;
}


Entity::~Entity()
{
}
