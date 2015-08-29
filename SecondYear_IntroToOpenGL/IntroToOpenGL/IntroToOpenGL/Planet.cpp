#include "Planet.h"



Planet::Planet()
{
}


Planet::~Planet()
{
}

//Custom planet constructor
Planet::Planet(vec3 pos, float radius, int rows, int columns, vec4 colorFill)
{
	//Save position and radius in case it's needed later
	Position = pos;
	Radius = radius;
	Rows = rows;
	Columns = columns;
	Color = colorFill;
}

void Planet::Update(mat4 t)
{
		Gizmos::addSphere(Position, Radius, Rows, Columns, Color, &t);
}

void Planet::Orbit(float currentTime, Planet &planet, float angle)
{
	float newX = 0;
	float newZ = 0;

			//Simplifying all points to xyz or uvw to make calls easier for equations
	//first point (simplifying this->Position.x to x)
	float x = this->Position.x;
	float y = this->Position.y;
	float z = this->Position.z;
	//second point (simplifying planet.Position.x to u)
	float u = planet.Position.x;
	float v = planet.Position.y;
	float w = planet.Position.z;


	newX += (u*((u*x) + (v*y) + (w*z))*(1 - cos(angle)) + ((u*u) + (v*v) + (w*w))*x*cos(angle) + sqrt(((u*u) + (v*v) + (w*w))*(-((w*y) + (v*z)))*sin(angle))) / ((u*u) + (v*v) + (w*w));
	newZ += (w*((u*x) + (v*y) + (w*z))*(1 - cos(angle)) + ((u*u) + (v*v) + (w*w))*z*cos(angle) + sqrt(((u*u) + (v*v) + (w*w))*(-((w*y) + (v*z)))*sin(angle))) / ((u*u) + (v*v) + (w*w));

	Position = vec3(newX, 0.0f, newZ);
}