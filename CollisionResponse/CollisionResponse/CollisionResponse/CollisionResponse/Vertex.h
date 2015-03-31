#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

struct VertPC
{
	Vector3 m_vPos;
	Vector4 m_vColour;
};

struct VertPCU
{
	Vector3 m_vPos;
	Vector4 m_vColour;
	Vector2 m_vUV;
};


#endif //_VERTEX_H_