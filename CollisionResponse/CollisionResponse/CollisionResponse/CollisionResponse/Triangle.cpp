#include "Triangle.h"
#include <GL/glew.h>

Triangle::Triangle()
{
	m_verts[0].vPos.x = -1;
	m_verts[0].vPos.y = -1;
	m_verts[0].vPos.z = 1;
	
	m_verts[1].vPos.x = 1;
	m_verts[1].vPos.y = -1;
	m_verts[1].vPos.z = 1;
	
	m_verts[2].vPos.x = 1;
	m_verts[2].vPos.y = 1;
	m_verts[2].vPos.z = 1;
	unsigned int uiIndecies[3] = {0,1,2};

	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiIBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertPC)*3, m_verts, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, uiIndecies, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Triangle::Update (float dt)
{

}

void Triangle::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);

	VertPC* pVerts = (VertPC*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for ( int i = 0 ; i < 3 ; ++i )
	{
		pVerts[i].vPos = m_oGlobalTransform * m_verts[i].vPos;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertPC), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertPC), (char*)0 + sizeof(float)*3);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
