#include "Matrix3x3.h"
#include <string.h>
#include <math.h>

//builds and returns a new identity matrix
Matrix3x3 Matrix3x3::Identity()
{
	Matrix3x3 ret;
	ret.m_afM[0][0] = 1;
	ret.m_afM[0][1] = 0;
	ret.m_afM[0][2] = 0;
	
	ret.m_afM[1][0] = 0;
	ret.m_afM[1][1] = 1;
	ret.m_afM[1][2] = 0;
	
	ret.m_afM[2][0] = 0;
	ret.m_afM[2][1] = 0;
	ret.m_afM[2][2] = 1;
	
	return ret;
}

//transposes matrix and returns *this
Matrix3x3& Matrix3x3::Transpose()
{
	float temp = m_afM[0][1];
	m_afM[0][1] = m_afM[1][0];
	m_afM[1][0] = temp;

	temp = m_afM[0][2];
	m_afM[0][2] = m_afM[2][0];
	m_afM[2][0] = temp;

	temp = m_afM[1][2];
	m_afM[1][2] = m_afM[2][1];
	m_afM[2][1] = temp;

	return *this;
}

//builds and returns a new matrix that is the transpose of this matrix
Matrix3x3 Matrix3x3::GetTranspose()
{
	Matrix3x3 temp = *this;
	temp.Transpose();
	return temp;
}


Matrix3x3 Matrix3x3::operator +(Matrix3x3& a_RHS)
{
	Matrix3x3 temp = *this;
	temp.m_afM[0][0] += a_RHS.m_afM[0][0];
	temp.m_afM[0][1] += a_RHS.m_afM[0][1];
	temp.m_afM[0][2] += a_RHS.m_afM[0][2];
	
	temp.m_afM[1][0] += a_RHS.m_afM[1][0];
	temp.m_afM[1][1] += a_RHS.m_afM[1][1];
	temp.m_afM[1][2] += a_RHS.m_afM[1][2];
	
	temp.m_afM[2][0] += a_RHS.m_afM[2][0];
	temp.m_afM[2][1] += a_RHS.m_afM[2][1];
	temp.m_afM[2][2] += a_RHS.m_afM[2][2];

	return temp;
}

Matrix3x3 Matrix3x3::operator -(Matrix3x3& a_RHS)
{
	Matrix3x3 temp = *this;
	temp.m_afM[0][0] -= a_RHS.m_afM[0][0];
	temp.m_afM[0][1] -= a_RHS.m_afM[0][1];
	temp.m_afM[0][2] -= a_RHS.m_afM[0][2];
	
	temp.m_afM[1][0] -= a_RHS.m_afM[1][0];
	temp.m_afM[1][1] -= a_RHS.m_afM[1][1];
	temp.m_afM[1][2] -= a_RHS.m_afM[1][2];
	
	temp.m_afM[2][0] -= a_RHS.m_afM[2][0];
	temp.m_afM[2][1] -= a_RHS.m_afM[2][1];
	temp.m_afM[2][2] -= a_RHS.m_afM[2][2];

	return temp;
}

Matrix3x3 Matrix3x3::operator *(Matrix3x3& a_RHS)
{
	Matrix3x3 temp;
	temp.m_afM[0][0] = m_afM[0][0] * a_RHS.m_afM[0][0] + m_afM[1][0] * a_RHS.m_afM[0][1] + m_afM[2][0] * a_RHS.m_afM[0][2];
	temp.m_afM[1][0] = m_afM[0][0] * a_RHS.m_afM[1][0] + m_afM[1][0] * a_RHS.m_afM[1][1] + m_afM[2][0] * a_RHS.m_afM[1][2];
	temp.m_afM[2][0] = m_afM[0][0] * a_RHS.m_afM[2][0] + m_afM[1][0] * a_RHS.m_afM[2][1] + m_afM[2][0] * a_RHS.m_afM[2][2];
	
	temp.m_afM[0][1] = m_afM[0][1] * a_RHS.m_afM[0][0] + m_afM[1][1] * a_RHS.m_afM[0][1] + m_afM[2][1] * a_RHS.m_afM[0][2];
	temp.m_afM[1][1] = m_afM[0][1] * a_RHS.m_afM[1][0] + m_afM[1][1] * a_RHS.m_afM[1][1] + m_afM[2][1] * a_RHS.m_afM[1][2];
	temp.m_afM[2][1] = m_afM[0][1] * a_RHS.m_afM[2][0] + m_afM[1][1] * a_RHS.m_afM[2][1] + m_afM[2][1] * a_RHS.m_afM[2][2];
	
	temp.m_afM[0][2] = m_afM[0][2] * a_RHS.m_afM[0][0] + m_afM[1][2] * a_RHS.m_afM[0][1] + m_afM[2][2] * a_RHS.m_afM[0][2];
	temp.m_afM[1][2] = m_afM[0][2] * a_RHS.m_afM[1][0] + m_afM[1][2] * a_RHS.m_afM[1][1] + m_afM[2][2] * a_RHS.m_afM[1][2];
	temp.m_afM[2][2] = m_afM[0][2] * a_RHS.m_afM[2][0] + m_afM[1][2] * a_RHS.m_afM[2][1] + m_afM[2][2] * a_RHS.m_afM[2][2];

	return temp;
}


