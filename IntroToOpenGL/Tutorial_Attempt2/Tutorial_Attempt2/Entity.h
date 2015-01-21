#pragma once
#include <glew.h>
#include <wglew.h>
#include <glfw3.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "SOIL.h"

class Entity
{
public:
	Entity();
	~Entity();

	GLFWwindow* window;

	struct TriangleVertex
	{
		float fPositions[4];
		float fColours[4];
		float fUVs[2];
	};

	struct QuadVertex
	{
		float fPositions[4];
		float fColours[4];
		float fUVs[3];
	};

	float points[9];

	int Initialize();

	void DrawTriangle();

private:
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
	unsigned int loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP);


};

