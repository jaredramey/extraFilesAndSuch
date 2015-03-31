#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include "Vector3.h"

class Matrix3x3
{
public:
	Matrix3x3()
	{
		m_afM[0][0] = 1;
		m_afM[0][1] = 0;
		m_afM[0][2] = 0;
		
		m_afM[1][0] = 0;
		m_afM[1][1] = 1;
		m_afM[1][2] = 0;
		
		m_afM[2][0] = 0;
		m_afM[2][1] = 0;
		m_afM[2][2] = 1;
	}
	~Matrix3x3(){}

	//builds and returns a new identity matrix
	static Matrix3x3 Identity();
	//transposes matrix and returns *this
	Matrix3x3& Transpose();
	//builds and returns a new matrix that is the transpose of this matrix
	Matrix3x3 GetTranspose();
	

	//builds and returns a new rotation matrix
	static Matrix3x3 setupRotation(float a_fRadians);
	//builds and returns a new scale matrix
	static Matrix3x3 setupScale(Vector3 a_Scale);
	//builds and returns a new translation matrix
	static Matrix3x3 setupTranslation(Vector3 a_Translation);

	Matrix3x3 operator +(Matrix3x3& a_RHS);
	Matrix3x3 operator -(Matrix3x3& a_RHS);
	Matrix3x3 operator *(Matrix3x3& a_RHS);

	Vector3 operator *(Vector3& a_RHS);

	Matrix3x3& operator +=(Matrix3x3& a_RHS);
	Matrix3x3& operator -=(Matrix3x3& a_RHS);
	Matrix3x3& operator *=(Matrix3x3& a_RHS);

	float m_afM[3][3];
};

#endif //_MATRIX3X3_H_