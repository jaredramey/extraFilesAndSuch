#ifndef _VEC4_H_
#define _VEC4_H_

class Vector4
{
public:
	Vector4();
	Vector4(float a_x, float a_y, float a_z, float a_w);
	
	Vector4 operator + (Vector4& a_RHS);
	Vector4 operator - (Vector4& a_RHS);
	Vector4 operator * (float a_RHS);

	Vector4& operator += (Vector4& a_RHS);
	Vector4& operator -= (Vector4& a_RHS);
	Vector4& operator *= (float a_RHS);

	float Dot(Vector4& a_RHS);
	float Magnitude();
	float SqMagnitude();
	Vector4& Normalize();
	Vector4 GetNormalize();

	float x, y, z, w;
};



#endif //_VEC2_H_