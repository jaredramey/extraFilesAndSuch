#include "Vector3.h"
#include <math.h>

Vector3::Vector3() :
	x(0), y(0), z(0)
{}
	
Vector3::Vector3(float a_x, float a_y, float a_z) :
	x(a_x), y(a_y), z(a_z)
{}

Vector3 Vector3::operator + (Vector3& a_RHS)
{
	Vector3 temp;
	temp.x = x + a_RHS.x;
	temp.y = y + a_RHS.y;
	return temp;
}

Vector3 Vector3::operator - (Vector3& a_RHS)
{
	Vector3 temp;
	temp.x = x - a_RHS.x;
	temp.y = y - a_RHS.y;
	return temp;
}

Vector3 Vector3::operator * (float a_RHS)
{
	Vector3 temp;
	temp.x = x * a_RHS;
	temp.y = y * a_RHS;
	return temp;
}

Vector3 Vector3::operator / (float a_RHS)
{
	Vector3 temp;
	temp.x = x / a_RHS;
	temp.y = y / a_RHS;
	return temp;
}

Vector3& Vector3::operator += (Vector3& a_RHS)
{
	x += a_RHS.x;
	y += a_RHS.y;
	return *this;
}

Vector3& Vector3::operator -= (Vector3& a_RHS)
{
	x -= a_RHS.x;
	y -= a_RHS.y;
	return *this;
}

Vector3& Vector3::operator *= (float a_RHS)
{
	x *= a_RHS;
	y *= a_RHS;
	return *this;
}

Vector3& Vector3::operator /= (float a_RHS)
{
	x /= a_RHS;
	y /= a_RHS;
	return *this;
}

float Vector3::Dot(Vector3& a_RHS)
{
	return (x*a_RHS.x)+(y*a_RHS.y);
}

float Vector3::Magnitude()
{
	return sqrtf((x*x)+(y*y));
}

float Vector3::SqMagnitude()
{
	return (x*x)+(y*y);
}

Vector3& Vector3::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	return *this;
}

Vector3 Vector3::GetNormalize()
{
	Vector3 temp = *this;
	temp.Normalize();
	return temp;
}

//////////////////////////////////////////////////////////////////
//IMPLEMENT REFLECTION FUNCTION
//////////////////////////////////////////////////////////////////

Vector3 Vector3::GetReflected(Vector3 a_vNormal)
{
	float magnitude = -(a_vNormal.Magnitude());
	float projectedVect = (magnitude * a_vNormal.SqMagnitude());

	return *this;

}

