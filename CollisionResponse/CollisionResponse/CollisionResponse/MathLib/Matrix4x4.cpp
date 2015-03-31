#include "Matrix4x4.h"


//builds and returns a new identity matrix
Matrix4x4 Matrix4x4::GetOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	//ideally this function would be part of your matrix class
	//however I wasn't willing to write your matrix class for you just to show you this
	//so here we are in array format!
	//add this to your matrix class as a challenge if you like!
	Matrix4x4 ret;
	ret.m_afM[0] = 2.0f/(right - left);;
	ret.m_afM[1] = ret.m_afM[2] = ret.m_afM[3] = ret.m_afM[4] = 0;
	ret.m_afM[5] = 2.0f/(top - bottom);
	ret.m_afM[6] = ret.m_afM[7] = ret.m_afM[8] = ret.m_afM[9] = 0;
	ret.m_afM[10] = 2.0f/(a_fFar - a_fNear);
	ret.m_afM[11] = 0;
	ret.m_afM[12] = -1*((right + left)/(right - left));
	ret.m_afM[13] = -1*((top + bottom)/(top - bottom));
	ret.m_afM[14] = -1*((a_fFar + a_fNear)/(a_fFar - a_fNear));
	ret.m_afM[15] = 1;
	return ret;
}

//transposes matrix and returns *this
Matrix4x4& Matrix4x4::Transpose()
{
	float temp = m_afMM[0][1];
	m_afMM[0][1] = m_afMM[1][0];
	m_afMM[1][0] = temp;

	temp = m_afMM[0][2];
	m_afMM[0][2] = m_afMM[2][0];
	m_afMM[2][0] = temp;

	temp = m_afMM[0][3];
	m_afMM[0][3] = m_afMM[3][0];
	m_afMM[3][0] = temp;
	
	temp = m_afMM[1][2];
	m_afMM[1][2] = m_afMM[2][1];
	m_afMM[2][1] = temp;

	temp = m_afMM[1][3];
	m_afMM[1][3] = m_afMM[3][1];
	m_afMM[3][1] = temp;
	
	temp = m_afMM[3][2];
	m_afMM[3][2] = m_afMM[2][3];
	m_afMM[2][3] = temp;

	return *this;
}
//builds and returns a new matrix that is the transpose of this matrix
Matrix4x4 Matrix4x4::GetTranspose()
{
	Matrix4x4 ret = *this;
	ret.Transpose();
	return ret;
}
	
