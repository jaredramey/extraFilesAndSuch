#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Entity.h"
#include "Vertex.h"

class Circle : public Entity
{
public:
	Circle(float a_fRadius = 1.f, Vector4 a_vColour = Vector4(1,1,1,1));
	virtual ~Circle(){}

	virtual void Update(float a_dt);
	virtual void Draw(unsigned int a_uiShader);

	void SetVelocity(Vector3 a_vVelocity)
	{
		m_vVelocity = a_vVelocity;
	}
	
	bool IsColliding(Circle* a_pOther);
	bool IsColliding(Vector3 a_vPoint);

	void ApplyCollision(Circle* a_pOther);


private:
	unsigned m_uiVBO;
	unsigned m_uiIBO;
	
	VertPC m_aVerts[32];
	float m_fMass;

	Vector3 m_vVelocity;

	float m_fRadius;
};


#endif //_CIRCLE_H_