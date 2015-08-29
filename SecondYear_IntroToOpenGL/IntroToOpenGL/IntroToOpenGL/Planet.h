#pragma once
#include <iostream>
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Planet
{
public:
	vec3 Position;

	Planet();
	~Planet();

	//Custom planet constructor
	Planet(vec3 Pos, float radius, int rows, int columns, vec4 colorFill);
	void Update(mat4 t);
	void Orbit(float currentTime, Planet &planet, float angle);

private:
	float Radius;
	int Rows;
	int Columns;
	vec4 Color;
};