Matrix4x4 Matrix4x4::operator *(Matrix4x4& a_RHS)
{
	Matrix4x4 temp;

	temp.m_afMM[0][0] = m_afMM[0][0] * a_RHS.m_afMM[0][0] + m_afMM[1][0] * a_RHS.m_afMM[0][1] + m_afMM[2][0] * a_RHS.m_afMM[0][2] + m_afMM[2][0] * a_RHS.m_afMM[0][3];
	temp.m_afMM[1][0] = m_afMM[0][0] * a_RHS.m_afMM[1][0] + m_afMM[1][0] * a_RHS.m_afMM[1][1] + m_afMM[2][0] * a_RHS.m_afMM[1][2] + m_afMM[2][0] * a_RHS.m_afMM[1][3];
	temp.m_afMM[2][0] = m_afMM[0][0] * a_RHS.m_afMM[2][0] + m_afMM[1][0] * a_RHS.m_afMM[2][1] + m_afMM[2][0] * a_RHS.m_afMM[2][2] + m_afMM[2][0] * a_RHS.m_afMM[2][3];
	temp.m_afMM[3][0] = m_afMM[0][0] * a_RHS.m_afMM[3][0] + m_afMM[1][0] * a_RHS.m_afMM[3][1] + m_afMM[2][0] * a_RHS.m_afMM[3][2] + m_afMM[2][0] * a_RHS.m_afMM[3][3];
	
	temp.m_afMM[0][1] = m_afMM[0][1] * a_RHS.m_afMM[0][0] + m_afMM[1][1] * a_RHS.m_afMM[0][1] + m_afMM[2][1] * a_RHS.m_afMM[0][2] + m_afMM[2][1] * a_RHS.m_afMM[0][3];
	temp.m_afMM[1][1] = m_afMM[0][1] * a_RHS.m_afMM[1][0] + m_afMM[1][1] * a_RHS.m_afMM[1][1] + m_afMM[2][1] * a_RHS.m_afMM[1][2] + m_afMM[2][1] * a_RHS.m_afMM[1][3];
	temp.m_afMM[2][1] = m_afMM[0][1] * a_RHS.m_afMM[2][0] + m_afMM[1][1] * a_RHS.m_afMM[2][1] + m_afMM[2][1] * a_RHS.m_afMM[2][2] + m_afMM[2][1] * a_RHS.m_afMM[2][3];
	temp.m_afMM[3][1] = m_afMM[0][1] * a_RHS.m_afMM[3][0] + m_afMM[1][1] * a_RHS.m_afMM[3][1] + m_afMM[2][1] * a_RHS.m_afMM[3][2] + m_afMM[2][1] * a_RHS.m_afMM[3][3];
	
	temp.m_afMM[0][2] = m_afMM[0][2] * a_RHS.m_afMM[0][0] + m_afMM[1][2] * a_RHS.m_afMM[0][1] + m_afMM[2][2] * a_RHS.m_afMM[0][2] + m_afMM[2][2] * a_RHS.m_afMM[0][3];
	temp.m_afMM[1][2] = m_afMM[0][2] * a_RHS.m_afMM[1][0] + m_afMM[1][2] * a_RHS.m_afMM[1][1] + m_afMM[2][2] * a_RHS.m_afMM[1][2] + m_afMM[2][2] * a_RHS.m_afMM[1][3];
	temp.m_afMM[2][2] = m_afMM[0][2] * a_RHS.m_afMM[2][0] + m_afMM[1][2] * a_RHS.m_afMM[2][1] + m_afMM[2][2] * a_RHS.m_afMM[2][2] + m_afMM[2][2] * a_RHS.m_afMM[2][3];
	temp.m_afMM[3][2] = m_afMM[0][2] * a_RHS.m_afMM[3][0] + m_afMM[1][2] * a_RHS.m_afMM[3][1] + m_afMM[2][2] * a_RHS.m_afMM[3][2] + m_afMM[2][2] * a_RHS.m_afMM[3][3];
	
	temp.m_afMM[0][3] = m_afMM[0][3] * a_RHS.m_afMM[0][0] + m_afMM[1][3] * a_RHS.m_afMM[0][1] + m_afMM[2][3] * a_RHS.m_afMM[0][2] + m_afMM[2][3] * a_RHS.m_afMM[0][3];
	temp.m_afMM[1][3] = m_afMM[0][3] * a_RHS.m_afMM[1][0] + m_afMM[1][3] * a_RHS.m_afMM[1][1] + m_afMM[2][3] * a_RHS.m_afMM[1][2] + m_afMM[2][3] * a_RHS.m_afMM[1][3];
	temp.m_afMM[2][3] = m_afMM[0][3] * a_RHS.m_afMM[2][0] + m_afMM[1][3] * a_RHS.m_afMM[2][1] + m_afMM[2][3] * a_RHS.m_afMM[2][2] + m_afMM[2][3] * a_RHS.m_afMM[2][3];
	temp.m_afMM[3][3] = m_afMM[0][3] * a_RHS.m_afMM[3][0] + m_afMM[1][3] * a_RHS.m_afMM[3][1] + m_afMM[2][3] * a_RHS.m_afMM[3][2] + m_afMM[2][3] * a_RHS.m_afMM[3][3];

	return temp;
}

Matrix4x4& Matrix4x4::operator *=(Matrix4x4& a_RHS)
{
	*this = *this * a_RHS;

	return *this;
}