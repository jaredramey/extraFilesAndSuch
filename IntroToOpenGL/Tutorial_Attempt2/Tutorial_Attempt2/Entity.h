#pragma once
class Entity
{
public:
	Entity();
	~Entity();

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

	TriangleVertex triangleCreate;
};