Matrix3x3& Matrix3x3::operator +=(Matrix3x3& a_RHS)
{
	m_afM[0][0] += a_RHS.m_afM[0][0];
	m_afM[0][1] += a_RHS.m_afM[0][1];
	m_afM[0][2] += a_RHS.m_afM[0][2];
	
	m_afM[1][0] += a_RHS.m_afM[1][0];
	m_afM[1][1] += a_RHS.m_afM[1][1];
	m_afM[1][2] += a_RHS.m_afM[1][2];
	
	m_afM[2][0] += a_RHS.m_afM[2][0];
	m_afM[2][1] += a_RHS.m_afM[2][1];
	m_afM[2][2] += a_RHS.m_afM[2][2];

	return *this;
}

Matrix3x3& Matrix3x3::operator -=(Matrix3x3& a_RHS)
{
	m_afM[0][0] -= a_RHS.m_afM[0][0];
	m_afM[0][1] -= a_RHS.m_afM[0][1];
	m_afM[0][2] -= a_RHS.m_afM[0][2];
	
	m_afM[1][0] -= a_RHS.m_afM[1][0];
	m_afM[1][1] -= a_RHS.m_afM[1][1];
	m_afM[1][2] -= a_RHS.m_afM[1][2];
	
	m_afM[2][0] -= a_RHS.m_afM[2][0];
	m_afM[2][1] -= a_RHS.m_afM[2][1];
	m_afM[2][2] -= a_RHS.m_afM[2][2];

	return *this;
}

Matrix3x3& Matrix3x3::operator *=(Matrix3x3& a_RHS)
{
	Matrix3x3 temp = *this * a_RHS;
	*this = temp;
	return *this;
}

//builds and returns a new rotation matrix
Matrix3x3 Matrix3x3::setupRotation(float a_fRadians)
{
	Matrix3x3 temp = Matrix3x3::Identity();
	
	temp.m_afM[0][0] = cosf(a_fRadians);
	temp.m_afM[0][1] = sinf(a_fRadians);

	temp.m_afM[1][0] = -sinf(a_fRadians);
	temp.m_afM[1][1] = cosf(a_fRadians);

	return temp;
}

//builds and returns a new scale matrix
Matrix3x3 Matrix3x3::setupScale(Vector3 a_Scale)
{
	Matrix3x3 temp = Matrix3x3::Identity();
	
	temp.m_afM[0][0] = a_Scale.x;
	temp.m_afM[1][1] = a_Scale.y;

	return temp;
}

//builds and returns a new translation matrix
Matrix3x3 Matrix3x3::setupTranslation(Vector3 a_Translation)
{
	Matrix3x3 temp = Matrix3x3::Identity();

	temp.m_afM[2][0] = a_Translation.x;
	temp.m_afM[2][1] = a_Translation.y;

	return temp;
}

Vector3 Matrix3x3::operator *(Vector3& a_RHS)
{
	Vector3 ret;
	
	ret.x = m_afM[0][0] * a_RHS.x + m_afM[1][0] * a_RHS.y + m_afM[2][0] * a_RHS.z;
	ret.y = m_afM[0][1] * a_RHS.x + m_afM[1][1] * a_RHS.y + m_afM[2][1] * a_RHS.z;
	ret.z = m_afM[0][2] * a_RHS.x + m_afM[1][2] * a_RHS.y + m_afM[2][2] * a_RHS.z;

	return ret;

}