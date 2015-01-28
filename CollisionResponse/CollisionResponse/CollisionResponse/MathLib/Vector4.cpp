#include "Vector4.h"
#include <math.h>

Vector4::Vector4() :
	x(0), y(0), z(0), w(0)
{}
Vector4::Vector4(float a_x, float a_y, float a_z, float a_w) :
	x(a_x), y(a_y), z(a_z), w(a_w)
{}
	
Vector4 Vector4::operator + (Vector4& a_RHS)
{
	Vector4 ret;
	ret.x = x + a_RHS.x;
	ret.y = y + a_RHS.y;
	ret.z = z + a_RHS.z;
	return ret;
}
Vector4 Vector4::operator - (Vector4& a_RHS)
{
	Vector4 ret;
	ret.x = x - a_RHS.x;
	ret.y = y - a_RHS.y;
	ret.z = z - a_RHS.z;
	return ret;
}
Vector4 Vector4::operator * (float a_RHS)
{
	Vector4 ret;
	ret.x = x * a_RHS;
	ret.y = y * a_RHS;
	ret.z = z * a_RHS;
	return ret;
}

Vector4& Vector4::operator += (Vector4& a_RHS)
{
	x = x + a_RHS.x;
	y = y + a_RHS.y;
	z = z + a_RHS.z;
	return *this;
}
Vector4& Vector4::operator -= (Vector4& a_RHS)
{
	x = x - a_RHS.x;
	y = y - a_RHS.y;
	z = z - a_RHS.z;
	return *this;
}
Vector4& Vector4::operator *= (float a_RHS)
{
	x = x * a_RHS;
	y = y * a_RHS;
	z = z * a_RHS;
	return *this;
}

float Vector4::Dot(Vector4& a_RHS)
{
	return (x*a_RHS.x)+(y*a_RHS.y)+(z*a_RHS.z);
}
float Vector4::Magnitude()
{
	return sqrtf((x*x)+(y*y)+(z*z));
}
float Vector4::SqMagnitude()
{
	return (x*x)+(y*y)+(z*z);
}
Vector4& Vector4::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
	return *this;
}
Vector4 Vector4::GetNormalize()
{
	Vector4 ret = *this;
	ret.Normalize();
	return ret;
}
