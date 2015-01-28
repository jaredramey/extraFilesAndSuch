#ifndef _VEC2_H_
#define _VEC2_H_

class Vector2
{
public:
	Vector2();
	Vector2(float a_x, float a_y);
	
	Vector2 operator + (Vector2& a_RHS);
	Vector2 operator - (Vector2& a_RHS);
	Vector2 operator * (float a_RHS);

	Vector2& operator += (Vector2& a_RHS);
	Vector2& operator -= (Vector2& a_RHS);
	Vector2& operator *= (float a_RHS);

	float Dot(Vector2& a_RHS);
	float Magnitude();
	float SqMagnitude();
	Vector2& Normalize();
	Vector2 GetNormalize();

	float x, y;
};



#endif //_VEC2_H_