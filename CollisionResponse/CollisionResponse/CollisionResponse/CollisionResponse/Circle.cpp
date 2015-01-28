#include "Circle.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glew.h>

#include "Window.h"

Circle::Circle(float a_fRadius, Vector4 a_vColour) : 
	m_fRadius(a_fRadius)
{
	m_aVerts[0].m_vPos = Vector3(0,0,1);
	m_aVerts[0].m_vColour = a_vColour;
	m_fMass = 1.f;
	for ( int i = 0 ; i < 31 ; ++i )
	{
		m_aVerts[i+1].m_vPos = 
			Vector3(
			  sinf((i / 31.f) * (float)M_PI*2.f) * a_fRadius
			, cosf((i / 31.f) * (float)M_PI*2.f) * a_fRadius
			, 1);

		m_aVerts[i+1].m_vColour = a_vColour;
	}

	unsigned int indexArray[33];
	for (int i = 0 ; i < 32 ; ++i) indexArray[i] = i;
	indexArray[32] = 1;
	
	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiIBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_aVerts), m_aVerts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vVelocity = Vector3(500,500,0);

}

void Circle::Update(float a_dt)
{
	Vector3 vPos = GetPosition();
	float e = 0.8f;
	float frictionCoefficient = 0.5f;

	//Apply friction
	m_vVelocity -= (m_vVelocity * a_dt) * frictionCoefficient;
	//Apply Velocity
	vPos += m_vVelocity * a_dt;
	
	//Reflecting along each wall
	if (vPos.x + m_fRadius > GetWindowDimensions().x / 2.f)
	{
		vPos.x = GetWindowDimensions().x / 2.f - m_fRadius;
		m_vVelocity = m_vVelocity.GetReflected(Vector3(-1,0,0)) * e;
	}
	if (vPos.y + m_fRadius > GetWindowDimensions().y / 2.f)
	{
		vPos.y = GetWindowDimensions().y / 2.f - m_fRadius;
		m_vVelocity = m_vVelocity.GetReflected(Vector3(0,-1,0)) * e;
	}
	if (vPos.x - m_fRadius < -GetWindowDimensions().x / 2.f)
	{
		vPos.x = -GetWindowDimensions().x / 2.f + m_fRadius;
		m_vVelocity = m_vVelocity.GetReflected(Vector3(1,0,0)) * e;
	}
	if (vPos.y - m_fRadius < -GetWindowDimensions().y / 2.f)
	{
		vPos.y = -GetWindowDimensions().y / 2.f + m_fRadius;
		m_vVelocity = m_vVelocity.GetReflected(Vector3(0,1,0)) * e;
	}

	SetPosition(vPos);
}

void Circle::Draw(unsigned int a_uiShader)
{
	GLuint MatrixIDModel = glGetUniformLocation(a_uiShader, "mModel");
	glUniformMatrix3fv(MatrixIDModel, 1, GL_FALSE, (float*)&GetTransform());

	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertPC), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertPC), (char*)0 + sizeof(Vector3));
	
	glDrawElements(GL_TRIANGLE_FAN, 33, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool Circle::IsColliding(Circle* a_pOther)
{
	float fRadSum = m_fRadius + a_pOther->m_fRadius;
	return (GetPosition() - a_pOther->GetPosition()).SqMagnitude() < (fRadSum * fRadSum);
}

bool Circle::IsColliding(Vector3 a_vPoint)
{
	return (GetPosition() - a_vPoint).SqMagnitude() < (m_fRadius * m_fRadius);
}

void Circle::ApplyCollision(Circle* a_pOther)
{
	////////////////////////////////////////////////////////////////////////////////
	//IMPLEMENT COLLISION RESPONSE HERE
	////////////////////////////////////////////////////////////////////////////////

}