#include "Vector.h"


Vector::Vector()
{
}


Vector::~Vector()
{
}

void Vector::LERP(Vector &end, float t)
{
	float temp = (1 - t)*x + t*end.x;
	float tempY = (1 - t)*y + t*end.y;
	x = temp;
	y = tempY;
}

void Vector::CubBezier(Vector &p_Two, Vector &p_Three, float t)
{
	LERP(p_Two, t);

	p_Two.LERP(p_Three, t);

	LERP(p_Three, t);
}

void Vector::SetPos(float X, float Y)
{
	x = X;
	y = Y;
}

float Vector::getX()
{
	return x;
}

float Vector::getY()
{
	return y;
}