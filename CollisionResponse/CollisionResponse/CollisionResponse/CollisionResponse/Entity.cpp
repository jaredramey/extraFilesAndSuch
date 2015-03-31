#include "Entity.h"

#include <math.h>

Vector3 Entity::GetPosition()
{
	Vector3 ret;
	
	ret.x = m_oLocalTransform.m_afM[2][0];
	ret.y = m_oLocalTransform.m_afM[2][1];
	ret.z = 1;

	return ret;
}

Vector3 Entity::GetScale()
{
	//get x axis
	Vector3 xAxis;
	xAxis.x = m_oLocalTransform.m_afM[0][0];
	xAxis.y = m_oLocalTransform.m_afM[0][1];
	xAxis.z = 0;

	//get y axis
	Vector3 yAxis;
	yAxis.x = m_oLocalTransform.m_afM[1][0];
	yAxis.y = m_oLocalTransform.m_afM[1][1];
	yAxis.z = 0;

	//calculate scale
	Vector3 ret;
	ret.x = xAxis.Magnitude();
	ret.y = yAxis.Magnitude();
	ret.z = 0;
	return ret; // return scale
}

float Entity::GetRotation()
{
	return atan2f(m_oLocalTransform.m_afM[0][1], m_oLocalTransform.m_afM[0][0]);
}

void Entity::SetPosition(Vector3 a_vPos)
{
	m_oLocalTransform.m_afM[2][0] = a_vPos.x;
	m_oLocalTransform.m_afM[2][1] = a_vPos.y;
}

void Entity::SetScale(Vector3 a_vScale)
{
	float fRotation = GetRotation();
	Vector3 vPosition = GetPosition();

	m_oLocalTransform = Matrix3x3::setupTranslation(vPosition)
		* Matrix3x3::setupRotation(fRotation)
		* Matrix3x3::setupScale(a_vScale);
}

void Entity::SetRotation(float a_fRotation)
{
	Vector3 vPosition = GetPosition();
	Vector3 vScale = GetScale();

	m_oLocalTransform = Matrix3x3::setupTranslation(vPosition)
		* Matrix3x3::setupRotation(a_fRotation)
		* Matrix3x3::setupScale(vScale);
}

Vector3 Entity::GetUp()
{
	Vector3 ret;
	
	ret.x = m_oLocalTransform.m_afM[1][0];
	ret.y = m_oLocalTransform.m_afM[1][1];
	ret.z = 0;
	ret.Normalize();
	return ret;
}

Vector3 Entity::GetRight()
{
	Vector3 ret;
	
	ret.x = m_oLocalTransform.m_afM[0][0];
	ret.y = m_oLocalTransform.m_afM[0][1];
	ret.z = 0;
	
	ret.Normalize();
	return ret;
}

void Entity::SetUp(Vector3 a_vUp)
{
	SetRight(Vector3(a_vUp.y, -a_vUp.x, 0));
}

void Entity::SetRight(Vector3 a_vRight)
{
	SetRotation(atan2f(a_vRight.y, a_vRight.x));
}
