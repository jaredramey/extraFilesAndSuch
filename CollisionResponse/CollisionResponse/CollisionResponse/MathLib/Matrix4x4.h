#ifndef _MATRIX4X4E_H_
#define _MATRIX4X4E_H_

class Matrix4x4
{
public:
	Matrix4x4()
	{
		m_afMM[0][0] = 1;
		m_afMM[0][1] = 0;
		m_afMM[0][2] = 0;
		m_afMM[0][3] = 0;
		
		m_afMM[1][0] = 0;
		m_afMM[1][1] = 1;
		m_afMM[1][2] = 0;
		m_afMM[1][3] = 0;
		
		m_afMM[2][0] = 0;
		m_afMM[2][1] = 0;
		m_afMM[2][2] = 1;
		m_afMM[2][3] = 0;
			 
		m_afMM[3][0] = 0;
		m_afMM[3][1] = 0;
		m_afMM[3][2] = 0;
		m_afMM[3][3] = 1;
	}
	~Matrix4x4(){}

	//builds and returns a new identity matrix
	static Matrix4x4 GetOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

	//transposes matrix and returns *this
	Matrix4x4& Transpose();
	//builds and returns a new matrix that is the transpose of this matrix
	Matrix4x4 GetTranspose();
	
	Matrix4x4 operator *(Matrix4x4& a_RHS);
	Matrix4x4& operator *=(Matrix4x4& a_RHS);

	union
	{
		float m_afMM[4][4];
		float m_afM[16];
	};
};


#endif