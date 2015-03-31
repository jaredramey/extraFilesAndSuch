#ifndef _VEC3_H_
#define _VEC3_H_

class Vector3
{
public:
	Vector3();
	Vector3(float a_x, float a_y, float a_z);
	
	Vector3 operator + (Vector3& a_RHS);
	Vector3 operator - (Vector3& a_RHS);
	Vector3 operator * (float a_RHS);
	Vector3 operator / (float a_RHS);

	Vector3& operator += (Vector3& a_RHS);
	Vector3& operator -= (Vector3& a_RHS);
	Vector3& operator *= (float a_RHS);
	Vector3& operator /= (float a_RHS);

	float Dot(Vector3& a_RHS);
	float Magnitude();
	float SqMagnitude();
	Vector3& Normalize();
	Vector3 GetNormalize();
	Vector3 GetReflected(Vector3 a_vNormal);


	float x, y, z;
};



#endif //_VEC2_H_