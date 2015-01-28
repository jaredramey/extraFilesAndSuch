#include "Vector2.h"
#include <math.h>

Vector2::Vector2() :
	x(0), y(0)
{}

Vector2::Vector2(float a_x, float a_y):
	x(a_x), y(a_y)
{}
	
Vector2 Vector2::operator + (Vector2& a_RHS)
{
	Vector2 temp;
	temp.x = x + a_RHS.x;
	temp.y = y + a_RHS.y;
	return temp;
}
Vector2 Vector2::operator - (Vector2& a_RHS)
{
	Vector2 temp;
	temp.x = x - a_RHS.x;
	temp.y = y - a_RHS.y;
	return temp;
}
Vector2 Vector2::operator * (float a_RHS)
{
	Vector2 temp;
	temp.x = x * a_RHS;
	temp.y = y * a_RHS;
	return temp;
}

Vector2& Vector2::operator += (Vector2& a_RHS)
{
	x += a_RHS.x;
	y += a_RHS.y;
	return *this;
}
Vector2& Vector2::operator -= (Vector2& a_RHS)
{
	x -= a_RHS.x;
	y -= a_RHS.y;
	return *this;
}
Vector2& Vector2::operator *= (float a_RHS)
{
	x *= a_RHS;
	y *= a_RHS;
	return *this;
}

float Vector2::Dot(Vector2& a_RHS)
{
	return (x*a_RHS.x)+(y*a_RHS.y);
}
float Vector2::Magnitude()
{
	return sqrtf((x*x)+(y*y));
}
float Vector2::SqMagnitude()
{
	return (x*x)+(y*y);
}
Vector2& Vector2::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	return *this;
}
Vector2 Vector2::GetNormalize()
{
	Vector2 temp = *this;
	temp.Normalize();
	return temp;
}

