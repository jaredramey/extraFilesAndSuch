#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "Matrix4x4.h"
#include "Matrix3x3.h"

#include <vector>

class Entity
{
	friend class Scene;
public:
	Entity()
	{}

	//transformation management
	void SetPosition(Vector3 a_vPos);
	void SetScale(Vector3 a_vScale);
	void SetRotation(float a_fRotation);

	Matrix3x3 GetTransform()
	{
		return m_oLocalTransform;
	}

	Vector3 GetPosition();
	Vector3 GetScale();
	float GetRotation();

	Vector3 GetUp();
	Vector3 GetRight();

	void SetUp(Vector3 a_vUp);
	void SetRight(Vector3 a_vRight);

	//Child / Parent management
	void SetParent(Entity* a_pParent);
	void AddChild(Entity* a_pChild);
	void RemoveChild(Entity* a_pChild);

	virtual void Update(float a_dt){}
	virtual void Draw(unsigned int a_uiShader){}

protected:
	Matrix3x3 m_oLocalTransform;

};
#endif //_ENTITY_H_